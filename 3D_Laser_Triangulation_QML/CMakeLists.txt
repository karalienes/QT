cmake_minimum_required(VERSION 3.16)

project(3D_Laser_Triangulation_QML VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Qml Concurrent)


qt_add_executable(app3D_Laser_Triangulation_QML
    main.cpp
)

qt_add_qml_module(app3D_Laser_Triangulation_QML
    URI MyApp
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        SOURCES cameraworker.h cameraworker.cpp
        SOURCES imageprovider.h imageprovider.cpp
        SOURCES frameprovider.h frameprovider.cpp
)

# qt_add_resources(app3D_Laser_Triangulation_QML "resources"
#     PREFIX "/"
#     FILES
#         Main.qml
#     RESOURCES
#         qml/resources.qrc
# )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(app3D_Laser_Triangulation_QML PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.app3D_Laser_Triangulation_QML
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(app3D_Laser_Triangulation_QML
    PRIVATE Qt6::Quick Qt6::Concurrent Qt6::Qml
)

include(GNUInstallDirs)
install(TARGETS app3D_Laser_Triangulation_QML
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

find_package(OpenCV REQUIRED)

include_directories(/usr/local/include/opencv4)
target_link_libraries(app3D_Laser_Triangulation_QML PRIVATE     opencv_core
    opencv_imgproc
    opencv_highgui
    opencv_imgcodecs
    opencv_videoio)
