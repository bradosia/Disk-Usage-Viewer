/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifndef FSDB_FILESYSTEM_SIGNAL_CPP
#define FSDB_FILESYSTEM_SIGNAL_CPP

#include <memory>

// local project
#include "FilesystemSignalWin.hpp"

namespace FSDB {
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
    /* A DWORD is 4 bytes or 32-bits
     */
    DWORD bytesRead = 0;
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
      while (bytesRead < lpBytesReturned) {
        FILE_NOTIFY_INFORMATION *event = (FILE_NOTIFY_INFORMATION *)&buffer[bytesRead];
        if (event->FileNameLength) {
          std::shared_ptr<SignalEvent> sigEvent =
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
          (*sig)(sigEvent);
        }
        bytesRead += ((DWORD)bufferSize + event->NextEntryOffset);
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
} // namespace FSDB

#endif // FSDB_FILESYSTEM_SIGNAL_H
#endif
