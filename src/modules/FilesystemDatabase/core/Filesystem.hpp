/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

#ifndef FSDB_FILESYSTEM_H
#define FSDB_FILESYSTEM_H

// C++
#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>
#include <unordered_map>

namespace FSDB {
namespace filesystem {

/* Idea: In windows, use the ProgramData folder to save data
 * KNOWNFOLDERID: FOLDERID_ProgramData
 * Edit: It is better to keep the data in the same folder as the binary
 * to reduce fragmenting of files for easy uninstallation
 */

void traverse(
    std::filesystem::path pathInitial,
    std::shared_ptr<std::unordered_map<std::wstring, bool>> visitedPtr);

} // namespace filesystem
} // namespace FSDB

#endif // DISK_USAGE_FILESYSTEM_H
