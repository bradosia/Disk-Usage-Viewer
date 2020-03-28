/*
 * @name Disk Usage Viewer
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Graphical User Interface for analyzing disk usage

 * Icons and images owned by their respective owners
 */

#include "Application.hpp"

Application::Application(int &argc, char **argv) : QApplication(argc, argv) {
  mainWindow = std::make_unique<MainWindow>();
  mainWindow->show();
}

Application::~Application() {}
