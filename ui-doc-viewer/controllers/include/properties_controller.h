//
// Created by pornosaur on 1.8.19.
//

#ifndef DOC_VIEWER_PROPERTY_CONTROLLER_H
#define DOC_VIEWER_PROPERTY_CONTROLLER_H

#include <QMap>
#include <QObject>
#include <utils/include/Observer.h>

#include "area.h"

namespace qcontroller {

    class PropertiesController : public Observer {
    Q_OBJECT

    private:
        QMap<QString, qmodel::AreaGroup *> areas_map;

        static QString current_area_uuid, current_doc_uuid;

        void _save_template(const stg::save_t &json_data);

    public:
        PropertiesController();

        ~PropertiesController();

        void update(void *data) override {};


    public slots:

        void save_template(bool checked);

        void set_current_selected_area(const QString &doc_uuid, const QString &area_uuid);

        void create_new_area(const QString &doc_uuid, const area::area_t &area_struct);

        void add_area(const QString &doc_uuid, const area::area_t &area_struct);

        void remove_area(const QString &doc_uuid, const QString &area_uuid);

        void update_area_struct(const QString &doc_uuid, const QString &area_uuid, const area::area_t &area_struct);

        void update_area_struct(const area::area_t &area_struct);



        void load_template();

        void remove_doc_template(const QString &doc_uuid);

    signals:

        void send_created_area(const QString &area_uuid, const area::area_t &area_struct);

        void send_area_uuid(const QString &area_uuid, const area::area_t &area_struct);

        void send_updated_area(const QString &area_uuid, const area::area_t &area_struct);

        void send_save_request(const stg::save_t &json_data);

    };

}


#endif //DOC_VIEWER_PROPERTY_CONTROLLER_H
