//
// Created by pornosaur on 13.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_TAB_WIDGET_H
#define DOC_VIEWER_DOCUMENT_TAB_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <utils/include/types_utils.h>

#include "document_renderer.h"
#include "types_utils.h"

namespace qview {

    class DocTabWidget : public QWidget {
        Q_OBJECT

    private:
        QHBoxLayout *vertical_layout, *vertical_layout_content;
        QScrollArea *scroll_area_doc;
        QWidget *scroll_area_doc_content;

        DocumentRenderer *doc_renderer;


    public:
        explicit DocTabWidget(const QString &uuid, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        ~DocTabWidget() override;

        inline DocumentRenderer *get_renderer() const { return doc_renderer; }

    signals:

        void create_new_area(const area::area_t &area);

        void remove_area(const QString &area_uuid);
    };

}

#endif //DOC_VIEWER_DOCUMENT_TAB_WIDGET_H
