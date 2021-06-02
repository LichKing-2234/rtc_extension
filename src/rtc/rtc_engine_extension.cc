#include "rtc_engine_extension.h"
#include "event_notify_template.h"
#include "public/iextension_mediaapply_delegate.h"
#include "public/iextension_mediastream_delegate.h"
#include "json/json11.hpp"

#define DEFINE_CALL_METHOD(name)                                               \
  { method_handler_map_["" #name] = &RtcEngineExtension::OnCallMethod_##name; }

namespace ems {
using namespace json11;
static std::string kProviderName = "AGORA";

class RTCVideoFrameObserver : public rtc::IRTCVideoFrameObserver {
public:
  RTCVideoFrameObserver(
      owcr::extension::IExtensionMediaStreamDelegate *media_stream_dele)
      : media_stream_dele_(media_stream_dele) {}

  virtual bool
  onCaptureVideoFrame(rtc::YuvI420VideoFrame &videoFrame) override {
    auto path = std::to_string(0);
    media_stream_dele_->OnIncomingCapturedI420Data(
        kProviderName.c_str(), kProviderName.length(), path.c_str(),
        path.length(), (unsigned char *)videoFrame.yBuffer,
        (unsigned char *)videoFrame.uBuffer,
        (unsigned char *)videoFrame.vBuffer, videoFrame.yStride,
        videoFrame.uStride, videoFrame.vStride, videoFrame.width,
        videoFrame.height, 24, videoFrame.rotation, videoFrame.renderTimeMs);
    return true;
  }

  virtual bool onRenderVideoFrame(rtc::UserId uid,
                                  rtc::YuvI420VideoFrame &videoFrame) override {
    auto path = std::to_string(uid);
    media_stream_dele_->OnIncomingCapturedI420Data(
        kProviderName.c_str(), kProviderName.length(), path.c_str(),
        path.length(), (unsigned char *)videoFrame.yBuffer,
        (unsigned char *)videoFrame.uBuffer,
        (unsigned char *)videoFrame.vBuffer, videoFrame.yStride,
        videoFrame.uStride, videoFrame.vStride, videoFrame.width,
        videoFrame.height, 24, videoFrame.rotation, videoFrame.renderTimeMs);
    return true;
  }

private:
  owcr::extension::IExtensionMediaStreamDelegate *media_stream_dele_;
};

class RTCEngineEventHandler : public rtc::IRTCEngineEventHandler {
public:
  RTCEngineEventHandler(ExtensionContext *context) : context_(context) {}

  void onJoinedRoom(rtc::UserId myId, const char *room) override {
    std::string event_name = "JoinedRoom";
    Json json = Json::object{
        {"myId", (double)myId},
        {"room", room},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onLeaveRoom() override {
    std::string event_name = "LeaveRoom";
    std::string result = "";
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onClientRoleChanged(rtc::CLIENT_ROLE_TYPE oldRole,
                           rtc::CLIENT_ROLE_TYPE newRole) override {
    std::string event_name = "ClientRoleChanged";
    Json json = Json::object{
        {"oldRole", oldRole},
        {"newRole", newRole},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onUserJoined(const rtc::UserId uid) override {
    std::string event_name = "UserJoined";
    Json json = Json::object{
        {"uid", (double)uid},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onUserOffline(const rtc::UserId uid) override {
    std::string event_name = "UserOffline";
    Json json = Json::object{
        {"uid", (double)uid},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onConnectionStateChanged(rtc::RTC_CONNECTION_STATE_TYPE state,
                                const char *reason) override {
    std::string event_name = "ConnectionStateChanged";
    Json json = Json::object{
        {"state", state},
        {"reason", reason},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onLastMileQuality(rtc::NETWORK_QUALITY_TYPE quality) override {
    std::string event_name = "LastMileQuality";
    Json json = Json::object{
        {"quality", quality},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onAudioDeviceStateChanged(
      const char *deviceId, rtc::RTC_MEDIA_DEVICE_TYPE deviceType,
      rtc::RTC_MEDIA_DEVICE_STATE_TYPE deviceState) override {
    std::string event_name = "AudioDeviceStateChanged";
    Json json = Json::object{
        {"deviceId", deviceId},
        {"deviceType", deviceType},
        {"deviceState", deviceState},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onVideoDeviceStateChanged(
      const char *deviceId, rtc::RTC_MEDIA_DEVICE_TYPE deviceType,
      rtc::RTC_MEDIA_DEVICE_STATE_TYPE deviceState) override {
    std::string event_name = "VideoDeviceStateChanged";
    Json json = Json::object{
        {"deviceId", deviceId},
        {"deviceType", deviceType},
        {"deviceState", deviceState},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onFirstLocalVideoFrame(int width, int height) override {
    std::string event_name = "FirstLocalVideoFrame";
    Json json = Json::object{
        {"width", width},
        {"height", height},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onFirstLocalAudioFrame() override {
    std::string event_name = "FirstLocalAudioFrame";
    std::string result = "";
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onFirstRemoteVideoFrame(rtc::UserId uid, int width,
                               int height) override {
    std::string event_name = "FirstRemoteVideoFrame";
    Json json = Json::object{
        {"uid", (double)uid},
        {"width", width},
        {"height", height},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onFirstRemoteAudioFrame(rtc::UserId uid) override {
    std::string event_name = "FirstRemoteAudioFrame";
    Json json = Json::object{
        {"uid", (double)uid},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onUserMuteVideo(rtc::UserId userId, bool isMuting) override {
    std::string event_name = "UserMuteVideo";
    Json json = Json::object{
        {"userId", (double)userId},
        {"isMuting", isMuting},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onUserMuteAudio(rtc::UserId userId, bool isMuting) override {
    std::string event_name = "UserMuteAudio";
    Json json = Json::object{
        {"userId", (double)userId},
        {"isMuting", isMuting},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onUserEnableVideo(rtc::UserId userId, bool enabled) override {
    std::string event_name = "UserEnableVideo";
    Json json = Json::object{
        {"userId", (double)userId},
        {"enabled", enabled},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onActiveSpeaker(rtc::UserId uid) override {
    std::string event_name = "ActiveSpeaker";
    Json json = Json::object{
        {"uid", (double)uid},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onAudioVolume(rtc::UserId uid, unsigned volume) override {
    std::string event_name = "AudioVolume";
    Json json = Json::object{
        {"uid", (double)uid},
        {"volume", (double)volume},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onError(rtc::RTC_RET_CODE code, const char *msg) override {
    std::string event_name = "Error";
    Json json = Json::object{
        {"code", code}, {"msg", nullptr}, // Ұָ��
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onRTCStats(const rtc::RTCStats &stats) override {
    std::string event_name = "RTCStats";
    Json json = Json::object{
        {"stats",
         Json::object{
             {"rxAudioKBitRate", (int)stats.rxAudioKBitRate},
             {"rxAudioKBitRate", (int)stats.txAudioKBitRate},
             {"rxAudioKBitRate", (int)stats.rxVideoKBitRate},
             {"rxAudioKBitRate", (int)stats.txVideoKBitRate},
             {"rxAudioKBitRate", stats.cpuAppUsage},
             {"rxAudioKBitRate", (double)stats.duration},
             {"rxAudioKBitRate", stats.cpuTotalUsage},
             {"rxAudioKBitRate", (int)stats.txPacketLossRate},
             {"rxAudioKBitRate", (int)stats.rxPacketLossRate},
             {"rxAudioKBitRate", (double)stats.userCount},
             {"rxAudioKBitRate", stats.memoryAppUsageRatio},
             {"rxAudioKBitRate", stats.memoryTotalUsageRatio},
             {"rxAudioKBitRate", stats.memoryAppUsageInKbytes},
             {"rxAudioKBitRate", (double)stats.txBytes},
             {"rxAudioKBitRate", (double)stats.rxBytes},
             {"rxAudioKBitRate", (int)stats.lastmileDelay},
             {"gatewayRtt", stats.gatewayRtt},
         }},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onSeiTimestampArrived(rtc::UserId uid, uint64_t seiTime) override {
    std::string event_name = "SeiTimestampArrived";
    Json json = Json::object{
        {"uid", (double)uid},
        {"seiTime", (double)seiTime},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void
  onRtmpStreamingStateChanged(const char *url,
                              rtc::RTMP_STREAM_PUBLISH_STATE state,
                              rtc::RTMP_STREAM_PUBLISH_ERROR errCode) override {
    std::string event_name = "RtmpStreamingStateChanged";
    Json json = Json::object{
        {"url", url},
        {"state", state},
        {"errCode", errCode},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onStartCloudRecordStateChanged(const std::string &auth, int recordId,
                                      int state, int errorCode,
                                      const std::string &sid) override {
    std::string event_name = "StartCloudRecordStateChanged";
    Json json = Json::object{
        {"auth", auth},           {"recordId", recordId}, {"state", state},
        {"errorCode", errorCode}, {"sid", sid},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onStopCloudRecordStateChanged(const std::string &auth, int recordId,
                                     const std::string &sid, int state,
                                     int errorCode) override {
    std::string event_name = "StopCloudRecordStateChanged";
    Json json = Json::object{
        {"auth", auth},   {"recordId", recordId},   {"sid", sid},
        {"state", state}, {"errorCode", errorCode},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onHttpMetadataStateStateChanged(const std::string &streamId,
                                       int category, int state, int errorCode,
                                       const std::string &errMsg) override {
    std::string event_name = "HttpMetadataStateStateChanged";
    Json json = Json::object{
        {"streamId", streamId},   {"category", category}, {"state", state},
        {"errorCode", errorCode}, {"errMsg", errMsg},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void
  onRtmpUplinesStateChanged(const char *streamId, int state, int errCode,
                            const rtc::Stru_RtmpUplinesInfo &info) override {
    std::string event_name = "RtmpUplinesStateChanged";
    Json::array addrs(info.addrs.size());
    for (auto &item : info.addrs) {
      addrs.push_back(Json::object{
          {"addr", item.addr},
          {"direct", item.direct},
          {"nid", item.nid},
          {"loc", item.loc},
      });
    }
    Json json = Json::object{
        {"streamId", streamId},
        {"state", state},
        {"errCode", errCode},
        {"info",
         Json::object{
             {"cip", info.cip},
             {"lac", info.lac},
             {"lid", info.lid},
             {"timestamp", (double)info.timestamp},
             {"max_age", (double)info.max_age},
             {"addrs", addrs},
         }},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onRemoteAudioStateChanged(rtc::UserId uid, rtc::REMOTE_AUDIO_STATE state,
                                 rtc::REMOTE_AUDIO_STATE_REASON reason,
                                 int elapsed) override {
    std::string event_name = "RemoteAudioStateChanged";
    Json json = Json::object{
        {"uid", (double)uid},
        {"state", state},
        {"reason", reason},
        {"elapsed", elapsed},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onRemoteVideoStateChanged(rtc::UserId uid,
                                 rtc::RTC_REMOTE_VIDEO_STATE state,
                                 rtc::RTC_REMOTE_VIDEO_STATE_REASON reason,
                                 int elapsed) override {
    std::string event_name = "RemoteVideoStateChanged";
    Json json = Json::object{
        {"uid", (double)uid},
        {"state", state},
        {"reason", reason},
        {"elapsed", elapsed},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void
  onLocalVideoStateChanged(rtc::RTC_LOCAL_VIDEO_STREAM_STATE localVideoState,
                           rtc::RTC_LOCAL_VIDEO_STREAM_ERROR error) override {
    std::string event_name = "LocalVideoStateChanged";
    Json json = Json::object{
        {"localVideoState", localVideoState},
        {"error", error},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onEngineChangeNotify() override {
    std::string event_name = "EngineChangeNotify";
    std::string result = "";
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onNetworkQuality(rtc::UserId uid, int txQuality, int rxQuality) {
    std::string event_name = "NetworkQuality";
    Json json = Json::object{
        {"uid", (double)uid},
        {"txQuality", txQuality},
        {"rxQuality", rxQuality},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onVideoBufferingStateChanged(rtc::UserId uid,
                                    rtc::VIDEO_BUFFERING_STATE state,
                                    int64_t timestampInMs) override {
    std::string event_name = "VideoBufferingStateChanged";
    Json json = Json::object{
        {"uid", (double)uid},
        {"state", state},
        {"timestampInMs", (double)timestampInMs},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

  void onLocalVideoStats(const rtc::LocalVideoStats stats) {
    std::string event_name = "LocalVideoStats";
    Json json = Json::object{
        {"stats",
         Json::object{
             {"sentBitrate", stats.sentBitrate},
             {"sentFrameRate", stats.sentFrameRate},
             {"videoEncodeFps", stats.videoEncodeFps},
             {"targetBitrate", stats.targetBitrate},
             {"targetFrameRate", stats.targetFrameRate},
             {"encodedFrameWidth", stats.encodedFrameWidth},
             {"encodedFrameHeight", stats.encodedFrameHeight},
             {"captureFrameRate", stats.captureFrameRate},
         }},
    };
    std::string result = json.dump();
    context_->EventNotify()->OnEvent(event_name.c_str(), event_name.length(),
                                     result.c_str(), result.length());
  }

private:
  ExtensionContext *context_;
};

RtcEngineExtension::RtcEngineExtension()
    : context_(nullptr), manager_v1_(nullptr), manager_v2_(nullptr),
      media_stream_dele_(nullptr), media_apply_dele_(nullptr) {
  rtc_engine_ = getRtcEngineInstance();
  rtc_engine_event_handler_ = nullptr;
  rtc_video_frame_observer_ = nullptr;
}

RtcEngineExtension::~RtcEngineExtension() {
  releaseRtcEngineInstance();
  rtc_engine_ = nullptr;
  if (rtc_engine_event_handler_) {
    delete rtc_engine_event_handler_;
    rtc_engine_event_handler_ = nullptr;
  }
  if (rtc_video_frame_observer_) {
    delete rtc_video_frame_observer_;
    rtc_video_frame_observer_ = nullptr;
  }
}

void RtcEngineExtension::Initialize(ExtensionContext *context) {
  // add by jiangxinyong
  if (rtc_engine_)  {
    rtc_engine_->registerLogFunc(RtcEngineExtension::OnLogMsg);
  }
  context_ = context;
  InitHandlerMap();
  InitMedia();
  rtc_engine_event_handler_ = new RTCEngineEventHandler(context);
  rtc_engine_->registerEventHandler(rtc_engine_event_handler_);
}

void RtcEngineExtension::UnInitialize() { UninitMedia(); }

// Methods
void RtcEngineExtension::InitHandlerMap() {
  method_handler_map_.clear();
  DEFINE_CALL_METHOD(initWithToken);
  DEFINE_CALL_METHOD(joinRoom);
  DEFINE_CALL_METHOD(leaveRoom);

  DEFINE_CALL_METHOD(setClientRole);
  DEFINE_CALL_METHOD(enableLocalVideo);
  DEFINE_CALL_METHOD(enableLocalAudio);
  DEFINE_CALL_METHOD(muteLocalVideo);
  DEFINE_CALL_METHOD(muteLocalAudio);
  DEFINE_CALL_METHOD(muteRemoteVideo);
  DEFINE_CALL_METHOD(muteRemoteAudio);
  DEFINE_CALL_METHOD(muteAllRemoteVideo);
  DEFINE_CALL_METHOD(muteAllRemoteAudio);
  DEFINE_CALL_METHOD(setRemoteVolume);

  // DEFINE_CALL_METHOD(setupLocalVideo);
  DEFINE_CALL_METHOD(setLocalRenderMode);
  DEFINE_CALL_METHOD(startPreview);
  DEFINE_CALL_METHOD(stopPreview);
  // DEFINE_CALL_METHOD(setupRemoteVideo);
  DEFINE_CALL_METHOD(setRemoteRenderMode);

  DEFINE_CALL_METHOD(setVideoResolution);
  DEFINE_CALL_METHOD(setVideoBitrate);
  DEFINE_CALL_METHOD(setVideoFps);
  DEFINE_CALL_METHOD(setMirror);
  DEFINE_CALL_METHOD(setAudioRecordedParam);

  /*DEFINE_CALL_METHOD(enableExternalAudioSource);
  DEFINE_CALL_METHOD(pushExternalAudioFrame);
  DEFINE_CALL_METHOD(enableExternalVideoSource);
  DEFINE_CALL_METHOD(pushExternalVideoFrame);*/

  /*DEFINE_CALL_METHOD(registerAudioFrameObserver);
  DEFINE_CALL_METHOD(registerVideoFrameObserver);*/
  DEFINE_CALL_METHOD(getVersion);
  /*DEFINE_CALL_METHOD(registerLogFunc);
  DEFINE_CALL_METHOD(registerEventHandler);*/
  DEFINE_CALL_METHOD(enableLastmileTest);
  DEFINE_CALL_METHOD(disableLastmileTest);
  DEFINE_CALL_METHOD(enableLoopbackRecording);
  DEFINE_CALL_METHOD(initChannelToken);
  DEFINE_CALL_METHOD(setConfig);
  DEFINE_CALL_METHOD(setLogFileConfig);

  DEFINE_CALL_METHOD(sendSeiTimestamp);
  DEFINE_CALL_METHOD(getCurSeiTimestamp);
  DEFINE_CALL_METHOD(setLiveTranscoding);
  DEFINE_CALL_METHOD(addPublishStreamUrl);
  DEFINE_CALL_METHOD(removePublishStreamUrl);
  DEFINE_CALL_METHOD(setServerTimestamp);
  DEFINE_CALL_METHOD(enableAutoTimestamp);
  DEFINE_CALL_METHOD(enableContentInspect);
  DEFINE_CALL_METHOD(setAVSyncSource);
  /*DEFINE_CALL_METHOD(getNewPlayoutManager);
  DEFINE_CALL_METHOD(getNewMicManager);
  DEFINE_CALL_METHOD(getNewVideoDeviceManager);*/
  DEFINE_CALL_METHOD(adjustRecordingSignalVolume);
  DEFINE_CALL_METHOD(enableDualStreamMode);
  DEFINE_CALL_METHOD(setRemoteVideoStreamType);
  DEFINE_CALL_METHOD(adjustPlaybackSignalVolume);
  DEFINE_CALL_METHOD(setBusinessUserRole);
  DEFINE_CALL_METHOD(setContentInspectExtraConfig);
}

void RtcEngineExtension::CallMethod(
    const std::string &method, const std::string &params,
    owcr::extension::IExtensionMethodCallback *call_back) {
  if (method_handler_map_.find(method) == method_handler_map_.end()) {
    call_back->OnMethodError(owcr::extension::E_METHOD_NOT_SUPPORTED, "", 0);
    return;
  }
  DEFINE_DISPATCH_METHOD(method, params, call_back);
}

RtcEngineExtension *RtcEngineExtension::GetInstance() {
  static RtcEngineExtension *ma_extension_engine = CreateRtcEngineExtension();
  return ma_extension_engine;
}

RtcEngineExtension *RtcEngineExtension::CreateRtcEngineExtension() {
  return new RtcEngineExtension();
}

int RtcEngineExtension::InitMedia() {
  if (context_->Manager()->QueryInterface(owcr::extension::IEM_V_1,
                                          (void **)&manager_v1_)) {
    if (manager_v1_) {
      media_stream_dele_ = manager_v1_->GetMediaStreamDelegate();
      if (media_stream_dele_) {
        rtc_video_frame_observer_ =
            new RTCVideoFrameObserver(media_stream_dele_);
        rtc_engine_->registerVideoFrameObserver(rtc_video_frame_observer_);
      }
    }
  } else {
    return -1;
  }
  if (context_->Manager()->QueryInterface(owcr::extension::IEM_V_2,
                                          (void **)&manager_v2_)) {
    if (manager_v2_) {
      media_apply_dele_ = manager_v2_->GetMediaApplyDelegate();
      if (media_apply_dele_) {
        media_apply_dele_->AddListener(this);
      }
    }
  } else {
    return -1;
  }
  return 0;
}

void RtcEngineExtension::UninitMedia() {
  if (media_apply_dele_) {
    media_apply_dele_->RemoveListener(this);
  }
}

int RtcEngineExtension::OnIncomingCapturedI420Data(
    const char *provider_name, int provider_name_length, const char *path,
    int path_length, const unsigned char *y_data, const unsigned char *u_data,
    const unsigned char *v_data, unsigned int y_stride, unsigned int u_stride,
    unsigned int v_stride, int frame_width, int frame_height, float frame_rate,
    int clockwise_rotation, long long timestamp, int frame_feedback_id) {
  return 0;
}

int RtcEngineExtension::OnIncomingCapturedI420Data(
    const char *provider_name, int provider_name_length, const char *path,
    int path_length, const unsigned char *data, int data_length,
    int frame_width, int frame_height, float frame_rate, int clockwise_rotation,
    long long timestamp, owcr::extension::VideoPixelFormat pixel_format,
    int frame_feedback_id) {
  return 0;
}

void RtcEngineExtension::OnCallMethod_initWithToken(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto token = json["token"].string_value();
  auto ret = rtc_engine_->initWithToken(token.c_str());
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_joinRoom(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  auto ret = rtc_engine_->joinRoom();
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_leaveRoom(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  auto ret = rtc_engine_->leaveRoom();
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setClientRole(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto roleType = json["roleType"].int_value();
  auto ret = rtc_engine_->setClientRole((rtc::CLIENT_ROLE_TYPE)roleType);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_enableLocalVideo(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto enable = json["enable"].bool_value();
  rtc_engine_->enableLocalVideo(enable);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_enableLocalAudio(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto enable = json["enable"].bool_value();
  rtc_engine_->enableLocalAudio(enable);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_muteLocalVideo(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto mute = json["mute"].bool_value();
  rtc_engine_->muteLocalVideo(mute);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_muteLocalAudio(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto mute = json["mute"].bool_value();
  rtc_engine_->muteLocalAudio(mute);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_muteRemoteVideo(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto uid = static_cast<rtc::UserId>(json["uid"].int_value());
  auto mute = json["mute"].bool_value();
  rtc_engine_->muteRemoteVideo(uid, mute);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_muteRemoteAudio(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto uid = static_cast<rtc::UserId>(json["uid"].int_value());
  auto mute = json["mute"].bool_value();
  rtc_engine_->muteRemoteAudio(uid, mute);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_muteAllRemoteVideo(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto mute = json["mute"].bool_value();
  rtc_engine_->muteAllRemoteVideo(mute);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_muteAllRemoteAudio(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto mute = json["mute"].bool_value();
  rtc_engine_->muteAllRemoteAudio(mute);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_setRemoteVolume(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto uid = static_cast<rtc::UserId>(json["uid"].int_value());
  auto volume = json["volume"].int_value();
  auto channelId = json["channelId"].string_value();
  rtc_engine_->setRemoteVolume(uid, volume, channelId.c_str());
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_setLocalRenderMode(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto mode = json["mode"].int_value();
  rtc_engine_->setLocalRenderMode((rtc::RTC_VIDEO_RENDER_MODE)mode);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_startPreview(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  rtc_engine_->startPreview();
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_stopPreview(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  rtc_engine_->stopPreview();
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_setRemoteRenderMode(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto uid = static_cast<rtc::UserId>(json["uid"].int_value());
  auto mode = json["mode"].int_value();
  rtc_engine_->setRemoteRenderMode(uid, (rtc::RTC_VIDEO_RENDER_MODE)mode);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_setVideoResolution(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto w = json["w"].int_value();
  auto h = json["h"].int_value();
  auto ret = rtc_engine_->setVideoResolution(w, h);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setMirror(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto isMirror = json["isMirror"].bool_value();
  rtc_engine_->setMirror(isMirror);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_setAudioRecordedParam(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto sampleRate = static_cast<unsigned>(json["sampleRate"].int_value());
  auto nChannel = static_cast<unsigned>(json["nChannel"].int_value());
  auto nIntervalTime = json["nIntervalTime"].int_value();
  rtc_engine_->setAudioRecordedParam(sampleRate, nChannel, nIntervalTime);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_getVersion(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  int build = 0;
  auto ret = rtc_engine_->getVersion(&build);
  auto json_ret = std::string(ret);
  callback->OnMethodSucceed(ret, json_ret.length());
}

void RtcEngineExtension::OnCallMethod_enableLastmileTest(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  auto ret = rtc_engine_->enableLastmileTest();
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_disableLastmileTest(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  auto ret = rtc_engine_->disableLastmileTest();
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_enableLoopbackRecording(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto enabled = json["enabled"].bool_value();
  auto deviceName = json["deviceName"].string_value();
  auto ret = rtc_engine_->enableLoopbackRecording(enabled, deviceName.c_str());
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_initChannelToken(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto token = json["token"].string_value();
  auto ret = rtc_engine_->initChannelToken(token.c_str());
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setConfig(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto config = json["config"].string_value();
  auto ret = rtc_engine_->setConfig(config.c_str());
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setLogFileConfig(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto path = json["path"].string_value();
  auto logSize = json["path"].int_value();
  auto ret = rtc_engine_->setLogFileConfig(path.c_str(), logSize);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_sendSeiTimestamp(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto seiTime = static_cast<unsigned>(json["seiTime"].number_value());
  auto ret = rtc_engine_->sendSeiTimestamp(seiTime);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_getCurSeiTimestamp(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  uint64_t seiTime = 0;
  auto ret = rtc_engine_->getCurSeiTimestamp(seiTime);
  if (ret) {
    auto json_ret = std::to_string(seiTime); // TODO
    callback->OnMethodSucceed(json_ret.c_str(), json_ret.length());
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setLiveTranscoding(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto json_config = json["config"];

  rtc::Stru_RtmpLiveTranscoding config;
  config.width = json_config["width"].int_value();
  config.height = json_config["height"].int_value();
  config.videoBitrate = json_config["videoBitrate"].int_value();
  config.videoFramerate = json_config["videoFramerate"].int_value();
  config.videoGop = json_config["videoGop"].int_value();
  config.backgroundColor =
      static_cast<unsigned>(json_config["backgroundColor"].int_value());

  for (auto &item : json_config["transcodingUsers"].array_items()) {
    rtc::Stru_RtmpTranscodingUser user;
    user.uid = static_cast<rtc::UserId>(item["uid"].int_value());
    user.x = item["x"].int_value();
    user.y = item["y"].int_value();
    user.width = item["width"].int_value();
    user.height = item["height"].int_value();
    user.zOrder = item["zOrder"].int_value();
    user.alpha = item["alpha"].number_value();
    user.audioChannel = item["audioChannel"].int_value();
    config.transcodingUsers.push_back(user);
  }

  auto json_watermark = json_config["watermark"];
  rtc::Stru_RtmpRtcImage watermark;
  watermark.url = json_watermark["url"].string_value().c_str();
  watermark.x = json_watermark["x"].int_value();
  watermark.y = json_watermark["y"].int_value();
  watermark.width = json_watermark["width"].int_value();
  watermark.height = json_watermark["height"].int_value();
  config.watermark = &watermark;

  auto json_backgroundImage = json_config["backgroundImage"];
  rtc::Stru_RtmpRtcImage backgroundImage;
  backgroundImage.url = json_backgroundImage["url"].string_value().c_str();
  backgroundImage.x = json_backgroundImage["x"].int_value();
  backgroundImage.y = json_backgroundImage["y"].int_value();
  backgroundImage.width = json_backgroundImage["width"].int_value();
  backgroundImage.height = json_backgroundImage["height"].int_value();
  config.backgroundImage = &backgroundImage;

  config.audioSampleRate =
      static_cast<unsigned>(json_config["audioSampleRate"].int_value());
  config.audioBitrate = json_config["audioBitrate"].int_value();
  config.audioChannels = json_config["audioChannels"].int_value();
  auto ret = rtc_engine_->setLiveTranscoding(config);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_addPublishStreamUrl(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto url = json["url"].string_value().c_str();
  auto transcodingEnabled = json["transcodingEnabled"].bool_value();
  auto ret = rtc_engine_->addPublishStreamUrl(url, transcodingEnabled);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_removePublishStreamUrl(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto url = json["url"].string_value().c_str();
  auto ret = rtc_engine_->removePublishStreamUrl(url);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setServerTimestamp(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto timestampMs = json["timestampMs"].int64_value();
  auto ret = rtc_engine_->setServerTimestamp(timestampMs);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_enableAutoTimestamp(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto enable = json["enable"].bool_value();
  auto freq = static_cast<float>(json["freq"].number_value());
  auto ret = rtc_engine_->enableAutoTimestamp(enable, freq);
  if (ret) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(rtc::RTC_FAILED, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_enableContentInspect(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto enabled = json["enabled"].bool_value();
  auto ret = rtc_engine_->enableContentInspect(enabled);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setAVSyncSource(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto channelId = json["channelId"].string_value().c_str();
  auto uid = static_cast<rtc::UserId>(json["uid"].int_value());
  auto ret = rtc_engine_->setAVSyncSource(channelId, uid);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_adjustRecordingSignalVolume(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto volume = json["volume"].int_value();
  auto ret = rtc_engine_->adjustRecordingSignalVolume(volume);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_enableDualStreamMode(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto enabled = json["enabled"].bool_value();
  auto ret = rtc_engine_->enableDualStreamMode(enabled);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setRemoteVideoStreamType(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto uid = static_cast<rtc::UserId>(json["uid"].int_value());
  auto streamType = json["streamType"].int_value();
  auto ret = rtc_engine_->setRemoteVideoStreamType(
      uid, (rtc::REMOTE_VIDEO_STREAM_TYPE)streamType);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_adjustPlaybackSignalVolume(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto volume = json["volume"].int_value();
  auto ret = rtc_engine_->adjustPlaybackSignalVolume(volume);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setBusinessUserRole(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto role = json["role"].int_value();
  auto ret = rtc_engine_->setBusinessUserRole((rtc::BUSI_USER_ROLE)role);
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setContentInspectExtraConfig(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto extInfo = json["extInfo"].string_value();
  std::vector<int> featureRate;
  for (auto &item : json["featureRate"].array_items()) {
    featureRate.push_back(item.int_value());
  }
  auto ret = rtc_engine_->setContentInspectExtraConfig(
      const_cast<char *>(extInfo.c_str()), featureRate.data(),
      featureRate.size());
  if (ret == rtc::RTC_SUCCESS) {
    callback->OnMethodSucceed("", 0);
  } else {
    callback->OnMethodError(ret, "", 0);
  }
}

void RtcEngineExtension::OnCallMethod_setVideoBitrate(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto videoBitrate = json["videoBitrate"].int_value();
  rtc_engine_->setVideoBitrate(videoBitrate);
  callback->OnMethodSucceed("", 0);
}

void RtcEngineExtension::OnCallMethod_setVideoFps(
    const std::string &params,
    owcr::extension::IExtensionMethodCallback *callback) {
  std::string error;
  auto json = Json::parse(params.c_str(), error);
  auto videoFps = static_cast<unsigned>(json["videoFps"].int_value());
  rtc_engine_->setVideoFps(videoFps);
  callback->OnMethodSucceed("", 0);
}

// add by jiangxinyong
void RtcEngineExtension::OnLogMsg(const char* msg) {
  // sdk log
  // TODO
}

} // namespace ems
