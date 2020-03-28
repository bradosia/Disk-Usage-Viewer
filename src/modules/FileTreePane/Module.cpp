/*
 * @name File Tree Pane Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for viewing a file tree
 */

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#include <rapidjson/prettywriter.h>

// Local Project
#include "Module.hpp"
#include "UI/MainWidget.hpp"

/*
 * FileTreePane
 */
namespace FileTreePane {

ModuleExport::ModuleExport() {}

std::shared_ptr<QWidget> ModuleExport::getWidget() {
  treeModel = std::make_shared<WidgetModel>();
  filesystemItemDelegate = std::make_shared<WidgetItemDelegate>();
  treeView = std::make_shared<MainWidget>();
  treeView->setModel(treeModel.get());
  treeView->setItemDelegateForColumn(1, filesystemItemDelegate.get());
  // move and drag and drop feature
  treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
  treeView->setDragEnabled(true);
  treeView->setAcceptDrops(true);
  treeView->setDropIndicatorShown(true);
  return treeView;
}

void ModuleExport::treeSetJSON(std::shared_ptr<rapidjson::Document> data) {
#if PLUGIN_DEBUG
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  data.Accept(writer);
  std::cout << "treeSetJSON() data:\n" << buffer.GetString() << std::endl;
#endif
  if (treeView) {
    treeModel->addData(data);
    treeView->update();
  } else {
    std::cout << "Call getWidget() first.\n" << std::endl;
  }
}

void ModuleExport::registerSettings(
    std::shared_ptr<rapidjson::Document> moduleRequest,
    std::shared_ptr<std::unordered_map<
        std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>
        moduleCallbackMap) {
  moduleRequest->SetObject();
  moduleRequest->AddMember("treeData", "treeSet",
                           moduleRequest->GetAllocator());
  moduleCallbackMap->insert(
      {"treeSet",
       std::bind(&ModuleExport::treeSetJSON, this, std::placeholders::_1)});

#if SETTINGS_DEBUG
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  moduleRequest.Accept(writer);
  std::cout << "Plugin JSON settings:\n" << buffer.GetString() << "\n";
  std::cout << "Plugin Callback Map:\n";
  for (auto pairs : pluginCallbackMap) {
    std::cout << "first:" << pairs.first << std::endl;
  }
#endif
}

} // namespace FileTreePane
