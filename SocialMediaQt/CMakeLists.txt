cmake_minimum_required(VERSION 3.16)
project(SocialMediaQt LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(SOURCE_FILES
    Lorem-Ipsum/main.cpp
    Lorem-Ipsum/MainWindow.cpp
    Lorem-Ipsum/MainWindow.h
    Lorem-Ipsum/SocialMedia.cpp
    Lorem-Ipsum/SocialMedia.h
Lorem-Ipsum/feed.cpp
    Lorem-Ipsum/feed.hpp
    Lorem-Ipsum/Notifikasi.cpp
    Lorem-Ipsum/Notifikasi.hpp
    Lorem-Ipsum/chat.cpp
    Lorem-Ipsum/chat.hpp
    Lorem-Ipsum/follow.cpp
    Lorem-Ipsum/follow.hpp
    Lorem-Ipsum/like.cpp
    Lorem-Ipsum/like.hpp
    Lorem-Ipsum/trending.cpp
    Lorem-Ipsum/trending.hpp
    Lorem-Ipsum/PostWidget.cpp
    Lorem-Ipsum/PostWidget.h
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE Lorem-Ipsum)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
