//
// Created by pornosaur on 25.7.19.
//

#ifndef DOC_VIEWER_AREA_H
#define DOC_VIEWER_AREA_H

#include <QUuid>
#include <iostream>
#include <jsoncpp/json/json.h>

#include "types_utils.h"

namespace qmodel {

    class Area {
    private:
        area::area_t _area_struct;

        QString _area_uuid;


    public:
        explicit Area(area::area_t area_struct, QString area_uuid = QUuid::createUuid().toString());

        inline QString get_area_uuid() const { return _area_uuid; }

        inline area::area_t get_area_struct() const { return _area_struct; }

        area::area_t set_area_struct(const area::area_t &area_struct);

        bool convert2json(Json::Value &json_data);
    };


    class AreaGroup {
    private:
        QString _doc_uuid;

        QMap<QString, Area *> areas_map;

    public:
        explicit AreaGroup(QString doc_uuid);

        ~AreaGroup();

        Area *create_area(const area::area_t &area_struct);

        QString create_area_uuid(const area::area_t &area_struct);

        void remove_area(const QString &area_uuid);

        bool update_area_struct(const QString &area_uuid, area::area_t &area_struct);

        bool convert2json(Json::Value &json_data);
    };
}

#endif //DOC_VIEWER_AREA_H
