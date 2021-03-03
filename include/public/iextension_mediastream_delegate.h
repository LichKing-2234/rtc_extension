#ifndef LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIASTREAM_DELEGATE_
#define LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIASTREAM_DELEGATE_

namespace owcr
{
namespace extension
{

class IExtension;
enum VideoPixelFormat {
  PIXEL_FORMAT_UNKNOWN = 0,  // Unknown or unspecified format value.
  PIXEL_FORMAT_I420 =
  1,  // 12bpp YUV planar 1x1 Y, 2x2 UV samples, a.k.a. YU12.

      // Note: Chrome does not actually support YVU compositing, so you probably
      // don't actually want to use this. See http://crbug.com/784627.
  PIXEL_FORMAT_YV12 = 2,  // 12bpp YVU planar 1x1 Y, 2x2 VU samples.

  PIXEL_FORMAT_I422 = 3,   // 16bpp YUV planar 1x1 Y, 2x1 UV samples.
  PIXEL_FORMAT_I420A = 4,  // 20bpp YUVA planar 1x1 Y, 2x2 UV, 1x1 A samples.
  PIXEL_FORMAT_I444 = 5,   // 24bpp YUV planar, no subsampling.
  PIXEL_FORMAT_NV12 =
  6,  // 12bpp with Y plane followed by a 2x2 interleaved UV plane.
  PIXEL_FORMAT_NV21 =
  7,  // 12bpp with Y plane followed by a 2x2 interleaved VU plane.
  PIXEL_FORMAT_UYVY =
  8,  // 16bpp interleaved 2x1 U, 1x1 Y, 2x1 V, 1x1 Y samples.
  PIXEL_FORMAT_YUY2 =
  9,  // 16bpp interleaved 1x1 Y, 2x1 U, 1x1 Y, 2x1 V samples.
  PIXEL_FORMAT_ARGB = 10,   // 32bpp ARGB, 1 plane.
  PIXEL_FORMAT_XRGB = 11,   // 24bpp XRGB, 1 plane.
  PIXEL_FORMAT_RGB24 = 12,  // 24bpp BGR, 1 plane.
  PIXEL_FORMAT_RGB32 = 13,  // 32bpp BGRA, 1 plane.
  PIXEL_FORMAT_MJPEG = 14,  // MJPEG compressed.
                            // MediaTek proprietary format. MT21 is similar to NV21 except the memory
                            // layout and pixel layout (swizzles). 12bpp with Y plane followed by a 2x2
                            // interleaved VU plane. Each image contains two buffers -- Y plane and VU
                            // plane. Two planes can be non-contiguous in memory. The starting addresses
                            // of Y plane and VU plane are 4KB alignment.
                            // Suppose image dimension is (width, height). For both Y plane and VU plane:
                            // Row pitch = ((width+15)/16) * 16.
                            // Plane size = Row pitch * (((height+31)/32)*32)
  PIXEL_FORMAT_MT21 = 15,

  // The P* in the formats below designates the number of bits per pixel. I.e.
  // P9 is 9-bits per pixel, P10 is 10-bits per pixel, etc.
  PIXEL_FORMAT_YUV420P9 = 16,
  PIXEL_FORMAT_YUV420P10 = 17,
  PIXEL_FORMAT_YUV422P9 = 18,
  PIXEL_FORMAT_YUV422P10 = 19,
  PIXEL_FORMAT_YUV444P9 = 20,
  PIXEL_FORMAT_YUV444P10 = 21,
  PIXEL_FORMAT_YUV420P12 = 22,
  PIXEL_FORMAT_YUV422P12 = 23,
  PIXEL_FORMAT_YUV444P12 = 24,

  /* PIXEL_FORMAT_Y8 = 25, Deprecated */
  PIXEL_FORMAT_Y16 = 26,  // single 16bpp plane.

                          // Please update UMA histogram enumeration when adding new formats here.
  PIXEL_FORMAT_MAX =
  PIXEL_FORMAT_Y16,  // Must always be equal to largest entry logged.
};

class IExtensionMediaStreamDelegate {
public:
  IExtensionMediaStreamDelegate(){}
  virtual ~IExtensionMediaStreamDelegate() {}

  virtual int SetupProvider(
    const char* provider_name,
    int provider_name_length,
    IExtension* extension) = 0;

  virtual int OnIncomingCapturedI420Data(
    const char* provider_name,
    int provider_name_length,
    const char* path,
    int path_length,
    const unsigned char* y_data,
    const unsigned char* u_data,
    const unsigned char* v_data,
    unsigned int y_stride,
    unsigned int u_stride,
    unsigned int v_stride,
    int frame_width,
    int frame_height,
    float frame_rate,
    int clockwise_rotation,
    long long timestamp,
    int frame_feedback_id = 0) = 0;

  virtual int OnIncomingCapturedI420Data(
    const char* provider_name,
    int provider_name_length,
    const char* path,
    int path_length,
    const unsigned char* data,
    int data_length,
    int frame_width,
    int frame_height,
    float frame_rate,
    int clockwise_rotation,
    long long timestamp,
    VideoPixelFormat pixel_format,
    int frame_feedback_id = 0) = 0;

  virtual void OnError(
    const char* provider_name,
    const char* provider_name_length,
    const char* reason,
    int reason_length) = 0;
};

} // namespace extension
} // namespace owcr
#endif // LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIASTREAM_DELEGATE_
