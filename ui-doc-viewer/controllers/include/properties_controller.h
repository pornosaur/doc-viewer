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

    public:
        PropertiesController();

        ~PropertiesController();

        void update(void *data) override {};

    public slots:

        void add_area(const QString &doc_uuid, const area::area_t &area_struct);

        void remove_area(const QString &doc_uuid, const QString &area_uuid);

        void update_area_struct(const QString &doc_uuid, const QString &area_uuid, const area::area_t &area_struct);

    signals:

        void send_area_uuid(const QString &area_uuid);
    };

}


#endif //DOC_VIEWER_PROPERTY_CONTROLLER_H
