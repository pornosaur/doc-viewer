//
// Created by pornosaur on 15.7.19.
//

#ifndef DOC_VIEWER_DOCUMENT_PAGE_PROPERTY_H
#define DOC_VIEWER_DOCUMENT_PAGE_PROPERTY_H

#include <QWidget>
#include <QVBoxLayout>

namespace qview {

    class DocPageProperty : public QWidget {
    private:
        QVBoxLayout *vertical_layout_page;

    public:
        explicit DocPageProperty(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        ~DocPageProperty() override = default;
    };

}

#endif //DOC_VIEWER_DOCUMENT_PAGE_PROPERTY_H
