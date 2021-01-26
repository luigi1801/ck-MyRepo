#! /bin/bash

function exit_if_error() {
 if [ "${?}" != "0" ]; then exit 1; fi
}

function remove_dir_if_exists() {
  if [ -d $1 ]; then rm -rdf $1; fi
}

echo "--------------------------"
echo "Creating Delegate Lib"
echo ${CK_ENV_LIB_TF}/src/tensorflow/lite/delegates/utils/dummy_delegate
echo "--------------------------"


#bazel build -c opt ${CK_ENV_LIB_TF}/src/
cd ${CK_ENV_LIB_TF}/src
bazel build -c opt tensorflow/lite/delegates/utils/dummy_delegate:dummy_external_delegate.so
exit_if_error
bazel shutdown
exit_if_error

remove_dir_if_exists ${INSTALL_DIR}/lib
mkdir ${INSTALL_DIR}/lib
cp bazel-bin/tensorflow/lite/delegates/utils/dummy_delegate/dummy_external_delegate.so ${INSTALL_DIR}/lib/lib-dummy_external_delegate.so

return 0