cmake_minimum_required(VERSION 3.5)

project(OSMManager LANGUAGES CXX)
set(version 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OSMManager_H ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OSMManager_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
find_path(RapidJSON_INCLUDE_DIRS rapidjson)
find_package(PROJ)

set(HDRS
    ${OSMManager_H}/root.h
    ${OSMManager_H}/node.h
    ${OSMManager_H}/way.h
    ${OSMManager_H}/relation.h
    ${OSMManager_H}/coordinatesconverter.h
    ${OSMManager_H}/utils.h
    ${OSMManager_H}/types.h
    ${OSMManager_H}/tinyxml2.h
    ${OSMManager_H}/object.h
)
set(SRCS
    ${OSMManager_SRC}/root.cpp
    ${OSMManager_SRC}/node.cpp
    ${OSMManager_SRC}/way.cpp
    ${OSMManager_SRC}/relation.cpp
    ${OSMManager_SRC}/coordinatesconverter.cpp
    ${OSMManager_SRC}/tinyxml2.cpp
    ${OSMManager_SRC}/object.cpp
)

add_library(OSMManager ${HDRS} ${SRCS})
target_include_directories(OSMManager PUBLIC $<BUILD_INTERFACE:${OSMManager_H}/> ${RapidJSON_INCLUDE_DIRS} ${PROJ_INCLUDE_DIRS})
target_link_libraries(OSMManager ${PROJ_LIBRARIES})

add_executable(OSMManager_Test ${HDRS} ${SRCS} ${OSMManager_SRC}/main.cpp)
target_include_directories(OSMManager_Test PUBLIC $<BUILD_INTERFACE:${OSMManager_H}/> ${RapidJSON_INCLUDE_DIRS} ${PROJ_INCLUDE_DIRS})
target_link_libraries(OSMManager_Test ${PROJ_LIBRARIES})

install(FILES ${HDRS} DESTINATION include/OSMManager-${version})
install(TARGETS OSMManager
        DESTINATION lib/OSMManager-${version}
        EXPORT OSMManager-targets)
install(EXPORT OSMManager-targets
        DESTINATION lib/OSMManager-${version})

configure_file(
   ${OSMManager_SOURCE_DIR}/pkg/osmmanager-config.cmake.in
   ${OSMManager_BINARY_DIR}/pkg/osmmanager-config.cmake @ONLY)

configure_file(
   ${OSMManager_SOURCE_DIR}/pkg/osmmanager-config-version.cmake.in
   ${OSMManager_BINARY_DIR}/pkg/osmmanager-config-version.cmake @ONLY)

install(FILES ${OSMManager_BINARY_DIR}/pkg/osmmanager-config.cmake
         ${OSMManager_BINARY_DIR}/pkg/osmmanager-config-version.cmake
         DESTINATION lib/OSMManager-${version})


