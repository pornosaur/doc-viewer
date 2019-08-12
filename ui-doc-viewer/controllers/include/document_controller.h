//
// Created by pornosaur on 15.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_CONTROLLER_H
#define DOC_VIEWER_DOCUMENT_CONTROLLER_H

#include <QtWidgets>
#include <QUuid>
#include <QString>
#include <QHash>

#include "Observer.h"
#include "document.h"
#include "types_utils.h"

namespace qcontroller {

    class DocController : public Observer {
    Q_OBJECT

    private:
        QHash<QString, qmodel::Document *> documents_map;

        QString create_document(const QString &file_path);

    public:
        ~DocController() override;

        void update(void *data) override;

    public slots:

        void load_document();

        void convert_to_qimage(const QString &uuid, int page);

        void save_document_template(const stg::save_t &save_doc);

    signals:

        void document_changed(const QString &file_path, const QString &uuid);

        void respond_qimage(const QImage &p_image);
    };

}

#endif //DOC_VIEWER_DOCUMENT_CONTROLLER_H
