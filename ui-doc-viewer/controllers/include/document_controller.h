//
// Created by pornosaur on 15.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_CONTROLLER_H
#define DOC_VIEWER_DOCUMENT_CONTROLLER_H

#include <QtWidgets>

#include "Observer.h"

namespace qcontroller {

    class DocController : public Observer {
    Q_OBJECT

    private:
        bool load_document_from_file(const QString &path);

    public:
        ~DocController() override;

        void update(void *data) override;

    public slots:

        void load_document(const QString &doc_path);

    signals:

        void document_changed(const QImage &doc_img);

    };

}

#endif //DOC_VIEWER_DOCUMENT_CONTROLLER_H
