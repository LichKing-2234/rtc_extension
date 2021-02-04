#include "extension_context.h"

bool ExtensionContext::Init(
    owcr::extension::IExtensionManager *manager,
    owcr::extension::IExtensionEventNotify *event_notify) {
  common::AutoLock lock(context_lock_);
  if (be_inited_)
    return false;
  manager_ = manager;
  event_notify_ = event_notify;
  be_inited_ = true;
  return true;
}

bool ExtensionContext::Uninit() {
  common::AutoLock lock(context_lock_);
  if (!be_inited_)
    return false;
  manager_ = 0;
  event_notify_ = 0;
  be_inited_ = false;
  return true;
}