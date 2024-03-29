//
// Created by pornosaur on 16.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_TAB_VIEW_WIDGET_H
#define DOC_VIEWER_DOCUMENT_TAB_VIEW_WIDGET_H

#include <QTabWidget>
#include <QApplication>

#include "document_tab_widget.h"
#include "types_utils.h"


namespace qview {

    class DocTabViewWidget : public QTabWidget {
    Q_OBJECT

    public:
        explicit DocTabViewWidget(QWidget *parent = nullptr);

        QString get_current_doc();

    public slots:

        void close_tab(const QString &doc_uuid);

        void create_new_tab(const QString &tab_name, const QString &uuid);

        void rendering_image(const QImage &image);

        void update_area_uuid(const QString &area_uuid, const area::area_t &area_struct);

        void create_new_area(const area::area_t &area);

        void remove_area(const QString &area_uuid);

        void update_area_struct(const QString &area_uuid, const area::area_t &area_struct);

        void set_current_widget(int idx);

    signals:

        void inquiry_for_page_image(const QString &uuid, int page);

        void send_new_area(const QString &doc_uuid, const area::area_t &area);

        void send_remove_area(const QString &doc_uuid, const QString &area_uuid);

        void
        send_update_area_struct(const QString &doc_uuid, const QString &area_uuid, const area::area_t &area_struct);

        void request_close_tab(const QString &uuid);



    };

}

#endif //DOC_VIEWER_DOCUMENT_TAB_VIEW_WIDGET_H
