#pragma once

#if defined(__APPLE__)
#include <rtc_sdk/IRTCEngine.h>
#else
#include "IRTCEngine.h"
#endif
#include "extension_context.h"
#include "public/iextension_mediastream_delegate.h"
#include "public/iextension_media_listener.h"
#include <map>

namespace ems {
class DeviceManagerExtension {
public:
  typedef void (DeviceManagerExtension::*MethodHandler)(
      const std::string &, owcr::extension::IExtensionMethodCallback *);

  DeviceManagerExtension();
  virtual ~DeviceManagerExtension();
  static DeviceManagerExtension *GetInstance();
  virtual void Initialize(ExtensionContext *context);
  virtual void UnInitialize();
  void CallMethod(const std::string &method, const std::string &params,
                  owcr::extension::IExtensionMethodCallback *call_back);

protected:
  static DeviceManagerExtension *CreateDeviceManagerExtension();
  void InitHandlerMap();

public:
  void OnCallMethod_getDeviceCount(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_getCurDeviceID(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setCurDevice(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setCurDeviceID(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_getDevice(const std::string &params,
                         owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_getVolume(const std::string &params,
                         owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_setVolume(const std::string &params,
                         owcr::extension::IExtensionMethodCallback *callback);

protected:
  ExtensionContext *context_;
  std::map<std::string, MethodHandler> method_handler_map_;
  rtc::IRTCEngine *rtc_engine_;
};
} // namespace ems
