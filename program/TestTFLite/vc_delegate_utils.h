#ifndef VC_DELEGATE_UTILS_H_
#define VC_DELEGATE_UTILS_H_

#include <memory>

#include "tensorflow/lite/c/common.h"


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct {
  // Allowed ops to delegate.
  int allowed_builtin_code;
  // Report error during init.
  bool error_during_init;
  // Report error during prepare.
  bool error_during_prepare;
  // Report error during invoke.
  bool error_during_invoke;
} VCDelegateOptions;

// Returns a structure with the default delegate options.
VCDelegateOptions TfLiteVCDelegateOptionsDefault();

// Creates a new delegate instance that needs to be destroyed with
// `TfLiteDummyDelegateDelete` when delegate is no longer used by TFLite.
// When `options` is set to `nullptr`, the above default values are used:
TfLiteDelegate* TfLiteVCDelegateCreate(const VCDelegateOptions* options);

// Destroys a delegate created with `TfLiteDummyDelegateCreate` call.
void TfLiteVCDelegateDelete(TfLiteDelegate* delegate);

#ifdef __cplusplus
}
#endif  // __cplusplus

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif  // VC_DELEGATE_UTILS_H_
