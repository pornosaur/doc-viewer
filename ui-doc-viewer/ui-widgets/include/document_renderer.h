//
// Created by pornosaur on 26.4.19.
//

#ifndef PROJECT_DOCUMENT_RENDERER_H
#define PROJECT_DOCUMENT_RENDERER_H

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>

#include "template_rect.h"

namespace qview {

    class DocumentRenderer : public QGraphicsView {
    Q_OBJECT

    private:
        QGraphicsPixmapItem *doc_pixmap;
        QGraphicsScene *_scene;

    public:
        explicit DocumentRenderer(QWidget *parent = nullptr);

    public slots:
        void set_document_pixmap(const QImage &image);

    protected:
        void mousePressEvent(QMouseEvent *ev) override;

    };
}

#endif //PROJECT_DOCUMENT_RENDERER_H
