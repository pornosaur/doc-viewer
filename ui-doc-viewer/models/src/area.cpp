//
// Created by pornosaur on 25.7.19.
//

#include <QUuid>
#include <iostream>
#include <fstream>

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

bool Area::convert2json(Json::Value &json_data) {
    json_data = Json::Value(Json::objectValue);

    json_data["name"] = _area_struct.name;
    json_data["page"] = static_cast<int>(_area_struct.page);
    json_data["type"] = _area_struct.get_type_str();
    json_data["actions"] = _area_struct.get_actions_str();
    json_data["dimension"]["x"] = _area_struct.dimension._x;
    json_data["dimension"]["y"] = _area_struct.dimension._y;
    json_data["dimension"]["w"] = _area_struct.dimension._w;
    json_data["dimension"]["h"] = _area_struct.dimension._h;

    return true;
}

area::area_t Area::convert2area(const Json::Value &json_area) {
    area::area_t area_struct = {
            false,
            json_area["name"].asString(),
            area::str_to_enum<area::Type>(json_area["type"].asString()),
            area::strs_to_enum<area::Actions>(json_area["actions"].asString()),
            {json_area["dimension"]["x"].asFloat(),
             json_area["dimension"]["y"].asFloat(),
             json_area["dimension"]["w"].asFloat(),
             json_area["dimension"]["h"].asFloat()
            },
            static_cast<size_t>(json_area["page"].asInt())
    };

    return area_struct;
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
    this->areas_map.insert(area->get_area_uuid(), area);

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

bool AreaGroup::convert2json(Json::Value &json_data) {
    json_data = Json::Value(Json::arrayValue);
    for (const auto it : areas_map) {
        Json::Value area_json;
        if (it->convert2json(area_json)) json_data.append(area_json);
    }

    return true;
}

/* Convert and save in mem */
std::vector<Area *> AreaGroup::convert2areas(Json::Value &json_data) {
    if (!json_data.isArray()) return {};

    std::vector<Area *> areas;
    for (const auto &item : json_data) {
        auto *area = create_area(Area::convert2area(item));
        areas.push_back(area);
    }

    return std::move(areas);
}

std::vector<Area *> AreaGroup::load_from_file(const QString &path, Json::Value &root) {
    root = Json::Value(Json::objectValue);

    std::ifstream stream(path.toStdString(), std::ifstream::binary);
    stream >> root;

    if (!root.isMember("areas")) return {};

    return std::move(convert2areas(root["areas"]));
}

//-------------------------------------
