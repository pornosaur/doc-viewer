cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ui-doc-viewer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(
        ui-widgets/include
        models/include
        utils/include
)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package( OpenCV REQUIRED )

set(LIBS Qt5::Core Qt5::Gui Qt5::Widgets ${OpenCV_LIBS} stdc++fs)

set(SOURCE
        # UTILS
        utils/src/Observable.cpp

        # MODELS
        models/src/document.cpp

        # CONTROLLERS


        # WIDGETS
        ui-widgets/src/mainwindow.cpp
        ui-widgets/src/document_renderer.cpp
        ui-widgets/src/document_tab_widget.cpp

        # MAIN
        main.cpp
        )

set(INCLUDE
        # UTILS
        utils/include/Observer.h
        utils/include/Observable.h

        # MODELS
        models/include/document.h

        #CONTROLLERS

        # WIDGETS
        ui-widgets/include/mainwindow.h
        ui-widgets/include/document_renderer.h
        ui-widgets/include/document_tab_widget.h

        )

set(UI  # FORE WIDGETS .ui FILES
        ui-widgets/views/mainwindow.ui
        )

qt5_wrap_ui(UI_GEN ${UI})
qt5_wrap_cpp(CPP_GEN ${INCLUDE})

add_executable(${PROJECT_NAME} ${SOURCE} ${INCLUDE} ${UI_GEN} ${CPP_GEN})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})