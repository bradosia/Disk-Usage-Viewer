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
sudo apt-get install qt5-default libboost-all-dev sqlite3
```

Build
```shell
git clone https://github.com/bradosia/Disk-Usage-Viewer/
cd Disk-Usage-Viewer
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
```

## Windows - MSYS + MinGW

Get Dependencies
```shell
pacman -S mingw-w64-x86_64-qt5 
```

Build
```shell
git clone https://github.com/bradosia/Disk-Usage-Viewer/
cd Disk-Usage-Viewer
mkdir build
cd build
cmake -G "MSYS Makefiles" ..
make
```

## Windows - MSVC

Get Dependencies (untested)
```shell
nuget install QtCore boost sqlite
```

## MacOS

Get Dependencies (untested)
```shell
brew install qt boost sqlite
```

Build (untested)
```shell
git clone https://github.com/bradosia/Disk-Usage-Viewer/
cd Disk-Usage-Viewer
mkdir build
cd build
cmake -G "Xcode" ..
xcodebuild -list -project <NAME>.xcodeproj/
xcodebuild -scheme <SCHEME NAME> build
```
