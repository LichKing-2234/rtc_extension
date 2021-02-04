#include "main_entry.h"

#include "extension_impl.h"

int GetIExtension(void **pptr) {
  *pptr = (void *)ExtensionImpl::GetGlobalExtension();
  return 0;
}
