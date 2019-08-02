//
// Created by pornosaur on 1.8.19.
//

#include <iostream>
#include "properties_controller.h"

using namespace qcontroller;

PropertiesController::PropertiesController() {

}

PropertiesController::~PropertiesController() {
    //TODO: maybe call saving to file procedure.

    qDeleteAll(areas_map);
    areas_map.clear();
}

void PropertiesController::add_area(const QString &doc_uuid, const area::area_t &area_struct) {
    qmodel::AreaGroup *area_group = areas_map.value(doc_uuid, nullptr);

    if (!area_group) {
        area_group = new qmodel::AreaGroup(doc_uuid);
        areas_map.insert(doc_uuid, area_group);
    }

    //TODO: create AreaGroup while new tab was opened!

    auto area_uuid = area_group->create_area_uuid(area_struct);
    emit send_area_uuid(area_uuid);
}

void PropertiesController::remove_area(const QString &doc_uuid, const QString &area_uuid) {
    qmodel::AreaGroup *area_group = areas_map.value(doc_uuid, nullptr);

    if (area_group) area_group->remove_area(area_uuid);
}