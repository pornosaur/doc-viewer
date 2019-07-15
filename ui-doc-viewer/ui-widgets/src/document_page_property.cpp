//
// Created by pornosaur on 15.7.19.
//

#include "document_page_property.h"

using namespace qview;

DocPageProperty::DocPageProperty(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f) {
    setObjectName(QStringLiteral("page"));
    setGeometry(QRect(0, 0, 148, 286));

    vertical_layout_page = new QVBoxLayout(this);
    vertical_layout_page->setObjectName(QStringLiteral("vertical_layout_page"));
    vertical_layout_page->setContentsMargins(0, 0, 0, 0);
}