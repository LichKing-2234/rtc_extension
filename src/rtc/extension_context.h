#ifndef LIB_EXTENSION_CONTEXT_H_
#define LIB_EXTENSION_CONTEXT_H_

#include "common/lock.h"
#include "public/iextension.h"
#include "public/iextension_manager.h"

class ExtensionContext {
public:
  ExtensionContext() : manager_(0), event_notify_(0), be_inited_(false) {}
  virtual ~ExtensionContext() {}

  bool Init(owcr::extension::IExtensionManager *manager,
            owcr::extension::IExtensionEventNotify *event_notify);
  bool Uninit();

  owcr::extension::IExtensionManager *Manager() { return manager_; }

  owcr::extension::IExtensionEventNotify *EventNotify() {
    return event_notify_;
  }

  common::Lock &safe() { return context_lock_; }

private:
  owcr::extension::IExtensionManager *manager_;
  owcr::extension::IExtensionEventNotify *event_notify_;
  bool be_inited_;

  common::Lock context_lock_;
};

#endif // LIB_EXTENSION_CONTEXT_H_