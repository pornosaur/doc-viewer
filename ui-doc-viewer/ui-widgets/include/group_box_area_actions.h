//
// Created by pornosaur on 6.8.19.
//

#ifndef DOC_VIEWER_GROUP_BOX_AREA_ACTIONS_H
#define DOC_VIEWER_GROUP_BOX_AREA_ACTIONS_H

#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>

#include "types_utils.h"

namespace qview {

    class GroupBoxAreaActions : public QGroupBox {
    Q_OBJECT

    private:
        QGridLayout *grid_layout;
        QCheckBox *check_box_extract, *check_box_ocr, *check_box_conceal, *check_box_clipping;

        void set_signals_connections();


    public:
        explicit GroupBoxAreaActions(QWidget *parent = nullptr);

    public slots:
        void area_actions_changed(int state);

    signals:
        void send_area_actions_changes(const area::tool_box_t &settings);

    };

}

#endif //DOC_VIEWER_GROUP_BOX_AREA_ACTIONS_H
