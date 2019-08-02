//
// Created by pornosaur on 13.7.19.
//

#include "document_tab_widget.h"

using namespace qview;

DocTabWidget::DocTabWidget(const QString &uuid, QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f) {
    setObjectName(QStringLiteral("doc_tab"));

    vertical_layout = new QHBoxLayout(this);
    vertical_layout->setSpacing(0);
    vertical_layout->setObjectName(QStringLiteral("vertical_layout_tab"));
    vertical_layout->setContentsMargins(0, 0, 0, 0);


    scroll_area_doc = new QScrollArea(this);
    scroll_area_doc->setObjectName(QStringLiteral("scroll_area_doc"));
    scroll_area_doc->setWidgetResizable(true);

    scroll_area_doc_content = new QWidget(scroll_area_doc);
    scroll_area_doc_content->setObjectName(QStringLiteral("scroll_area_doc_content"));

    vertical_layout_content = new QHBoxLayout(scroll_area_doc_content);
    vertical_layout_content->setSpacing(0);
    vertical_layout_content->setObjectName(QStringLiteral("vertical_layout_content"));
    vertical_layout_content->setContentsMargins(0, 0, 0, 0);

    doc_renderer = new DocumentRenderer(uuid, scroll_area_doc_content);
    doc_renderer->setObjectName(QStringLiteral("graphics_view_doc_renderer"));

    connect(doc_renderer, &DocumentRenderer::create_new_area, this, &DocTabWidget::create_new_area);
    connect(doc_renderer, &DocumentRenderer::remove_area, this, &DocTabWidget::remove_area);
    connect(doc_renderer, &DocumentRenderer::update_area_struct, this, &DocTabWidget::update_area_struct);

    vertical_layout_content->addWidget(doc_renderer, Qt::AlignHCenter);

    scroll_area_doc->setWidget(scroll_area_doc_content);
    vertical_layout->addWidget(scroll_area_doc, Qt::AlignHCenter);
}

DocTabWidget::~DocTabWidget() {
    disconnect(doc_renderer, &DocumentRenderer::create_new_area, this, &DocTabWidget::create_new_area);
    disconnect(doc_renderer, &DocumentRenderer::remove_area, this, &DocTabWidget::remove_area);
    disconnect(doc_renderer, &DocumentRenderer::update_area_struct, this, &DocTabWidget::update_area_struct);

    delete doc_renderer;
}