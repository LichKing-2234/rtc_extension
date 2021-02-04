#include "extension_impl.h"
#include "public/iextension.h"
#include "public/iextension_manager.h"
#include <string>

using namespace owcr::extension;
ExtensionImpl g_ma_extension_;

// Static
owcr::extension::IExtension *ExtensionImpl::GetGlobalExtension() {
  return &g_ma_extension_;
}

ExtensionImpl::ExtensionImpl() {}

int ExtensionImpl::Init(owcr::extension::IExtensionManager *manager,
                        owcr::extension::IExtensionEventNotify *event_notify) {
  if (!context_.Init(manager, event_notify))
    return -1;

  common::AutoLock auto_lock(context_.safe());
  rtc_engine_.reset(new ems::RtcEngineExtension());
  rtc_engine_->Initialize(&context_);
  device_manager_.reset(new ems::DeviceManagerExtension());
  device_manager_->Initialize(&context_);
  return 0;
}

int ExtensionImpl::Uninit() {
  if (!context_.Uninit())
    return -1;
  common::AutoLock auto_lock(context_.safe());
  if (rtc_engine_) {
    rtc_engine_->UnInitialize();
    rtc_engine_.reset();
  }
  if (device_manager_) {
    device_manager_->UnInitialize();
    device_manager_.reset();
  }
  return 0;
}

int ExtensionImpl::CallMethod(
    const char *method_name, int method_name_length, const char *json_args,
    int json_args_length,
    owcr::extension::IExtensionMethodCallback *call_back) {
  std::string method(method_name);
  std::string args(json_args);
  CallEngineMethodInternal(method, args, call_back);
  return 0;
}

void ExtensionImpl::CallEngineMethodInternal(
    const std::string method, const std::string &params,
    owcr::extension::IExtensionMethodCallback *call_back) {
  std::string prefix_engine = "engine-";
  std::string prefix_device = "device-";
  if (method.rfind(prefix_engine, 0) == 0) {
    if (!rtc_engine_) {
      call_back->OnMethodError(E_METHOD_ENGINE_NOT_STARTED, "", 0);
      return;
    }
    rtc_engine_->CallMethod(
        method.substr(prefix_engine.length(), method.length()), params,
        call_back);
  } else if (method.rfind(prefix_device, 0) == 0) {
    if (!device_manager_) {
      call_back->OnMethodError(E_METHOD_ENGINE_NOT_STARTED, "", 0);
      return;
    }
    device_manager_->CallMethod(
        method.substr(prefix_device.length(), method.length()), params,
        call_back);
  } else {
    call_back->OnMethodError(E_METHOD_ENGINE_NOT_STARTED, "", 0);
  }
}
