//gm
// Created by pornosaur on 26.7.19.
//

#ifndef DOC_VIEWER_COMBO_BOX_AREA_TYPE_H
#define DOC_VIEWER_COMBO_BOX_AREA_TYPE_H

#include <QComboBox>
#include <QWidget>

#include "types_utils.h"

namespace qview {
    Q_NAMESPACE

    class ComboBoxAreaType : public QComboBox {
        Q_OBJECT
        Q_ENUM(area::Type)


    public slots:
        void changed_selected(int idx);

    public:
        explicit ComboBoxAreaType(QWidget *parent = nullptr);

    };

}

#endif //DOC_VIEWER_COMBO_BOX_AREA_TYPE_H
