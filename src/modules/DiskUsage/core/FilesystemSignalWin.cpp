/*
 * @name Disk Usage Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Disk Usage Utilities
 */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifndef DISK_USAGE_FILESYSTEM_SIGNAL_CPP
#define DISK_USAGE_FILESYSTEM_SIGNAL_CPP

#include <memory>

// local project
#include "FilesystemSignalWin.hpp"

namespace DiskUsage {
namespace filesystem {

Signal::Signal() { bufferSize = 1024 * sizeof(FILE_NOTIFY_INFORMATION); }

Signal::~Signal() {
  for (auto &handleIt : handleMap) {
    handleIt.second->threadRunFlag = false;
    CloseHandle(handleIt.second->fileHandle);
    handleIt.second->threadRunFlag = false;
  }
}

void Signal::watch(HANDLE fileHandle, std::shared_ptr<HandleInfo> handleInfo) {
  /* What will happen when the instance is deleted?
   */
  while (handleInfo->threadRunFlag) {
    int i = 0;
    DWORD buffer[bufferSize];
    DWORD lpBytesReturned = 0;

    // blocks until there is something to read
    bool flag = ReadDirectoryChangesW(
        fileHandle, buffer, bufferSize * 4, TRUE,
        FILE_NOTIFY_CHANGE_SECURITY | FILE_NOTIFY_CHANGE_CREATION |
            FILE_NOTIFY_CHANGE_LAST_ACCESS | FILE_NOTIFY_CHANGE_LAST_WRITE |
            FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_ATTRIBUTES |
            FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_FILE_NAME,
        &lpBytesReturned, NULL, nullptr);

    /* checking for error
     */
    if (lpBytesReturned >= 0 && handleInfo->threadRunFlag) {
      /* actually read return the list of change events happens. Here, read the
       * change event one by one and process it accordingly.
       */
      while (i < lpBytesReturned) {
        FILE_NOTIFY_INFORMATION *event = (FILE_NOTIFY_INFORMATION *)&buffer[i];
        if (event->FileNameLength) {
          std::unique_ptr<SignalEvent> sigEvent =
              std::make_unique<SignalEvent>();
          sigEvent->path = std::wstring(event->FileName, event->FileNameLength);
          if (event->Action == FILE_ACTION_ADDED) {
            sigEvent->type = signalEventType::fileCreate;
          } else if (event->Action == FILE_ACTION_REMOVED) {
            sigEvent->type = signalEventType::fileDelete;
          } else if (event->Action == FILE_ACTION_MODIFIED) {
            sigEvent->type = signalEventType::fileDataChange;
          } else if (event->Action == FILE_ACTION_RENAMED_OLD_NAME) {
            sigEvent->type = signalEventType::fileNameChange;
          } else if (event->Action == FILE_ACTION_RENAMED_NEW_NAME) {
            sigEvent->type = signalEventType::fileNameChange;
          }
          // signal
          (*sig)(std::move(sigEvent));
        }
        i += (PFILE_NOTIFY_INFORMATION)((LPBYTE)event + event->NextEntryOffset);
      }
    } else {
      // error
    }
  }
}

bool Signal::addWatch(std::wstring pathName) {
  HANDLE fileHandle =
      CreateFileW(pathName.c_str(), FILE_LIST_DIRECTORY,
                  FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL,
                  OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
  if (fileHandle == INVALID_HANDLE_VALUE) {
    return false;
  }

  std::shared_ptr<HandleInfo> handleInfo =
      std::make_shared<HandleInfo>(fileHandle, true);
  /* Each watch on a separate thread
   */
  std::shared_ptr<std::thread> watcherThread = std::make_shared<std::thread>(
      &Signal::watch, this, fileHandle, handleInfo);
  watcherThread->detach();

  handleMap.insert({fileHandle, handleInfo});
  return true;
}

} // namespace filesystem
} // namespace DiskUsage

#endif // DISK_USAGE_FILESYSTEM_SIGNAL_H
#endif
