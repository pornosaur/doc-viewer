//
// Created by pornosaur on 1.8.19.
//

#include <iostream>

#include "properties_controller.h"

using namespace qcontroller;

QString PropertiesController::current_area_uuid = "";
QString PropertiesController::current_doc_uuid = "";

PropertiesController::PropertiesController() {}

PropertiesController::~PropertiesController() {
    //TODO: maybe call saving to file procedure.

    qDeleteAll(areas_map);
    areas_map.clear();
}

void PropertiesController::set_current_selected_area(const QString &doc_uuid, const QString &area_uuid) {
    current_doc_uuid = doc_uuid;
    current_area_uuid = area_uuid;
}

void PropertiesController::add_area(const QString &doc_uuid, const area::area_t &area_struct) {
    qmodel::AreaGroup *area_group = areas_map.value(doc_uuid, nullptr);

    if (!area_group) {
        area_group = new qmodel::AreaGroup(doc_uuid);
        areas_map.insert(doc_uuid, area_group);
    }

    auto area_uuid = area_group->create_area_uuid(area_struct);
    if (!area_uuid.isEmpty()) set_current_selected_area(doc_uuid, area_uuid);

    emit send_area_uuid(area_uuid, area_struct);
}

void PropertiesController::remove_area(const QString &doc_uuid, const QString &area_uuid) {
    auto *area_group = areas_map.value(doc_uuid, nullptr);
    if (area_group) area_group->remove_area(area_uuid);

    set_current_selected_area("", "");
}

void PropertiesController::update_area_struct(const QString &doc_uuid, const QString &area_uuid,
                                              const area::area_t &area_struct) {
    auto *area_group = areas_map.value(doc_uuid, nullptr);

    bool updated = false;
    area::area_t _area_struct = area_struct;
    if (area_group) {
        updated = area_group->update_area_struct(area_uuid, _area_struct);
        set_current_selected_area(doc_uuid, area_uuid);
    }
    if (updated) emit send_updated_area("", _area_struct);
}

void PropertiesController::update_area_struct(const area::area_t &area_struct) {
    if (current_area_uuid.isEmpty() || current_doc_uuid.isEmpty()) return;

    update_area_struct(current_doc_uuid, current_area_uuid, area_struct);
}
