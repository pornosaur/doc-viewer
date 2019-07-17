//
// Created by pornosaur on 13.7.19.
//

#include "document_tab_widget.h"

using namespace qview;

DocTabWidget::DocTabWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f) {
    setObjectName(QStringLiteral("doc_tab"));

    vertical_layout = new QVBoxLayout(this);
    vertical_layout->setSpacing(0);
    vertical_layout->setObjectName(QStringLiteral("vertical_layout_tab"));
    vertical_layout->setContentsMargins(0, 0, 0, 0);

    scroll_area_doc = new QScrollArea(this);
    scroll_area_doc->setObjectName(QStringLiteral("scroll_area_doc"));
    scroll_area_doc->setWidgetResizable(true);

    scroll_area_doc_content = new QWidget();
    scroll_area_doc_content->setObjectName(QStringLiteral("scroll_area_doc_content"));
    //TODO: May set static width and height while win in init.
    //scroll_area_doc_content->setGeometry(QRect(0, 0, scroll_area_doc->width(), scroll_area_doc->height()));

    vertical_layout_content = new QVBoxLayout(scroll_area_doc_content);
    vertical_layout_content->setSpacing(0);
    vertical_layout_content->setObjectName(QStringLiteral("vertical_layout_content"));
    vertical_layout_content->setContentsMargins(0, 0, 0, 0);

    doc_renderer = new DocumentRenderer(scroll_area_doc_content);
    doc_renderer->setObjectName(QStringLiteral("graphics_view_doc_renderer"));

    vertical_layout_content->addWidget(doc_renderer, Qt::AlignCenter);
    scroll_area_doc->setWidget(scroll_area_doc_content);
    vertical_layout->addWidget(scroll_area_doc, Qt::AlignCenter);
}