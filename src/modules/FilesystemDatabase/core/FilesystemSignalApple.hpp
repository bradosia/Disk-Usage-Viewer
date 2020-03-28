/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

#ifndef FSDB_FILESYSTEM_SIGNAL_NATIVE_H
#define FSDB_FILESYSTEM_SIGNAL_NATIVE_H

// C++
#include <thread>
#include <unordered_map>

// Boost
#include <boost/signals2.hpp>

// Local Project
#include "FilesystemSignalBase.hpp"

#define INOTIFY_EVENT_SIZE  ( sizeof (struct inotify_event) )
#define INOTIFY_EVENT_BUF_LEN     ( 1024 * ( INOTIFY_EVENT_SIZE + 16 ) )

namespace FSDB {
namespace filesystem {

/* FSDB::filesystem::SignalNative class
 *
 * determine the event change similar to:
 * POSIX: read(fd, buffer, EVENT_BUF_LEN);
 * WINAPI: WaitForMultipleObjects(2, dwChangeHandles, FALSE, INFINITE);
 */
class Signal : SignalBase {
private:
  int fd;
  std::vector<int> wd_list;
  bool threadRunFlag = false;

public:
  Signal();
  ~Signal();
  void watch();
  void addWatch(std::wstring pathName);
};

} // namespace filesystem
} // namespace FSDBs

#endif // FSDB_FILESYSTEM_SIGNAL_NATIVE_H
