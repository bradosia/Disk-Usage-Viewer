/*
 * @name Disk Usage Viewer
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Graphical User Interface for analyzing disk usage

 * Icons and images owned by their respective owners
 */
// C++
#include <thread>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QTreeView>

// Local Project
#include "../core/config.hpp"
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  /* UI Setup
   */
  ui = std::make_unique<Ui::main>();
  ui->setupUi(this);
  this->setObjectName("MainWindow");

  /* Load modules in another thread and let them appear as they load.
   * This will give the illusion to the user that the load time is fast.
   * A splash screen or loading bar will make the program start up seem slow.
   *
   * EDIT: can't do this because QT gives error:
   * QObject: Cannot create children for a parent that is in a different thread.
   */
  modulesLoadedNum = 0;
  modulesLoadedTotalNum = 2;
  std::thread loadModulesThread(&MainWindow::loadModules, this);
  loadModulesThread.join();

  // TODO: Thread these
  if (fileTreePaneModule) {
    fileTreePaneWidget = fileTreePaneModule->getWidget();
    // needed to prevent crashing on program exit
    centralQWidgetPtrs.push_back(fileTreePaneWidget);
  }
  filesystemDatabaseModuleLoaded();
  fileTreePaneModuleLoaded();

  // TODO: Check if widgets need to be added on paint cycles
  if (fileTreePaneModule) {
    ui->horizontalLayout->addWidget(fileTreePaneWidget.get());
    std::shared_ptr<QTreeView> treeViewWidget =
        std::dynamic_pointer_cast<QTreeView>(fileTreePaneWidget);
    treeViewWidget->expandAll();
    treeViewWidget->setColumnWidth(0, 200);
  }
}

void MainWindow::loadModules() {
#if MAIN_WINDOW_DEBUG
  std::cout << "MainWindow::loadModules() begin.\n";
#endif
  settingsManagerPtr = std::make_shared<bradosia::SettingsManager>();
  /* Module Load
   */
  moduleManagerPtr = std::make_shared<bradosia::ModuleManager>();
  moduleManagerPtr->addModuleInterface<FileTreePane::ModuleInterface>(
      "fileTreePaneModule");
  moduleManagerPtr->addModuleInterface<FSDB::ModuleInterface>(
      "filesystemDatabaseModule");
  moduleManagerPtr->loadModules("modules");
  fileTreePaneModule =
      moduleManagerPtr->getModule<FileTreePane::ModuleInterface>(
          "fileTreePaneModule");
  filesystemDatabaseModule = moduleManagerPtr->getModule<FSDB::ModuleInterface>(
      "filesystemDatabaseModule");
}

void MainWindow::fileTreePaneModuleLoaded() {
  if (fileTreePaneModule) {
    printf("FileTreePane Module Found\n");
    /* register widgets
     */
    fileTreePaneModule->init();
    /* register setting deploy
     */
    std::shared_ptr<rapidjson::Document> moduleRequest =
        std::make_shared<rapidjson::Document>();
    std::shared_ptr<std::unordered_map<
        std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>
        moduleCallbackMap = std::make_shared<std::unordered_map<
            std::string,
            std::function<void(std::shared_ptr<rapidjson::Document>)>>>();
    fileTreePaneModule->registerSettings(moduleRequest, moduleCallbackMap);
    settingsManagerPtr->merge(moduleRequest, moduleCallbackMap);
    // Did all modules load yet?
    modulesLoadedNum++;
    if (modulesLoadedNum == modulesLoadedTotalNum) {
      allModulesLoaded();
    }
  }
}

void MainWindow::filesystemDatabaseModuleLoaded() {
  if (filesystemDatabaseModule) {
    printf("FilesystemDatabase Module Found\n");
    /* register widgets
     */
    filesystemDatabaseModule->init();
    /* register setting deploy
     */
    std::shared_ptr<rapidjson::Document> moduleRequest =
        std::make_shared<rapidjson::Document>();
    std::shared_ptr<std::unordered_map<
        std::string, std::function<void(std::shared_ptr<rapidjson::Document>)>>>
        moduleCallbackMap = std::make_shared<std::unordered_map<
            std::string,
            std::function<void(std::shared_ptr<rapidjson::Document>)>>>();
    filesystemDatabaseModule->registerSettings(moduleRequest,
                                               moduleCallbackMap);
    settingsManagerPtr->merge(moduleRequest, moduleCallbackMap);
  }
  // Did all modules load yet?
  modulesLoadedNum++;
  if (modulesLoadedNum == modulesLoadedTotalNum) {
    allModulesLoaded();
  }
}

void MainWindow::allModulesLoaded() {
  /* SIGNALS AND SLOTS HOOKUP
   */
  fileTreePaneModule->getDirectorySignal->connect(std::bind(
      &FSDB::ModuleInterface::getDirectorySlot, filesystemDatabaseModule,
      std::placeholders::_1, std::placeholders::_2));
  /* Get the settings
   */
  settingsManagerPtr->deployFile(SETTINGS_FILE);
}
