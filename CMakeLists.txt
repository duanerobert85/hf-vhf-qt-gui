cmake_minimum_required(VERSION 3.16)
project(hf-vhf-qt-gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

add_executable(hf-vhf-qt-gui
    src/main.cpp
    src/ScannerWindow.cpp
    src/ScannerWindow.h
    src/PiScanClient.cpp
    src/PiScanClient.h
)

target_link_libraries(hf-vhf-qt-gui PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

# For Visual Studio
set_target_properties(hf-vhf-qt-gui PROPERTIES
    WIN32_EXECUTABLE TRUE
)
