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

//KNOWNFOLDERID: FOLDERID_ProgramData

void traverse(
    std::filesystem::path pathInitial,
    std::shared_ptr<std::unordered_map<std::wstring, bool>> visitedPtr);

} // namespace filesystem
} // namespace FSDB

#endif // DISK_USAGE_FILESYSTEM_H
