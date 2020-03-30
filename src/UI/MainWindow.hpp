/*
 * @name Disk Usage Viewer
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Graphical User Interface for analyzing disk usage

 * Icons and images owned by their respective owners
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// C++
#include <memory>

// bradosia libraries 1.0
#include <ModuleManager/ModuleManager.hpp>
#include <SettingsManager/SettingsManager.hpp>

// Modules
#include <FilesystemDatabase/Interface.hpp>
#include <FileTreePane/Interface.hpp>

// Local Project
#include "ui_main.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(){ 
      for (auto widgetPtr : centralQWidgetPtrs) {
        widgetPtr->setParent(nullptr);
      }
  };
  void loadModules();
  void fileTreePaneModuleLoaded();
  void filesystemDatabaseModuleLoaded();
  void allModulesLoaded();

private:
  unsigned int modulesLoadedNum;
  unsigned int modulesLoadedTotalNum;
  std::unique_ptr<Ui::main> ui;
  std::shared_ptr<FileTreePane::ModuleInterface> fileTreePaneModule;
  std::shared_ptr<FSDB::ModuleInterface> filesystemDatabaseModule;
  std::vector<std::shared_ptr<QWidget>> centralQWidgetPtrs;
  std::shared_ptr<bradosia::ModuleManager> moduleManagerPtr;
  std::shared_ptr<bradosia::SettingsManager> settingsManagerPtr;
  std::shared_ptr<QWidget> fileTreePaneWidget;
};
#endif // MAIN_WINDOW_H
