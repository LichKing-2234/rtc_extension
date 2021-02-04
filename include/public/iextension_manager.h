#ifndef LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MANAGER_
#define LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MANAGER_

namespace owcr
{
namespace extension
{

class IExtensionNetworkDelegate;
class IExtensionMediaStreamDelegate;
class IExtensionThreadDelegate;
class IExtensionPagesDelegate;
class IExtensionApiDelegate;
class IExtensionMediaApplyDelegate;
class IExtensionInfoDelegate;
class IExtensionCurlNetworkDelegate;
class IExtensionIODelegate;
class IExtensionLogDelegate;
class IExtensionRtlogDelegate;

enum EXTENSION_MANAGER_VERSION_NUM
{
  IEM_V_1 = 1,
  IEM_V_2 = 2,
  IEM_V_3 = 3,
};

class IExtensionManager_V_1 {
public:
  IExtensionManager_V_1(){}
  virtual ~IExtensionManager_V_1() {}

  // IEM_V_1
  virtual IExtensionNetworkDelegate* GetNetworkDelegate() = 0;
  virtual IExtensionMediaStreamDelegate* GetMediaStreamDelegate() = 0;
  virtual IExtensionThreadDelegate* GetThreadDelegate() = 0;
  virtual IExtensionPagesDelegate* GetPagesDeleaget() = 0;
  virtual IExtensionPagesDelegate* GetReportDeleaget() = 0;
  virtual IExtensionApiDelegate* GetApiDelegate() = 0;
};

class IExtensionManager_V_2 {
public:
  IExtensionManager_V_2() {}
  virtual ~IExtensionManager_V_2() {}
  virtual IExtensionMediaApplyDelegate* GetMediaApplyDelegate() = 0;
};

class IExtensionManager_V_3 {
public:
  IExtensionManager_V_3() {}
  virtual ~IExtensionManager_V_3() {}
  virtual IExtensionInfoDelegate* GetInfoDelegate() = 0;
  virtual IExtensionIODelegate* GetIODelegate() = 0;
  virtual IExtensionCurlNetworkDelegate* GetCurlNetworkDelegate() = 0;
  virtual IExtensionLogDelegate* GetLogDelegate() = 0;
  virtual IExtensionRtlogDelegate* GetRtlogDelegate() = 0;
};


class IExtensionManager {
public:
  IExtensionManager(){}
  virtual ~IExtensionManager() {}

  // 输入版本号，获取对应的 IExtensionManager_V_1 接口
  virtual bool QueryInterface(EXTENSION_MANAGER_VERSION_NUM num, void** api) = 0;
};

} // namespace extension
} // namespace owcr
#endif // LIB_OWCR_EXTENSION_PUBLIC_IEXTENSION_MANAGER_
