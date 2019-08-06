//
// Created by pornosaur on 3.8.19.
//

#include "toolbox_controller.h"

using namespace qcontroller;

ToolBoxController::ToolBoxController() {
    current_settings._type = area::Type::TEXT;
    current_settings._actions = area::Actions::OCR;
}

void ToolBoxController::update_settings(const area::tool_box_t &settings) {
    current_settings._actions =
            settings._actions == area::Actions::TRANSIENT ? current_settings._actions : settings._actions;
    current_settings._type = settings._type == area::Type::TRANSIENT ? current_settings._type : settings._type;
}

void ToolBoxController::request_settings(const QString &doc_uuid, const area::area_t &area_struct) {
    area::area_t sarea = area_struct;
    sarea.type = current_settings._type;
    sarea.actions = current_settings._actions;

    emit send_area(doc_uuid, sarea);
}