#pragma once

#include <mutex>

namespace common
{
  class Lock {
  public:
    Lock();
    ~Lock();

    void enter();
    void leave();
  private:
      std::mutex mutex_;
  };

  class AutoLock {
  public:
    AutoLock(Lock& lock);
    ~AutoLock();

  private:
    Lock& lock_;
  };
} // namespace common
