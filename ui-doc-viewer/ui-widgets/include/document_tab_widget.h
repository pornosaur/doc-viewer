//
// Created by pornosaur on 13.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_TAB_WIDGET_H
#define DOC_VIEWER_DOCUMENT_TAB_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

#include "document_renderer.h"

namespace qview {

    class DocTabWidget : public QWidget {
    private:
        QVBoxLayout *vertical_layout, *vertical_layout_content;
        QScrollArea *scroll_area_doc;
        QWidget *scroll_area_doc_content;

        DocumentRenderer *doc_renderer;


    public:
        explicit DocTabWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        ~DocTabWidget() override = default;
    };

}

#endif //DOC_VIEWER_DOCUMENT_TAB_WIDGET_H
