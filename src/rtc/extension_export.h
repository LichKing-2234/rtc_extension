#ifndef EXTENSION_EXPORT_H_
#define EXTENSION_EXPORT_H_

#if defined(WIN32)

#if defined(EXTENSION_IMPLEMENT)
#define EXTENSION_EXPORT __declspec(dllexport)
#else
#define EXTENSION_EXPORT __declspec(dllimport)
#endif // defined(LIB_OWCR_IMPLEMENTATION)

#else // defined(WIN32)
#if defined(EXTENSION_IMPLEMENTATION)
#define EXTENSION_EXPORT __attribute__((visibility("default")))
#else
#define EXTENSION_EXPORT5
#endif // defined(EXTENSION_IMPLEMENTATION)
#endif

#endif // OWCR_EXTENSION_EXPORT_H_
