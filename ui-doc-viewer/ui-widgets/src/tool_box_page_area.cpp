//
// Created by pornosaur on 25.7.19.
//

#include <QApplication>
#include <QString>
#include <iostream>

#include "tool_box_page_area.h"

using namespace qview;

ToolBoxPageArea::ToolBoxPageArea(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f) {
    setObjectName(QStringLiteral("page_area"));
    setMinimumSize(QSize(120, 0));
    setMaximumSize(QSize(16777215, 16777215));

    QFont font4;
    font4.setPointSize(8);

    vertical_layout_page_area = new QVBoxLayout(this);
    vertical_layout_page_area->setSpacing(0);
    vertical_layout_page_area->setObjectName(QStringLiteral("vertical_layout_page_area"));
    vertical_layout_page_area->setContentsMargins(0, 0, 0, 0);
    form_layout_area = new QFormLayout();
    form_layout_area->setObjectName(QStringLiteral("form_layout_area"));
    form_layout_area->setLabelAlignment(Qt::AlignCenter);
    form_layout_area->setHorizontalSpacing(5);
    form_layout_area->setVerticalSpacing(2);
    label_name = new QLabel(this);
    label_name->setObjectName(QStringLiteral("label_name"));
    label_name->setFont(font4);

    form_layout_area->setWidget(0, QFormLayout::LabelRole, label_name);

    line_edit_name = new QLineEdit(this);
    line_edit_name->setObjectName(QStringLiteral("line_edit_name"));
    line_edit_name->setMinimumSize(QSize(42, 20));
    line_edit_name->setMaximumSize(QSize(16777215, 20));
    line_edit_name->setFont(font4);

    form_layout_area->setWidget(0, QFormLayout::FieldRole, line_edit_name);

    label_type = new QLabel(this);
    label_type->setObjectName(QStringLiteral("label_type"));
    label_type->setFont(font4);

    form_layout_area->setWidget(1, QFormLayout::LabelRole, label_type);

    combo_box_type = new ComboBoxAreaType(this);
    combo_box_type->setObjectName(QStringLiteral("line_edit_type"));
    combo_box_type->setMinimumSize(QSize(42, 20));
    combo_box_type->setMaximumSize(QSize(16777215, 20));
    combo_box_type->setFont(font4);

    form_layout_area->setWidget(1, QFormLayout::FieldRole, combo_box_type);

    label_action = new QLabel(this);
    label_action->setObjectName(QStringLiteral("label_action"));
    label_action->setFont(font4);

    form_layout_area->setWidget(2, QFormLayout::LabelRole, label_action);

    check_box_ocr = new QCheckBox(this);
    check_box_ocr->setObjectName(QStringLiteral("check_box_ocr_prop"));
    check_box_ocr->setMaximumSize(QSize(16777215, 20));
    check_box_ocr->setFont(font4);

    form_layout_area->setWidget(2, QFormLayout::FieldRole, check_box_ocr);

    check_box_conceal = new QCheckBox(this);
    check_box_conceal->setObjectName(QStringLiteral("check_box_conceal_prop"));
    check_box_conceal->setMaximumSize(QSize(16777215, 20));
    check_box_conceal->setFont(font4);

    form_layout_area->setWidget(3, QFormLayout::FieldRole, check_box_conceal);

    check_box_extract = new QCheckBox(this);
    check_box_extract->setObjectName(QStringLiteral("check_box_extract_pro"));
    check_box_extract->setMaximumSize(QSize(16777215, 20));
    check_box_extract->setFont(font4);

    form_layout_area->setWidget(4, QFormLayout::FieldRole, check_box_extract);

    label_page = new QLabel(this);
    label_page->setObjectName(QStringLiteral("label_page"));
    label_page->setFont(font4);

    form_layout_area->setWidget(5, QFormLayout::LabelRole, label_page);

    label_page_num = new QLabel(this);
    label_page_num->setObjectName(QStringLiteral("label_page_num"));
    label_page_num->setMinimumSize(QSize(44, 0));
    label_page_num->setFont(font4);

    form_layout_area->setWidget(5, QFormLayout::FieldRole, label_page_num);

    line_separator = new QFrame(this);
    line_separator->setObjectName(QStringLiteral("line_separator"));
    line_separator->setFrameShape(QFrame::HLine);
    line_separator->setFrameShadow(QFrame::Sunken);

    form_layout_area->setWidget(6, QFormLayout::SpanningRole, line_separator);

    label_x = new QLabel(this);
    label_x->setObjectName(QStringLiteral("label_x"));
    label_x->setFont(font4);

    form_layout_area->setWidget(7, QFormLayout::LabelRole, label_x);

    line_edit_x = new QLabel(this); //new QLineEdit(this);
    line_edit_x->setObjectName(QStringLiteral("line_edit_x"));
    line_edit_x->setMinimumSize(QSize(42, 20));
    line_edit_x->setMaximumSize(QSize(16777215, 20));
    line_edit_x->setFont(font4);

    form_layout_area->setWidget(7, QFormLayout::FieldRole, line_edit_x);

    label_y = new QLabel(this);
    label_y->setObjectName(QStringLiteral("label_y"));
    label_y->setFont(font4);

    form_layout_area->setWidget(8, QFormLayout::LabelRole, label_y);

    line_edit_y = new QLabel(this);//new QLineEdit(this);
    line_edit_y->setObjectName(QStringLiteral("line_edit_y"));
    line_edit_y->setMinimumSize(QSize(42, 20));
    line_edit_y->setMaximumSize(QSize(16777215, 20));
    line_edit_y->setFont(font4);

    form_layout_area->setWidget(8, QFormLayout::FieldRole, line_edit_y);

    label_width = new QLabel(this);
    label_width->setObjectName(QStringLiteral("label_width"));
    label_width->setFont(font4);

    form_layout_area->setWidget(9, QFormLayout::LabelRole, label_width);

    line_edit_width = new QLabel(this); //new QLineEdit(this);
    line_edit_width->setObjectName(QStringLiteral("line_edit_width"));
    QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(line_edit_width->sizePolicy().hasHeightForWidth());
    line_edit_width->setSizePolicy(sizePolicy4);
    line_edit_width->setMinimumSize(QSize(42, 20));
    line_edit_width->setMaximumSize(QSize(16777215, 20));
    line_edit_width->setFont(font4);

    form_layout_area->setWidget(9, QFormLayout::FieldRole, line_edit_width);

    label_height = new QLabel(this);
    label_height->setObjectName(QStringLiteral("label_height"));
    label_height->setFont(font4);

    form_layout_area->setWidget(10, QFormLayout::LabelRole, label_height);

    line_edit_height = new QLabel(this); // new QLineEdit(this);
    line_edit_height->setObjectName(QStringLiteral("line_edit_height"));
    line_edit_height->setMinimumSize(QSize(42, 20));
    line_edit_height->setMaximumSize(QSize(16777215, 20));
    line_edit_height->setFont(font4);

    form_layout_area->setWidget(10, QFormLayout::FieldRole, line_edit_height);

    vertical_layout_page_area->addLayout(form_layout_area);

    label_name->setText(QApplication::translate("MainWindow", "Name:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
    line_edit_name->setToolTip(QApplication::translate("MainWindow", "Area name", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    label_type->setText(QApplication::translate("MainWindow", "Type:", Q_NULLPTR));
    label_action->setText(QApplication::translate("MainWindow", "Actions:", Q_NULLPTR));
    label_page->setText(QApplication::translate("MainWindow", "Page:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
    label_page_num->setToolTip(QApplication::translate("MainWindow", "Area in page", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    label_page_num->setText(QString());
    label_x->setText(QApplication::translate("MainWindow", "X:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
    line_edit_x->setToolTip(QApplication::translate("MainWindow", "Area x-axis position", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    label_y->setText(QApplication::translate("MainWindow", "Y:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
    line_edit_y->setToolTip(QApplication::translate("MainWindow", "Area y-axis position", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    label_width->setText(QApplication::translate("MainWindow", "Width:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
    line_edit_width->setToolTip(QApplication::translate("MainWindow", "Area width in px", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    label_height->setText(QApplication::translate("MainWindow", "Height:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
    line_edit_height->setToolTip(QApplication::translate("MainWindow", "Area height in px", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    check_box_ocr->setText(QApplication::translate("MainWindow", "OCR", Q_NULLPTR));
    check_box_conceal->setText(QApplication::translate("MainWindow", "Conceal", Q_NULLPTR));
    check_box_extract->setText(QApplication::translate("MainWindow", "Extract", Q_NULLPTR));
}

void
ToolBoxPageArea::update_area_properties(const QString &doc_uuid, const QString &area_uuid, const area::area_t &area) {
    line_edit_name->setText(area.name.c_str());
    combo_box_type->setCurrentIndex(static_cast<int>(area.type));
    label_page_num->setText(std::to_string(area.page).c_str());

    check_box_ocr->setChecked(area::is_action_set(area.actions, area::Actions::OCR));
    check_box_conceal->setChecked(area::is_action_set(area.actions, area::Actions::CONCEAL));
    check_box_extract->setChecked(area::is_action_set(area.actions, area::Actions::EXTRACT));

    line_edit_x->setText(std::to_string((int)area.dimension._x).c_str());
    line_edit_y->setText(std::to_string((int)area.dimension._y).c_str());
    line_edit_width->setText(std::to_string((int)area.dimension._w).c_str());
    line_edit_height->setText(std::to_string((int)area.dimension._h).c_str());

}