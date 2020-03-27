/*
 * @name Disk Usage Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages HTTP JSON Calls
 */

// local project
#include "Filesystem.hpp"

namespace DiskUsage {
namespace filesystem {

void traverse(
    std::filesystem::path pathInitial,
    std::shared_ptr<std::unordered_map<std::wstring, bool>> visitedPtr) {
  std::queue<std::filesystem::path> directoryQueue;
  directoryQueue.push(pathInitial);
  while (!directoryQueue.empty()) {
    try {
      for (auto &p : std::filesystem::directory_iterator(
               directoryQueue.front(),
               std::filesystem::directory_options::skip_permission_denied)) {
        if (p.is_directory()) {
          directoryQueue.push(p);
        }
        visitedPtr->insert({p.path().wstring(), false});
        // std::cout << p.path() << "\n";
      }
    } catch (const std::exception &e) {
      // std::cout << e.what() << "\n";
    }
    directoryQueue.pop();
  }
}

} // namespace filesystem
} // namespace DiskUsage
