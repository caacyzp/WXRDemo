cmake_minimum_required(VERSION 3.5)

project(WXRDemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


LIST(APPEND CMAKE_PREFIX_PATH "C:/Users/Zepu.Yan/Qt/5.12.11/mingw73_64/lib/cmake")

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

set(PROJECT_SOURCES
main.cpp
mainwindow.cpp
reflectivetyobject.cpp
weatherobject.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/Zepu.Yan/Qt/5.12.11/mingw73_64/bin")

add_executable(WXRDemo ${PROJECT_SOURCES})


target_link_libraries(WXRDemo PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

