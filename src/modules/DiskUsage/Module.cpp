/*
 * @name UC Davis PI Web API Browser
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Browser for UC Davis PI Web API data.
 *
 * Data from OSIsoft and UC Davis
 * Icons and images owned by their respective owners
 */

/*
 * piwebapi-ucdavis 1.0
 */
#include "Module.hpp"


/*
 * DiskUsage
 */
namespace DiskUsage {

void ModuleExport::treeSetJSON(rapidjson::Value &data) {
#if PLUGIN_DEBUG
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  data.Accept(writer);
  std::cout << "treeSetJSON() data:\n" << buffer.GetString() << std::endl;
#endif
  treeModel->addData(data);
  treeView->update();
}

void ModuleExport::registerSettings(
    rapidjson::Document &pluginRequest,
    std::unordered_map<std::string, std::function<void(rapidjson::Value &)>>
        &pluginCallbackMap) {
  pluginRequest.SetObject();
  pluginRequest.AddMember("treeData", "treeSet", pluginRequest.GetAllocator());
  pluginCallbackMap.insert({"treeSet", std::bind(&ModuleExport::treeSetJSON,
                                                 this, std::placeholders::_1)});
#if SETTINGS_DEBUG
  std::cout << "Plugin Callback Map:\n";
  for (auto pairs : pluginCallbackMap) {
    std::cout << "first:" << pairs.first << std::endl;
  }
#endif
}

} // namespace DiskUsage
