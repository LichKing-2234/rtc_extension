#include "device_manager_extension.h"
#include "event_notify_template.h"
#include "json/json11.hpp"

#define DEFINE_CALL_METHOD(name)                                               \
  {                                                                            \
    method_handler_map_["" #name] =                                            \
        &DeviceManagerExtension::OnCallMethod_##name;                          \
  }

namespace ems {
using namespace json11;

DeviceManagerExtension::DeviceManagerExtension() : context_(nullptr) {
  rtc_engine_ = getRtcEngineInstance();
}

DeviceManagerExtension::~DeviceManagerExtension() {
  releaseRtcEngineInstance();
  rtc_engine_ = nullptr;
}

void DeviceManagerExtension::Initialize(ExtensionContext *context) {
  context_ = context;
  InitHandlerMap();
}

void DeviceManagerExtension::UnInitialize() {}

// Methods
void DeviceManagerExtension::InitHandlerMap() {
  method_handler_map_.clear();
  DEFINE_CALL_METHOD(getDeviceCount);
  DEFINE_CALL_METHOD(getCurDeviceID);
  DEFINE_CALL_METHOD(setCurDevice);
  DEFINE_CALL_METHOD(setCurDeviceID);
  DEFINE_CALL_METHOD(getDevice);
  DEFINE_CALL_METHOD(getVolume);
  DEFINE_CALL_METHOD(setVolume);
  DEFINE_CALL_METHOD(startDeviceTest);
  DEFINE_CALL_METHOD(stopDeviceTest);
}

void DeviceManagerExtension::CallMethod(
    const std::string &method, const std::string &params,
    owcr::extension::IExtensionMethodCallback *call_back) {
  if (method_handler_map_.find(method) == method_handler_map_.end()) {
    call_back->OnMethodError(owcr::extension::E_METHOD_NOT_SUPPORTED, "", 0);
    return;
  }
  DEFINE_DISPATCH_METHOD(method, params, call_back);
}

DeviceManagerExtension *DeviceManagerExtension::GetInstance() {
  static DeviceManagerExtension *ma_extension_engine =
      CreateDeviceManagerExtension();
  return ma_extension_engine;
}

DeviceManagerExtension *DeviceManagerExtension::CreateDeviceManagerExtension() {
  return new DeviceManagerExtension();
}

void DeviceManagerExtension::OnCallMethod_getDeviceCount(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  unsigned ret = 0;
  switch (deviceType) {
  case 0: {
    ret = rtc_engine_->getNewVideoDeviceManager()->getDeviceCount();
    break;
  }
  case 1: {
    ret = rtc_engine_->getNewPlayoutManager()->getDeviceCount();
    break;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->getDeviceCount();
    break;
  }
  }
  auto json_ret = std::to_string(ret);
  callback->OnMethodSucceed(json_ret.c_str(), json_ret.length());
}

void DeviceManagerExtension::OnCallMethod_getCurDeviceID(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  char deviceId[rtc::MAX_DEVICE_ID_LENGTH];
  auto ret = false;
  switch (deviceType) {
  case 0: {
    ret = rtc_engine_->getNewVideoDeviceManager()->getCurDeviceID(deviceId);
    break;
  }
  case 1: {
    ret = rtc_engine_->getNewPlayoutManager()->getCurDeviceID(deviceId);
    break;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->getCurDeviceID(deviceId);
    break;
  }
  }
  if (ret) {
    callback->OnMethodSucceed(deviceId, rtc::MAX_DEVICE_ID_LENGTH);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void DeviceManagerExtension::OnCallMethod_setCurDevice(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  auto deviceIndex = static_cast<unsigned>(json["deviceIndex"].int_value());
  auto ret = false;
  switch (deviceType) {
  case 0: {
    ret = rtc_engine_->getNewVideoDeviceManager()->setCurDevice(deviceIndex);
    break;
  }
  case 1: {
    ret = rtc_engine_->getNewPlayoutManager()->setCurDevice(deviceIndex);
    break;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->setCurDevice(deviceIndex);
    break;
  }
  }
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void DeviceManagerExtension::OnCallMethod_setCurDeviceID(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  auto deviceId = json["deviceId"].string_value();
  auto ret = false;
  switch (deviceType) {
  case 0: {
    ret = rtc_engine_->getNewVideoDeviceManager()->setCurDeviceID(
        deviceId.c_str());
    break;
  }
  case 1: {
    ret = rtc_engine_->getNewPlayoutManager()->setCurDeviceID(deviceId.c_str());
    break;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->setCurDeviceID(deviceId.c_str());
    break;
  }
  }
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void DeviceManagerExtension::OnCallMethod_getDevice(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  auto nIndex = static_cast<unsigned>(json["nIndex"].int_value());
  char deviceName[rtc::MAX_DEVICE_ID_LENGTH];
  char deviceId[rtc::MAX_DEVICE_ID_LENGTH];
  auto ret = false;
  switch (deviceType) {
  case 0: {
    ret = rtc_engine_->getNewVideoDeviceManager()->getDevice(nIndex, deviceName,
                                                             deviceId);
    break;
  }
  case 1: {
    ret = rtc_engine_->getNewPlayoutManager()->getDevice(nIndex, deviceName,
                                                         deviceId);
    break;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->getDevice(nIndex, deviceName,
                                                     deviceId);
    break;
  }
  }
  if (ret) {
    Json json = Json::object{
        {"deviceName", deviceName},
        {"deviceId", deviceId},
    };
    std::string result = json.dump();
    callback->OnMethodSucceed(result.c_str(), result.length());
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void DeviceManagerExtension::OnCallMethod_getVolume(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  int ret = 0;
  switch (deviceType) {
  case 0: {
    callback->OnMethodError(rtc::RTC_ERR_NOT_SUPPORTED, "", 0);
    return;
  }
  case 1: {
    ret = rtc_engine_->getNewPlayoutManager()->getVolume();
    break;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->getVolume();
    break;
  }
  }
  if (ret >= 0) {
    auto json_ret = std::to_string(ret);
    callback->OnMethodSucceed(json_ret.c_str(), json_ret.length());
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void DeviceManagerExtension::OnCallMethod_setVolume(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  auto nVol = static_cast<unsigned>(json["nVol"].int_value());
  auto ret = false;
  switch (deviceType) {
  case 0: {
    callback->OnMethodError(rtc::RTC_ERR_NOT_SUPPORTED, "", 0);
    return;
  }
  case 1: {
    ret = rtc_engine_->getNewPlayoutManager()->setVolume(nVol);
    break;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->setVolume(nVol);
    break;
  }
  }
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void DeviceManagerExtension::OnCallMethod_startDeviceTest(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  int ret = 0;
  switch (deviceType) {
  case 0: {
    callback->OnMethodError(rtc::RTC_ERR_NOT_SUPPORTED, "", 0);
    return;
  }
  case 1: {
    callback->OnMethodError(rtc::RTC_ERR_NOT_SUPPORTED, "", 0);
    return;
  }
  case 2: {
    auto indicationInterval = json["indicationInterval"].int_value();
    ret = rtc_engine_->getNewMicManager()->startRecordingDeviceTest(
        indicationInterval);
    break;
  }
  }
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void DeviceManagerExtension::OnCallMethod_stopDeviceTest(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto deviceType = json["deviceType"].int_value();
  int ret = 0;
  switch (deviceType) {
  case 0: {
    callback->OnMethodError(rtc::RTC_ERR_NOT_SUPPORTED, "", 0);
    return;
  }
  case 1: {
    callback->OnMethodError(rtc::RTC_ERR_NOT_SUPPORTED, "", 0);
    return;
  }
  case 2: {
    ret = rtc_engine_->getNewMicManager()->stopRecordingDeviceTest();
    break;
  }
  }
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}
} // namespace ems
