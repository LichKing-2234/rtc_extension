#ifndef LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_DELEGATE_COMPATIBILITY_
#define LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_DELEGATE_COMPATIBILITY_

#include <string>

namespace owcr
{
	namespace extension
	{
		class IExtensionDelegateCompatibility {
		public:
			IExtensionDelegateCompatibility() {}
			virtual ~IExtensionDelegateCompatibility() {}

			// member funciton Version Compatibility
			virtual bool IsSupportFunction(const char *func_name) = 0;
		};
	} // namespace extension
} // namespace owcr
#endif // LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_DELEGATE_COMPATIBILITY_