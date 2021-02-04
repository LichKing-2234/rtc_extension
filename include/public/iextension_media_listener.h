#ifndef LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIA_LISTENER_
#define LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIA_LISTENER_
#include "iextension_mediastream_delegate.h"
class IExtensionMediaListener {
public:
    IExtensionMediaListener() {}
    virtual ~IExtensionMediaListener() {}

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
        owcr::extension::VideoPixelFormat pixel_format,
        int frame_feedback_id = 0) = 0;
};


#endif // LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIA_LISTENER_