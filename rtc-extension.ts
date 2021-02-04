export namespace RtcExtension {
  const EXT_ID = "rtc_ext";
  const VERSION = "1.0.0.0";

  declare type RetCallback = (error: number, content: string) => void
  declare type EventCallback = (event: number, data: string) => void

  declare interface Device {
    deviceId: string,
    deviceName: string
  }

  declare namespace EM {
    function Load(extensionId: string, version: string, isForce: boolean, callback: RetCallback): void;

    function UnLoad(extensionId: string, callback: RetCallback): void;

    function AddListener(extensionId: string, callback: EventCallback): number;

    function RemoverListener(extensionId: string, listenerId: number, callback: EventCallback): number;

    function CallMethod(extensionId: string, name: string, params: string, callback: RetCallback): number;
  }

  export function load() {
    EM.Load(EXT_ID, VERSION, true, (ec, content) => {
      console.log("Load EC:" + ec + "\nContent:" + content);
    });
    EM.AddListener(EXT_ID, (eventName, paramsStr) => {
      console.log("AddListener EC:" + eventName + "\nContent:" + paramsStr);
    });
  }

  export function unload() {
    EM.UnLoad(EXT_ID, (ec, content) => {
      console.log("unLoad EC:" + ec + "\nContent:" + content);
    });
  }

  export function initWithToken(token: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-initWithToken";
      const params = {token: token};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function joinRoom(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-joinRoom";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function leaveRoom(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-leaveRoom";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setClientRole(roleType: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setClientRole";
      const params = {roleType: roleType};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function enableLocalVideo(enable: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableLocalVideo";
      const params = {enable: enable};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function enableLocalAudio(enable: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableLocalAudio";
      const params = {enable: enable};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function muteLocalVideo(mute: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-muteLocalVideo";
      const params = {mute: mute};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function muteLocalAudio(mute: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-muteLocalAudio";
      const params = {mute: mute};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function muteRemoteVideo(uid: number, mute: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-muteRemoteVideo";
      const params = {uid: uid, mute: mute};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function muteRemoteAudio(uid: number, mute: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-muteRemoteAudio";
      const params = {uid: uid, mute: mute};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function muteAllRemoteVideo(mute: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-muteAllRemoteVideo";
      const params = {mute: mute};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function muteAllRemoteAudio(mute: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-muteAllRemoteAudio";
      const params = {mute: mute};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setRemoteVolume(uid: number, volume: number, channelId?: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setRemoteVolume";
      const params = {uid: uid, volume: volume, channelId: channelId};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setupLocalVideo(domId?: string): Promise<void> {
    return navigator.mediaDevices.getUserMedia({
      audio: false,
      video: {
        // @ts-ignore
        mandatory: {
          chromeMediaSource: 'external',
          chromeMediaSourceId: 'ems://AGORA/' + 0
        }
      }
    }).then((res) => {
      if (domId) {
        const video = document.getElementById(domId) as HTMLVideoElement;
        video.srcObject = res;
        return video.play();
      }
    });
  }

  export function setLocalRenderMode(mode: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setLocalRenderMode";
      const params = {mode: mode};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function startPreview(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-startPreview";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function stopPreview(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-stopPreview";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setupRemoteVideo(uid: number, domId?: string, channelId?: string): Promise<void> {
    return navigator.mediaDevices.getUserMedia({
      audio: false,
      video: {
        // @ts-ignore
        mandatory: {
          chromeMediaSource: 'external',
          chromeMediaSourceId: 'ems://AGORA/' + uid
        }
      }
    }).then((res) => {
      if (domId) {
        const video = document.getElementById(domId) as HTMLVideoElement;
        video.srcObject = res;
        return video.play();
      }
    });
  }

  export function setRemoteRenderMode(uid: number, mode: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setRemoteRenderMode";
      const params = {uid: uid, mode: mode};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setVideoResolution(w: number, h: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setVideoResolution";
      const params = {w: w, h: h};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setVideoBitrate(videoBitrate: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setVideoBitrate";
      const params = {videoBitrate: videoBitrate};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setVideoFps(videoFps: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setVideoFps";
      const params = {videoFps: videoFps};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setMirror(isMirror: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setMirror";
      const params = {isMirror: isMirror};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setAudioRecordedParam(sampleRate: number, nChannel: number, nIntervalTime: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setAudioRecordedParam";
      const params = {sampleRate: sampleRate, nChannel: nChannel, nIntervalTime: nIntervalTime};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getVersion(): Promise<string> {
    return new Promise<string>((resolve, reject) => {
      const fun_name = "engine-getVersion";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function enableLastmileTest(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableLastmileTest";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function disableLastmileTest(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableLastmileTest";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function enableLoopbackRecording(enabled: boolean, deviceName: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableLoopbackRecording";
      const params = {enabled: enabled, deviceName: deviceName};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setConfig(config: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setConfig";
      const params = {config: config};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setLogFileConfig(path: string, logSize: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setLogFileConfig";
      const params = {path: path, logSize: logSize};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function sendSeiTimestamp(seiTime: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-sendSeiTimestamp";
      const params = {seiTime: seiTime};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getCurSeiTimestamp(): Promise<number> {
    return new Promise<number>((resolve, reject) => {
      const fun_name = "engine-getCurSeiTimestamp";
      const params = {};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(+content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setLiveTranscoding(config: {}): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setLiveTranscoding";
      const params = {config: config};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function addPublishStreamUrl(url: string, transcodingEnabled: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-addPublishStreamUrl";
      const params = {url: url, transcodingEnabled: transcodingEnabled};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function removePublishStreamUrl(url: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-removePublishStreamUrl";
      const params = {url: url};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setServerTimestamp(timestampMs: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setServerTimestamp";
      const params = {timestampMs: timestampMs};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function enableAutoTimestamp(enable: boolean, freq: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableAutoTimestamp";
      const params = {enable: enable, freq: freq};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function enableContentInspect(enabled: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableContentInspect";
      const params = {enabled: enabled};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setAVSyncSource(channelId: string, uid: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setAVSyncSource";
      const params = {channelId: channelId, uid: uid};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function adjustRecordingSignalVolume(volume: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-adjustRecordingSignalVolume";
      const params = {volume: volume};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function enableDualStreamMode(enabled: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-enableDualStreamMode";
      const params = {enabled: enabled};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setRemoteVideoStreamType(uid: number, streamType: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "engine-setRemoteVideoStreamType";
      const params = {uid: uid, streamType: streamType};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getVideoDeviceCount(): Promise<number> {
    return new Promise<number>((resolve, reject) => {
      const fun_name = "device-getDeviceCount";
      const params = {deviceType: 0};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(+content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getCurVideoDeviceID(): Promise<string> {
    return new Promise<string>((resolve, reject) => {
      const fun_name = "device-getCurDeviceID";
      const params = {deviceType: 0};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setCurVideoDevice(deviceIndex: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setCurDevice";
      const params = {deviceType: 0, deviceIndex: deviceIndex};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setCurVideoDeviceID(deviceId: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setCurDeviceID";
      const params = {deviceType: 0, deviceId: deviceId};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getVideoDevice(nIndex: number): Promise<Device> {
    return new Promise<Device>((resolve, reject) => {
      const fun_name = "device-getDevice";
      const params = {deviceType: 0, nIndex: nIndex};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(JSON.parse(content));
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getPlayoutDeviceCount(): Promise<number> {
    return new Promise<number>((resolve, reject) => {
      const fun_name = "device-getDeviceCount";
      const params = {deviceType: 1};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(+content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getCurPlayoutDeviceID(): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-getCurDeviceID";
      const params = {deviceType: 1};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setCurPlayoutDevice(deviceIndex: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setCurDevice";
      const params = {deviceType: 1, deviceIndex: deviceIndex};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setCurPlayoutDeviceID(deviceId: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setCurDeviceID";
      const params = {deviceType: 1, deviceId: deviceId};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getPlayoutDevice(nIndex: number): Promise<Device> {
    return new Promise<Device>((resolve, reject) => {
      const fun_name = "device-getDevice";
      const params = {deviceType: 1, nIndex: nIndex};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(JSON.parse(content));
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getPlayoutVolume(): Promise<number> {
    return new Promise<number>((resolve, reject) => {
      const fun_name = "device-getVolume";
      const params = {deviceType: 1};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(+content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setPlayoutVolume(nVol: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setVolume";
      const params = {deviceType: 1, nVol: nVol};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getMicDeviceCount(): Promise<number> {
    return new Promise<number>((resolve, reject) => {
      const fun_name = "device-getDeviceCount";
      const params = {deviceType: 2};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(+content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getCurMicDeviceID(): Promise<string> {
    return new Promise<string>((resolve, reject) => {
      const fun_name = "device-getCurDeviceID";
      const params = {deviceType: 2};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setCurMicDevice(deviceIndex: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setCurDevice";
      const params = {deviceType: 2, deviceIndex: deviceIndex};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setCurMicDeviceID(deviceId: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setCurDeviceID";
      const params = {deviceType: 2, deviceId: deviceId};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getMicDevice(nIndex: number): Promise<Device> {
    return new Promise<Device>((resolve, reject) => {
      const fun_name = "device-getDevice";
      const params = {deviceType: 2, nIndex: nIndex};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(JSON.parse(content));
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function getMicVolume(): Promise<number> {
    return new Promise<number>((resolve, reject) => {
      const fun_name = "device-getVolume";
      const params = {deviceType: 2};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve(+content);
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }

  export function setMicVolume(nVol: number): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const fun_name = "device-setVolume";
      const params = {deviceType: 2, nVol: nVol};
      EM.CallMethod(EXT_ID, fun_name, JSON.stringify(params), (errorCode, content) => {
        if (errorCode === 0) {
          resolve();
        } else {
          reject({code: errorCode, content: content});
        }
      });
    });
  }
}
