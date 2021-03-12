#ifndef LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_
#define LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_

namespace owcr {
namespace extension {

class IExtensionManager;

enum ExtensionErrors {
  E_METHOD_NO_ERROR = 0,
  E_METHOD_NOT_SUPPORTED,
  E_METHOD_ARGS_ERROR,
  E_METHOD_ENGINE_NOT_INITED,
  E_METHOD_ENGINE_NOT_STARTED,
  E_METHOD_ENGINE_ALREADY_STARTED,
  E_METHOD_ENGINE_INIT_FAILED,
};

class IExtensionEventNotify {
public:
  virtual ~IExtensionEventNotify() {}

  virtual void OnEvent(const char *event_name, int event_name_length,
                       const char *event_json_params,
                       int event_json_parasm_length) = 0;
};

class IExtensionMethodCallback {
public:
  virtual ~IExtensionMethodCallback(){};

  virtual void OnMethodError(int error_num, const char *err_msg,
                             int err_msg_length) = 0;

  virtual void OnMethodSucceed(const char *json_ret, int json_ret_length) = 0;
};

class IExtension {
public:
  IExtension() {}
  virtual ~IExtension() {}

  virtual int Init(IExtensionManager *manager,
                   IExtensionEventNotify *event_notify) = 0;
  virtual int Uninit() = 0;

  virtual int CallMethod(const char *method_name, int method_name_length,
                         const char *json_args, int json_args_length,
                         IExtensionMethodCallback *call_back) = 0;
};

} // namespace extension
} // namespace owcr
#endif
