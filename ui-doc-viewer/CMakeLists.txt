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
        controllers/include
)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package( OpenCV REQUIRED )

set(LIBS Qt5::Core Qt5::Gui Qt5::Widgets ${OpenCV_LIBS} stdc++fs jsoncpp)

set(SOURCE
        # UTILS
        utils/src/Observable.cpp

        # MODELS
        models/src/document.cpp
        models/src/area.cpp

        # CONTROLLERS
        controllers/src/document_controller.cpp
        controllers/src/properties_controller.cpp
        controllers/src/toolbox_controller.cpp

        # WIDGETS
        ui-widgets/src/mainwindow.cpp
        ui-widgets/src/document_renderer.cpp
        ui-widgets/src/document_tab_widget.cpp
        ui-widgets/src/document_page_property.cpp
        ui-widgets/src/document_tab_view_widget.cpp
        ui-widgets/src/template_rect.cpp
        ui-widgets/src/pagination_widget.cpp
        ui-widgets/src/tool_box_page_area.cpp
        ui-widgets/src/combo_box_area_type.cpp
        ui-widgets/src/group_box_area_actoins.cpp

        # MAIN
        main.cpp
        )

set(INCLUDE
        # UTILS
        utils/include/Observer.h
        utils/include/Observable.h
        utils/include/types_utils.h

        # MODELS
        models/include/document.h
        models/include/area.h

        #CONTROLLERS
        controllers/include/document_controller.h
        controllers/include/properties_controller.h
        controllers/include/toolbox_controller.h

        # WIDGETS
        ui-widgets/include/mainwindow.h
        ui-widgets/include/document_renderer.h
        ui-widgets/include/document_tab_widget.h
        ui-widgets/include/document_page_property.h
        ui-widgets/include/document_tab_view_widget.h
        ui-widgets/include/template_rect.h
        ui-widgets/include/pagination_widget.h
        ui-widgets/include/tool_box_page_area.h
        ui-widgets/include/combo_box_area_type.h
        ui-widgets/include/group_box_area_actions.h

        )

set(UI  # FORE WIDGETS .ui FILES
        ui-widgets/views/mainwindow.ui
        )

qt5_wrap_ui(UI_GEN ${UI})
qt5_wrap_cpp(CPP_GEN ${INCLUDE})

file(COPY images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCE} ${INCLUDE} ${UI_GEN} ${CPP_GEN})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})