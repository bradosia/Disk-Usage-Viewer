# Disk Usage Viewer

# Development & Design Architecture

## Module System
A short and non-comprehensive diagram to show how the views will interact with models through signals and slots. 
![FilesystemTreeWidget](https://github.com/bradosia/Disk-Usage-Viewer/blob/master/UML/FilesystemTreeWidget_D20200326.png)

A possible implementation for a sortable filesystem tree widget:
![FilesystemTreeWidget](https://github.com/bradosia/Disk-Usage-Viewer/blob/master/UML/FilesystemTreeWidgetVariant_D20200326.png)

# Build

## Linux - Ubuntu

Get Dependencies
```shell
sudo apt-get install qt5-default libboost-all-dev
```

Build
```shell
git clone https://github.com/bradosia/Disk-Usage-Viewer/
cd Disk-Usage-Viewer
mkdir build
cd build
cmake -G "Unix Makefiles" ..
```
