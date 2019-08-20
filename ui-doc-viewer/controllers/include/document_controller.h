//
// Created by pornosaur on 15.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_CONTROLLER_H
#define DOC_VIEWER_DOCUMENT_CONTROLLER_H

#include <QtWidgets>
#include <QUuid>
#include <QString>
#include <QHash>
#include <mutex>
#include <condition_variable>


#include "Observer.h"
#include "document.h"
#include "types_utils.h"

namespace qcontroller {

    class DocController : public Observer {
    Q_OBJECT

    private:
        QHash<QString, qmodel::Document *> documents_map;
        QStringList doc_list;
        QStack<QString> doc_list_history;
        QString root_doc_list, doc_list_name, current_doc_path;
        int last_num_list = 0;

        QString create_document(const QString &file_path,  const QString &prefix = "", bool from_list = false);

        void _load_document(const QString &doc_path,  const QString &prefix = "", bool from_list = false);

        void load_next_document();

        void save_list_line_num();

        void load_list_line_num();

    public:
        ~DocController() override;

        void update(void *data) override;

        void corrupted_doc();

    public slots:

        void remove_document(const QString &doc_uuid);

        void load_document();

        void load_document_list();

        void convert_to_qimage(const QString &uuid, int page);

        void save_document_template(const stg::save_t &save_doc);

        void load_previous();

    signals:

        void current_document_changed(const QString &doc_uuid, const QString &area);

        void document_changed(const QString &file_path, const QString &uuid);

        void respond_qimage(const QImage &p_image);

        void request_delete_doc(const QString &doc_uuid);

        void request_close_delete_doc(const QString &doc_uuid);
    };

}

#endif //DOC_VIEWER_DOCUMENT_CONTROLLER_H
