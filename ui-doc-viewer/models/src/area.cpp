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

area::area_t Area::set_area_struct(const area::area_t &area_struct) {
    if (!area_struct.read_only) {
        _area_struct.dimension = area_struct.dimension.was_set ? area_struct.dimension : _area_struct.dimension;
        _area_struct.actions =
                area_struct.actions == area::Actions::TRANSIENT ? _area_struct.actions : area_struct.actions;
        _area_struct.type = area_struct.type == area::Type::TRANSIENT ? _area_struct.type : area_struct.type;
        _area_struct.page = area_struct.page == 0 ? _area_struct.page : area_struct.page;
        _area_struct.name = area_struct.name.empty() ? _area_struct.name : area_struct.name;
    }
    return _area_struct;
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

bool AreaGroup::update_area_struct(const QString &area_uuid, area::area_t &area_struct) {
    auto *area = areas_map.value(area_uuid, nullptr);
    if (area) {
        area_struct = area->set_area_struct(area_struct);
        return true;
    }

    return false;
}

//-------------------------------------
