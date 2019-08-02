#include <utility>

#include <utility>

#include <utility>

//
// Created by pornosaur on 25.7.19.
//

#include <QUuid>
#include <iostream>

#include "area.h"

using namespace qmodel;

//-----------AREA CLASS----------------
Area::Area(area::area_t area_struct, QString area_uuid) : _area_struct(std::move(area_struct)),
                                                          _area_uuid(std::move(area_uuid)) {

}

//-------------------------------------

//--------AREA GROUP CLASS-------------
AreaGroup::AreaGroup(QString doc_uuid) : _doc_uuid(std::move(doc_uuid)) {

}

AreaGroup::~AreaGroup() {
    qDeleteAll(areas_map);
    areas_map.clear();
}

Area *AreaGroup::create_area(const area::area_t &area_struct) {
    auto *area = new Area(area_struct);
    areas_map.insert(area->get_area_uuid(), area);

    return area;
}

QString AreaGroup::create_area_uuid(const area::area_t &area_struct) {
    auto *area = create_area(area_struct);
    return area->get_area_uuid();
}

void AreaGroup::remove_area(const QString &area_uuid) {
    auto *area = areas_map.take(area_uuid);
    delete area;
}

void AreaGroup::update_area_struct(const QString &area_uuid, const area::area_t &area_struct) {
    auto *area = areas_map.value(area_uuid, nullptr);
    if (area) area->set_area_struct(area_struct);
}

//-------------------------------------
