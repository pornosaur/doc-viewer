//
// Created by pornosaur on 3.4.19.
//

#ifndef PROJECT_M_DOCUMENT_H
#define PROJECT_M_DOCUMENT_H

#include <QGraphicsPixmapItem>
#include <QAbstractItemModel>
#include <QtWidgets/QGraphicsView>
#include <QImage>

#include <jsoncpp/json/json.h>

#include "types_utils.h"

namespace qmodel {

    class Document : public QObject {
    Q_OBJECT

    private:
        QString internal_uuid;

        QString doc_id, doc_path, doc_name;

        QImage doc_img; //TODO: Temporary solution for Thomas

        size_t total_pages = 1; //TODO: Temporary solution for Thomas

    public:
        explicit Document(QString file_path);

        ~Document() = default;

        inline QString get_internal_uuid() const { return internal_uuid; }

        inline size_t get_total_pages() const { return total_pages; }

        QImage get_page_image(int page);

        bool convert2json(Json::Value &doc_json);

        void save_to_file(const stg::save_t &save_doc);

    };

}

#endif //PROJECT_M_DOCUMENT_H
