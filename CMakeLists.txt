# Project
project(Adsbera)

# Set output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MODULE_OUTPUT_DIRECTORY})

# Find Qt libraries
find_package(Qt5 ${QT_REQUIRED_VERSION} COMPONENTS Gui Qml REQUIRED)

# Qt plugin definition
add_definitions(-DQT_PLUGIN)

# Target
add_library(${PROJECT_NAME} MODULE "")


# Include
HEADER_DIRECTORIES(INCLUDES "src")
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

# Sources
file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# Create translations QRC file
file(GLOB TS_FILES "translations/*.ts")
tr_to_qrc("${CMAKE_CURRENT_BINARY_DIR}/adsbera_ts.qrc")

# Local resources
file(GLOB LOC_QRC_FILES "qml/*.qrc" "resources/*.qrc")

# Compile resources
qt5_add_resources(QRC_SOURCES ${QRC_FILES} ${LOC_QRC_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${QRC_SOURCES})

# Libraries
target_link_libraries(${PROJECT_NAME} PUBLIC kjarni Qt5::Gui Qt5::Qml)
