/*
 * @name HTTP JSON
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages HTTP JSON Calls
 */

#ifndef DISK_USAGE_FILESYSTEM_H
#define DISK_USAGE_FILESYSTEM_H

// C++
#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>
#include <unordered_map>

namespace DiskUsage {
namespace filesystem {

void traverse(
    std::filesystem::path pathInitial,
    std::shared_ptr<std::unordered_map<std::wstring, bool>> visitedPtr);

} // namespace filesystem
} // namespace DiskUsage

#endif // DISK_USAGE_FILESYSTEM_H
