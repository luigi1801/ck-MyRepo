/*
 CK program template

 See CK LICENSE.txt for licensing details
 See CK COPYRIGHT.txt for copyright details

 Developer: Grigori Fursin, 2018, Grigori.Fursin@cTuning.org, http://fursin.net
*/

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/tools/gen_op_registration.h"
#include "tensorflow/lite/delegates/utils/simple_delegate.h"
#include "tensorflow/lite/delegates/utils/dummy_delegate/dummy_delegate.h"

#include "tensorflow/lite/c/common.h"

namespace tflite{
namespace VC_delegate{

}
}

int main(int argc, char* argv[])
{
/*
  char* env;
  
  std::cout << "Hello world!" << std::endl << std::endl;

  env=getenv("CK_VAR1");
  if (env!=NULL) {
    printf("CK_VAR1=%s\n",env);
  }

  env=getenv("CK_VAR2");
  if (env!=NULL) {
    printf("CK_VAR2=%s\n",env);
  }
*/
  std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("../linear.tflite");

  if(!model){
      printf("Failed to mmap model\n");
      exit(0);
  }

  printf("Creación del Interpreter\n");
  tflite::ops::builtin::BuiltinOpResolver resolver;
  std::unique_ptr<tflite::Interpreter> interpreter;
  tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

  printf("Creación del Delegate\n");
  DummyDelegateOptions params = TfLiteDummyDelegateOptionsDefault();
  auto* delegate_ptr = TfLiteDummyDelegateCreate(&params);

  tflite::Interpreter::TfLiteDelegatePtr delegate(delegate_ptr,
  [](TfLiteDelegate* delegate) {
     TfLiteDummyDelegateDelete(delegate);
  });

  printf("Cargando delegate al interpreter\n");
  interpreter->ModifyGraphWithDelegate(delegate.get());

  
  // Resize input tensors, if desired.
  interpreter->AllocateTensors();
  

  float* input = interpreter->typed_input_tensor<float>(0);
  // Dummy input for testing
  *input = 25.0;

  printf("Invocando Inferencia\n");
  interpreter->Invoke();

  float* output = interpreter->typed_output_tensor<float>(0);

  printf("Result is: %f\n", *output);

  return 0;
}
