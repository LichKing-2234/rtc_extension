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
class RtcEngineExtension : public IExtensionMediaListener {
public:
  typedef void (RtcEngineExtension::*MethodHandler)(
      const std::string &, owcr::extension::IExtensionMethodCallback *);

  RtcEngineExtension();
  virtual ~RtcEngineExtension();
  static RtcEngineExtension *GetInstance();
  virtual void Initialize(ExtensionContext *context);
  virtual void UnInitialize();
  void CallMethod(const std::string &method, const std::string &params,
                  owcr::extension::IExtensionMethodCallback *call_back);
  virtual int OnIncomingCapturedI420Data(
      const char *provider_name, int provider_name_length, const char *path,
      int path_length, const unsigned char *y_data, const unsigned char *u_data,
      const unsigned char *v_data, unsigned int y_stride, unsigned int u_stride,
      unsigned int v_stride, int frame_width, int frame_height,
      float frame_rate, int clockwise_rotation, long long timestamp,
      int frame_feedback_id = 0) override;
  virtual int OnIncomingCapturedI420Data(
      const char *provider_name, int provider_name_length, const char *path,
      int path_length, const unsigned char *data, int data_length,
      int frame_width, int frame_height, float frame_rate,
      int clockwise_rotation, long long timestamp,
      owcr::extension::VideoPixelFormat pixel_format,
      int frame_feedback_id = 0) override;

protected:
  static RtcEngineExtension *CreateRtcEngineExtension();
  void InitHandlerMap();
  int InitMedia();
  void UninitMedia();

public:
  void OnCallMethod_initWithToken(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_joinRoom(const std::string &params,
                        owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_leaveRoom(const std::string &params,
                         owcr::extension::IExtensionMethodCallback *callback);

  void OnCallMethod_setClientRole(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_enableLocalVideo(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_enableLocalAudio(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_muteLocalVideo(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_muteLocalAudio(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_muteRemoteVideo(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_muteRemoteAudio(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_muteAllRemoteVideo(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_muteAllRemoteAudio(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setRemoteVolume(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);

  void OnCallMethod_setLocalRenderMode(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_startPreview(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_stopPreview(const std::string &params,
                           owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setRemoteRenderMode(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);

  void OnCallMethod_setVideoResolution(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setVideoBitrate(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_setVideoFps(const std::string &params,
                           owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_setMirror(const std::string &params,
                         owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setAudioRecordedParam(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);

  void
  OnCallMethod_getVersion(const std::string &params,
                          owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_enableLastmileTest(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_disableLastmileTest(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_enableLoopbackRecording(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_initChannelToken(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void
  OnCallMethod_setConfig(const std::string &params,
                         owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setLogFileConfig(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);

  void OnCallMethod_sendSeiTimestamp(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_getCurSeiTimestamp(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setLiveTranscoding(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_addPublishStreamUrl(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_removePublishStreamUrl(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setServerTimestamp(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_enableAutoTimestamp(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_enableContentInspect(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setAVSyncSource(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_adjustRecordingSignalVolume(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_enableDualStreamMode(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);
  void OnCallMethod_setRemoteVideoStreamType(
      const std::string &params,
      owcr::extension::IExtensionMethodCallback *callback);

protected:
  ExtensionContext *context_;
  std::map<std::string, MethodHandler> method_handler_map_;
  owcr::extension::IExtensionManager_V_1 *manager_v1_;
  owcr::extension::IExtensionManager_V_2 *manager_v2_;
  owcr::extension::IExtensionMediaStreamDelegate *media_stream_dele_;
  owcr::extension::IExtensionMediaApplyDelegate *media_apply_dele_;
  rtc::IRTCEngine *rtc_engine_;
  rtc::IRTCEngineEventHandler *rtc_engine_event_handler_;
  rtc::IRTCVideoFrameObserver *rtc_video_frame_observer_;
};
} // namespace ems
