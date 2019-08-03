//
// Created by pornosaur on 3.8.19.
//

#ifndef DOC_VIEWER_TOOLBOX_CONTROLLER_H
#define DOC_VIEWER_TOOLBOX_CONTROLLER_H

#include "Observer.h"
#include "types_utils.h"

namespace qcontroller {

    class ToolBoxController : public Observer {
    Q_OBJECT

    private:
        area::tool_box_t current_settings;


    public:
        explicit ToolBoxController();

        void update(void *data) override {};

    public slots:

        void update_settings(const area::tool_box_t &settings);

        void request_settings(const QString &doc_uuid, const area::area_t &area_struct);

    signals:

        void send_area(const QString &doc_uuid, const area::area_t &area_struct);

    };

}

#endif //DOC_VIEWER_TOOLBOX_CONTROLLER_H
