//
// Created by pornosaur on 26.4.19.
//

#include <iostream>
#include <QMouseEvent>
#include <QStyle>

#include "document_renderer.h"

using namespace qview;

DocumentRenderer::DocumentRenderer(QWidget *parent) : QGraphicsView(parent) {
    setMouseTracking(true);
    setStyleSheet("background-color: rgba(255, 255, 255, 0.1);");

    _scene = new QGraphicsScene(this);
    setScene(_scene);

    doc_pixmap = new QGraphicsPixmapItem();
    _scene->addItem(doc_pixmap);

}

void DocumentRenderer::add_template_area(const QPointF &pos) {
    auto *template_area = new TemplateRect(pos.x(), pos.y(), 10, 10);
    _scene->addItem(template_area);

    template_area->setForceResizing(true);
    template_area->setSelected(true);
}

void DocumentRenderer::set_document_pixmap(const QImage &image) {
    doc_pixmap->setPixmap(QPixmap::fromImage(image));

    setGeometry(0, 0, image.width(), image.height());
    _scene->setSceneRect(0, 0, image.width(), image.height());
    setFrameStyle(QFrame::NoFrame);

    setMaximumWidth(image.width() + parentWidget()->style()->pixelMetric(QStyle::PM_ScrollBarExtent));
    setMinimumWidth(0);

    _scene->addItem(new TemplateRect(0, 0, 300, 300));
}

void DocumentRenderer::mousePressEvent(QMouseEvent *ev) {
    QGraphicsView::mousePressEvent(ev);

    if (!adding_area && !scene()->focusItem()) {
        add_template_area(mapToScene(ev->pos()));
        adding_area = true;
        QGraphicsView::mousePressEvent(ev);
    }

}

void DocumentRenderer::mouseReleaseEvent(QMouseEvent *ev) {
    if (adding_area) {
        if (scene()->focusItem(); auto *area = ((TemplateRect *) scene()->focusItem())) {
            area->setForceResizing(false);
        }

        adding_area = false;
    }

    QGraphicsView::mouseReleaseEvent(ev);
}

