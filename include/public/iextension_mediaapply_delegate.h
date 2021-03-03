#ifndef LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIAAPPLY_DELEGATE_
#define LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIAAPPLY_DELEGATE_

#include <set>
#include <mutex>

class IExtensionMediaListener;
namespace owcr
{
  namespace extension
  {
    class IExtensionMediaApplyDelegate {
    public:
      IExtensionMediaApplyDelegate() {}
      virtual ~IExtensionMediaApplyDelegate() {}

      virtual int AddListener(
          IExtensionMediaListener* listener) = 0;
      virtual int RemoveListener(
          IExtensionMediaListener* listener) = 0;

    protected:
      std::set<IExtensionMediaListener*> media_listeners_;
      std::mutex mutex_listener_;


      /*virtual void OnError(
          const char* provider_name,
          const char* provider_name_length,
          const char* reason,
          int reason_length) = 0;*/
    };

  } // namespace extension
} // namespace owcr

#endif // LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MEDIAAPPLY_DELEGATE_
