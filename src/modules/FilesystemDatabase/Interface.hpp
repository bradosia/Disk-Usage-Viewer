/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

#ifndef FSDB_INTERFACE_H
#define FSDB_INTERFACE_H

// c++17
#include <functional>
#include <memory>
#include <unordered_map>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>

/*
 * FSDB
 */
namespace FSDB {

class ModuleInterface {
public:
  virtual void init() = 0;
  virtual void registerSettings(
      std::shared_ptr<rapidjson::Document>,
      std::shared_ptr<std::unordered_map<
          std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>) = 0;
};

} // namespace FSDB

#endif
// end FSDB_INTERFACE_H
