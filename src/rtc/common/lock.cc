#include "lock.h"

namespace common {
// class Lock
    Lock::Lock()
    {
        
    }
    Lock::~Lock()
    {
        
    }
    void Lock::enter()
    {
        mutex_.lock();
    }
    void Lock::leave()
    {
        mutex_.unlock();
    }

// class AutoLock
    AutoLock::AutoLock(Lock& lock) : lock_(lock) {
        lock_.enter();
    }
    AutoLock::~AutoLock() {
          lock_.leave();
    }
}
