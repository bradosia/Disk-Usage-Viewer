/*
 * @name Disk Usage Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Disk Usage Utilities
 */

#ifndef DISK_USAGE_FILESYSTEM_SIGNAL_NATIVE_H
#define DISK_USAGE_FILESYSTEM_SIGNAL_NATIVE_H

// C++
#include <thread>
#include <unordered_map>

// WINAPI
#include <windows.h>

// Boost
#include <boost/signals2.hpp>

// Local Project
#include "FilesystemSignalBase.hpp"

namespace DiskUsage {
namespace filesystem {

/* DiskUsage::filesystem::Signal class
 *
 */
class Signal : SignalBase {
private:
  class HandleInfo {
  public:
    HANDLE fileHandle;
    bool threadRunFlag = false;
    HandleInfo(HANDLE fileHandle_, bool threadRunFlag_)
        : fileHandle(fileHandle_), threadRunFlag(threadRunFlag_){};
    ~HandleInfo(){};
  };

  std::unordered_map<HANDLE, std::shared_ptr<HandleInfo>> handleMap;
  unsigned int bufferSize;

public:
  Signal();
  ~Signal();
  void watch(HANDLE fileHandle, std::shared_ptr<HandleInfo> handleInfo);
  bool addWatch(std::wstring pathName);
};

} // namespace filesystem
} // namespace DiskUsage

#endif // DISK_USAGE_FILESYSTEM_SIGNAL_NATIVE_H
