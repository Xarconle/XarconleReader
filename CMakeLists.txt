cmake_minimum_required(VERSION 3.16)

project(XarconleReader VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Core Widgets)

qt_add_executable(appXarconleReader
    main.cpp
    ReaderBackend.h ReaderBackend.cpp
    FileProcessor.h FileProcessor.cpp
    HorizontalHistogram.h HorizontalHistogram.cpp
    HorizontalBar.h HorizontalBar.cpp
    ToolTip.h ToolTip.cpp
    Defs.h
)

qt_add_qml_module(appXarconleReader
    URI XarconleReader
    VERSION 1.0

    QML_FILES
    main.qml
    BetterButton.qml
    FileRow.qml
    OpenStartRow.qml
    PauseCancleRow.qml
    LengthRow.qml
    WelcomeText.qml
)

set_target_properties(appXarconleReader PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appXarconleReader
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appXarconleReader PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Widgets
)
