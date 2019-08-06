//
// Created by pornosaur on 6.8.19.
//

#include <QApplication>

#include "group_box_area_actions.h"


using namespace qview;

GroupBoxAreaActions::GroupBoxAreaActions(QWidget *parent) : QGroupBox(parent) {
    setObjectName(QStringLiteral("group_box_area_actions"));

    QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(sizePolicy().hasHeightForWidth());

    setSizePolicy(sizePolicy2);
    setMinimumSize(QSize(0, 0));
    setMaximumSize(QSize(16777215, 16777215));

    QFont font2;
    font2.setPointSize(8);
    font2.setBold(true);
    font2.setWeight(75);

    setFont(font2);
    setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
    setFlat(false);

    grid_layout = new QGridLayout(this);
    grid_layout->setSpacing(0);
    grid_layout->setObjectName(QStringLiteral("gridLayout_3"));
    grid_layout->setContentsMargins(0, 0, 5, 0);

    check_box_extract = new QCheckBox(this);
    check_box_extract->setObjectName(QStringLiteral("check_box_extract"));
    check_box_extract->setMaximumSize(QSize(80, 16777215));
    QFont font3;
    font3.setBold(false);
    font3.setWeight(50);
    check_box_extract->setFont(font3);

    grid_layout->addWidget(check_box_extract, 0, 1, 1, 1);

    check_box_conceal = new QCheckBox(this);
    check_box_conceal->setObjectName(QStringLiteral("check_box_conceal"));
    check_box_conceal->setMaximumSize(QSize(80, 16777215));
    check_box_conceal->setFont(font3);

    grid_layout->addWidget(check_box_conceal, 1, 0, 1, 1);

    check_box_clipping = new QCheckBox(this);
    check_box_clipping->setObjectName(QStringLiteral("check_box_clipping"));
    check_box_clipping->setMaximumSize(QSize(80, 16777215));
    check_box_clipping->setFont(font3);
    check_box_clipping->setCheckable(false);

    grid_layout->addWidget(check_box_clipping, 1, 1, 1, 1);

    check_box_ocr = new QCheckBox(this);
    check_box_ocr->setObjectName(QStringLiteral("check_box_ocr"));
    check_box_ocr->setMaximumSize(QSize(80, 16777215));
    check_box_ocr->setFont(font3);
    check_box_ocr->setChecked(true);

    grid_layout->addWidget(check_box_ocr, 0, 0, 1, 1);

    setTitle(QApplication::translate("MainWindow", "Area actions", Q_NULLPTR));
    check_box_extract->setText(QApplication::translate("MainWindow", "Extract", Q_NULLPTR));
    check_box_conceal->setText(QApplication::translate("MainWindow", "Conceal", Q_NULLPTR));
    check_box_clipping->setText(QApplication::translate("MainWindow", "Clipping", Q_NULLPTR));
    check_box_ocr->setText(QApplication::translate("MainWindow", "OCR", Q_NULLPTR));

    set_signals_connections();
}

void GroupBoxAreaActions::set_signals_connections() {
    connect(check_box_extract, &QCheckBox::stateChanged, this, &GroupBoxAreaActions::area_actions_changed);
    connect(check_box_ocr, &QCheckBox::stateChanged, this, &GroupBoxAreaActions::area_actions_changed);
    connect(check_box_clipping, &QCheckBox::stateChanged, this, &GroupBoxAreaActions::area_actions_changed);
    connect(check_box_conceal, &QCheckBox::stateChanged, this, &GroupBoxAreaActions::area_actions_changed);
}

void GroupBoxAreaActions::area_actions_changed(int state) {
    area::tool_box_t settings;

    if (check_box_conceal->isChecked()) settings._actions |= area::Actions::CONCEAL;
    if (check_box_clipping->isChecked()) settings._actions |= area::Actions::CLIPPING;
    if (check_box_ocr->isChecked()) settings._actions |= area::Actions::OCR;
    if (check_box_extract->isChecked()) settings._actions |= area::Actions::EXTRACT;

    emit send_area_actions_changes(settings);
}