/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

#ifndef FSDB_MODULE_H
#define FSDB_MODULE_H

// config
#include "core/config.hpp"

// c++17
//#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

/* Boost
 */
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/reader.h> // rapidjson::ParseResult
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

// Local Project
#include "Interface.hpp"
#include "core/Filesystem.hpp"
#include "core/FilesystemSignal.hpp"
#include "core/config.hpp"

/*
 * FSDB
 */
namespace FSDB {

/*
 * This widget uses the MVC design pattern.
 * This is the controller, the view is a QT widget, and the model is the API
 * storage
 */
class ModuleExport : public ModuleInterface {
private:
public:
  ModuleExport();
  ~ModuleExport(){};

  void init() { printf("Filesystem Database Module: init()\n"); }
  void
  registerSettings(std::shared_ptr<rapidjson::Document> moduleRequest,
                   std::shared_ptr<std::unordered_map<
                       std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>
                       moduleCallbackMap);
  void setSettings(std::shared_ptr<rapidjson::Value> data);
};

// Exporting `my_namespace::module` variable with alias name `module`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::module, module)`)
extern "C" BOOST_SYMBOL_EXPORT ModuleExport filesystemDatabaseModule;
ModuleExport filesystemDatabaseModule;

} // namespace FSDB

#endif
// end FSDB_MODULE_H
