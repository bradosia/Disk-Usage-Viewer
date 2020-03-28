/*
 * @name File Tree Pane Module
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief QT5 Widget for viewing a file tree
 */

#ifndef FILE_TREE_PANE_INTERFACE_H
#define FILE_TREE_PANE_INTERFACE_H

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

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QWidget>

/*
 * FileTreePane
 */
namespace FileTreePane {

class ModuleInterface {
public:
  virtual void init() = 0;
  virtual std::shared_ptr<QWidget> getWidget() = 0;
  virtual void registerSettings(
      std::shared_ptr<rapidjson::Document>,
      std::shared_ptr<std::unordered_map<std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>) = 0;
  /* Set the tree with JSON
   */
  virtual void treeSetJSON(std::shared_ptr<rapidjson::Document> data) = 0;
};

} // namespace FileTreePane

#endif
// end FILE_TREE_PANE_INTERFACE_H
