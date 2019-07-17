//
// Created by pornosaur on 16.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_TAB_VIEW_WIDGET_H
#define DOC_VIEWER_DOCUMENT_TAB_VIEW_WIDGET_H

#include <QTabWidget>
#include "document_tab_widget.h"


namespace qview {

    class DocTabViewWidget : public QTabWidget {
    Q_OBJECT

    public:
        explicit DocTabViewWidget(QWidget *parent = nullptr) : QTabWidget(parent) {
            setUsesScrollButtons(true);
            setTabsClosable(true);
            setMovable(true);
            setDocumentMode(true);
        };

    public slots:

        void create_new_tab(const QString &tab_name) {};

        void rendering_image(const QImage &image) {
            auto *tab = (DocTabWidget *) currentWidget();
            if (!tab) return;

            tab->get_renderer()->set_document_pixmap(image);
        };
    };

}

#endif //DOC_VIEWER_DOCUMENT_TAB_VIEW_WIDGET_H
