//
// Created by pornosaur on 26.7.19.
//

#include <iostream>
#include <QMetaEnum>

#include "combo_box_area_type.h"
#include "types_utils.h"

using namespace qview;


ComboBoxAreaType::ComboBoxAreaType(QWidget *parent) : QComboBox(parent) {
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);

    setObjectName(QStringLiteral("combo_box_area_type"));
    sizePolicy1.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy1);

    QFont font1;
    font1.setPointSize(10);
    setFont(font1);

    area::Type it = area::Type::ITERATION_BEGIN;
    for (++it; it < area::Type::ITERATION_END; ++it) {
        addItem(area::enum_to_str(it), QVariant::fromValue((int)it));
    }

    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ComboBoxAreaType::changed_selected);
}

void ComboBoxAreaType::changed_selected(int idx) {

    std::cout << "CHANGE SELECTED" << itemData(idx).toInt() << std::endl;
}