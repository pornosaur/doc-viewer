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
        QGraphicsPixmapItem doc_pixmap;

    public:
        explicit DocumentRenderer(QWidget *parent = nullptr) : QGraphicsView(parent) {
            setMouseTracking(true);


            setScene(new QGraphicsScene(this));
            scene()->addItem(&doc_pixmap);
            setStyleSheet("background-color: rgba(255, 255, 255, 0.1);");
           // auto *r = scene()->addRect(0, 0, 300 , 300);
            scene()->addItem(new TemplateRect(0, 0, 300, 300));

            /*r->brush().setColor(QColor::fromRgb(255, 0, 0));
            r->setPen(QPen(QColor::fromRgb(255, 0, 0)));*/

            //repaint();
            //scene()->removeItem(r);
            //doc_pixmap.setOpacity(0.1);
        };

    public slots:
        void set_document_pixmap(const QImage &image);

    protected:
        void mousePressEvent(QMouseEvent *ev) override;
    };
}

#endif //PROJECT_DOCUMENT_RENDERER_H
