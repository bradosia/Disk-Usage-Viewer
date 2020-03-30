/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

// local project
#include "Filesystem.hpp"

namespace FSDB {
namespace filesystem {

void traverse(
    boost::filesystem::path pathInitial,
    std::shared_ptr<std::unordered_map<std::wstring, bool>> visitedPtr) {
  std::queue<boost::filesystem::path> directoryQueue;
  directoryQueue.push(pathInitial);
  while (!directoryQueue.empty()) {
    try {
      for (auto &p : boost::filesystem::directory_iterator(
               directoryQueue.front(),
               boost::filesystem::directory_options::skip_permission_denied)) {
        if (boost::filesystem::is_directory(p)) {
          directoryQueue.push(p);
        }
        visitedPtr->insert({p.path().wstring(), false});
#if TRAVERSE_DEBUG
        std::cout << p.path() << "\n";
#endif
      }
    } catch (const std::exception &e) {
#if TRAVERSE_DEBUG
      std::cout << e.what() << "\n";
#endif
    }
    directoryQueue.pop();
  }
}

} // namespace filesystem
} // namespace FSDB
