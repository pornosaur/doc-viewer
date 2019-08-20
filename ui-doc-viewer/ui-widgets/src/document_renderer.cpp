//
// Created by pornosaur on 26.4.19.
//

#include <iostream>
#include <QMouseEvent>
#include <QStyle>

#include "document_renderer.h"

using namespace qview;

DocumentRenderer::DocumentRenderer(const QString &uuid, QWidget *parent) : QGraphicsView(parent) {
    setMouseTracking(true);
    setStyleSheet("background-color: rgba(255, 255, 255, 0.1);");

    _scene = new QGraphicsScene(this);
    setScene(_scene);

    doc_pixmap = new QGraphicsPixmapItem();
    _scene->addItem(doc_pixmap);

    internal_id = uuid;
    adding_area = false;
}

void DocumentRenderer::set_current_area_uuid(const QString &ara_uuid) {
    if (scene()->focusItem(); auto *area = ((TemplateRect *) scene()->focusItem())) {
        area->set_uuid(ara_uuid);
    }
}

void DocumentRenderer::_create_new_area(const QString &area_uuid, const area::area_t &area_struct) {
    auto *template_area = new TemplateRect(area_struct.dimension._x, area_struct.dimension._y, 10, 10);
    template_area->set_uuid(area_uuid);
    _scene->addItem(template_area);

    template_area->setForceResizing(true);
    template_area->setSelected(true);
    template_area->setFocus();
}

void DocumentRenderer::add_template_area(const QPointF &pos) {
    /*auto *template_area = new TemplateRect(pos.x(), pos.y(), 10, 10);
    _scene->addItem(template_area);

    template_area->setForceResizing(true);
    template_area->setSelected(true);
    template_area->setFocus();*/

    emit create_new_area(area::area_t(pos.x(), pos.y()));
}

void DocumentRenderer::remove_template_area() {
    if (scene()->focusItem(); auto *area = ((TemplateRect *) scene()->focusItem())) {
        scene()->removeItem(area);
        emit remove_area(area->get_uuid());

        delete area;
    }
}

void DocumentRenderer::update_template_area(TemplateRect *area) {
    if (!area->is_changed()) return;

    area::area_t area_struct;
    area_struct.dimension = area::area_dimension_t(area->x(), area->y(), area->get_width(), area->get_height());
    area->set_changed(false);

    emit update_area_struct(area->get_uuid(), area_struct);
}

void DocumentRenderer::set_document_pixmap(const QImage &image) {
    doc_pixmap->setPixmap(QPixmap::fromImage(image));

    setGeometry(0, 0, image.width(), image.height());
    _scene->setSceneRect(0, 0, image.width(), image.height());
    setFrameStyle(QFrame::NoFrame);

    setMaximumWidth(image.width() + parentWidget()->style()->pixelMetric(QStyle::PM_ScrollBarExtent));
    setMinimumWidth(0);
}

void DocumentRenderer::mousePressEvent(QMouseEvent *ev) {
    QGraphicsView::mousePressEvent(ev);

    if (!adding_area && !scene()->focusItem()) {
        add_template_area(mapToScene(ev->pos()));
        adding_area = true;
        QGraphicsView::mousePressEvent(ev);
    } else if (scene()->focusItem()) {
        auto *area = (TemplateRect *) scene()->focusItem();
        area->set_changed(true);

        update_template_area(area);
    }
}

void DocumentRenderer::mouseReleaseEvent(QMouseEvent *ev) {
    if (!adding_area && scene()->focusItem(); auto *area = ((TemplateRect *) scene()->focusItem())) {
        update_template_area(area);
    }

    if (adding_area) {
        if (scene()->focusItem(); auto *area = ((TemplateRect *) scene()->focusItem())) {
            area->setForceResizing(false);
        }

        adding_area = false;
    }


    QGraphicsView::mouseReleaseEvent(ev);
}

void DocumentRenderer::keyPressEvent(QKeyEvent *event) {
    QGraphicsView::keyPressEvent(event);

    if (event->key() == Qt::Key_Delete) {
        remove_template_area();
    }
}

void DocumentRenderer::clear_selection() {
    if (scene()) {
        scene()->clearSelection();
    }
}

