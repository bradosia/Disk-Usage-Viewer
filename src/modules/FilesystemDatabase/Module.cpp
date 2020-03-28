/*
 * @name Filesystem Database Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief filesystem database and utilities
 */

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/prettywriter.h>

// Local Project
#include "Module.hpp"

/*
 * FSDB
 */
namespace FSDB {

ModuleExport::ModuleExport() {}

void ModuleExport::registerSettings(
    std::shared_ptr<rapidjson::Document> moduleRequest,
    std::shared_ptr<std::unordered_map<std::string,
                                       std::function<void(std::shared_ptr<rapidjson::Document>)>>>
        moduleCallbackMap) {
  moduleRequest->SetObject();
  moduleRequest->AddMember("FilesystemDatabase", "FilesystemDatabaseCB",
                           moduleRequest->GetAllocator());
  moduleCallbackMap->insert(
      {"FilesystemDatabaseCB",
       std::bind(&ModuleExport::setSettings, this, std::placeholders::_1)});
}

void ModuleExport::setSettings(std::shared_ptr<rapidjson::Value> data) {
#if MODULE_EXPORT_SET_SETTINGS_DEBUG
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  data->Accept(writer);
  std::cout << "treeSetJSON() data:\n" << buffer.GetString() << std::endl;
#endif
}

} // namespace FSDB
