//
// Created by pornosaur on 3.4.19.
//

#ifndef PROJECT_M_DOCUMENT_H
#define PROJECT_M_DOCUMENT_H

#include <QGraphicsPixmapItem>
#include <QAbstractItemModel>
#include <QtWidgets/QGraphicsView>
#include <opencv4/opencv2/opencv.hpp>

namespace qmodel {

    class Document : public QObject {
    Q_OBJECT

    private:
        QString doc_path;

    public:
        Document() = default;

        ~Document() = default;

    signals:

        /* signals here */

    };

}

#endif //PROJECT_M_DOCUMENT_H
