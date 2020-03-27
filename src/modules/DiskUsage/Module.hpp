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

#ifndef DISK_USAGE_MODULE_H
#define DISK_USAGE_MODULE_H

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
#include <utility>

// c
#include <stdio.h>
#include <stdlib.h> /* srand, rand */
#include <string.h>

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
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h> // rapidjson::ParseResult
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QString>
#include <QTreeView>

#include "Interface.hpp"
#include "UI/MainWidget.hpp"
#include "UI/TreeItem.hpp"
#include "UI/TreeModel.hpp"

/*
 * DiskUsage
 */
namespace DiskUsage {

/*
 * Plugin uses the MVC design pattern.
 * This is the controller, the view is a QT widget, and the model is the API
 * storage
 */
class ModuleExport : public ModuleInterface {
private:
  std::shared_ptr<TreeModel> treeModel;
  std::shared_ptr<QTreeView> treeView;

public:
  PluginController(QWidget *parent = nullptr) {
    treeModel = std::make_shared<TreeModel>();
    treeView = std::make_shared<QTreeView>();
    treeView->setModel(treeModel.get());
    api = std::make_shared<PiWebAPI>();
  }
  ~PluginController(){};

  void init() { printf("GREETINGS FROM DLL\n"); }
  std::shared_ptr<QWidget> getWidget() {
    std::shared_ptr<QWidget> widget = treeView;
    return widget;
  }
  void treeSetJSON(rapidjson::Value &data);
  void registerSettings(
      rapidjson::Document &pluginRequest,
      std::unordered_map<std::string, std::function<void(rapidjson::Value &)>>
          &pluginCallbackMap);
};

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT ModuleExport module;
ModuleExport module;

} // namespace DiskUsage

#endif
// end DISK_USAGE_MODULE_H
