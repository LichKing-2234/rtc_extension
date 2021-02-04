#ifndef LIB_EXTENSION_IMPL_H_
#define LIB_EXTENSION_IMPL_H_

#include "device_manager_extension.h"
#include "extension_context.h"
#include "public/iextension.h"
#include "rtc_engine_extension.h"
#include <memory>
#include <string>

class ExtensionImpl : public owcr::extension::IExtension {
public:
  ExtensionImpl();
  virtual ~ExtensionImpl() {}

  static IExtension *GetGlobalExtension();

  virtual int Init(owcr::extension::IExtensionManager *manager,
                   owcr::extension::IExtensionEventNotify *event_notify);
  virtual int Uninit();

  ExtensionContext &Context() { return context_; }

  virtual int CallMethod(const char *method_name, int method_name_length,
                         const char *json_args, int json_args_length,
                         owcr::extension::IExtensionMethodCallback *call_back);

private:
  void CallEngineMethodInternal(
      const std::string method, const std::string &params,
      owcr::extension::IExtensionMethodCallback *call_back);
  ExtensionContext context_;
  std::unique_ptr<ems::RtcEngineExtension> rtc_engine_;
  std::unique_ptr<ems::DeviceManagerExtension> device_manager_;
};

#endif // LIB_EXTENSION_IMPL_H_
