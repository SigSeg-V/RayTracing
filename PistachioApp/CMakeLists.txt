cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(PistachioApp)

set(CMAKE_CXX_STANDARD 26)

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(glm CONFIG REQUIRED)

find_package(Vulkan) # CMake 3.21+

if (WIN32)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(SUBSYSTEM "CONSOLE")
    else()
        set(SUBSYSTEM "WINDOWS")
    endif()

    set(SUBSYSTEM_LINKER_OPTIONS "/SUBSYSTEM:${SUBSYSTEM} /ENTRY:mainCRTStartup")
else()
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(SUBSYSTEM_LINKER_OPTIONS "-mwindows")
    else()
        set(SUBSYSTEM_LINKER_OPTIONS "")
    endif()
endif()

# remove console window on release mode
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SUBSYSTEM_LINKER_OPTIONS}")

add_executable(PistachioApp
        Source/Private/PistachioApp.cpp
)

message(STATUS "${CMAKE_SOURCE_DIR}/Vendor/Pistachio/Source/Public")
message(STATUS "${PROJECT_SOURCE_DIR}/Vendor/Pistachio/Source/Public")

include_directories(${CMAKE_SOURCE_DIR}/Vendor/Pistachio/Source/Public ${Stb_INCLUDE_DIR})
target_link_libraries(PistachioApp Pistachio imgui::imgui glm::glm Vulkan::Vulkan)

install(TARGETS PistachioApp RUNTIME DESTINATION bin)
