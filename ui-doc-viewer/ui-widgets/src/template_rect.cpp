//
// Created by pornosaur on 17.7.19.
//

#include <QPen>
#include <QCursor>

#include "template_rect.h"

using namespace qview;


QPen TemplateRect::unselected_pen = QPen(QBrush(QColor(0, 0, 0)), 2);

QPen TemplateRect::selected_pen = QPen(QBrush(QColor(255, 0, 0)), 3);


TemplateRect::TemplateRect(const QRectF &rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent) {
    init();
}

TemplateRect::TemplateRect(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
        : QGraphicsRectItem(x, y, w, h, parent) {
    init();
}

void TemplateRect::init() {
    setAcceptHoverEvents(true);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);


    auto lb_p = rect().bottomRight();
    resize_button = new QGraphicsRectItem(lb_p.x() - 10, lb_p.y() - 10, 10, 10, this);
    childItems().push_back(resize_button);
    resize_button->setVisible(false);

    setPen(unselected_pen);
    setBrush(QBrush(QColor(0, 0, 0, 20), Qt::Dense3Pattern));
}

void TemplateRect::selecting_area(bool select) {
    if (!contains && select) {
        contains = true;

        //setPen(selected_pen);
        setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if (contains && !select) {
        contains = false;

        //setPen(unselected_pen);
        setCursor(QCursor(Qt::ArrowCursor));
    }
}


void TemplateRect::resize_area(const QPointF &pos) {
    prepareGeometryChange();

    QRectF new_rect(rect());

    qreal w = (pos.x() - rect().x());
    w = w <= 0 ? rect().width() : w;

    qreal h = (pos.y() - rect().y());
    h = h <= 0 ? rect().height() : h;

    new_rect.setWidth(w);
    new_rect.setHeight(h);
    new_rect = new_rect.normalized();

    resize_button->setRect(new_rect.bottomRight().x() - resize_button->rect().width(),
                           new_rect.bottomRight().y() - resize_button->rect().height(),
                           resize_button->rect().width(), resize_button->rect().height());

    setRect(new_rect);
}

void TemplateRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsRectItem::hoverMoveEvent(event);

    selecting_area(isSelected() && resize_button->contains(event->pos()));
}

void TemplateRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsRectItem::hoverLeaveEvent(event);

    selecting_area(false);
}


void TemplateRect::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mousePressEvent(event);

    if (!resizing && resize_button->contains(event->pos())) {
        resizing = true;
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}

void TemplateRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);

    if (resizing) resize_area(event->pos());
}

void TemplateRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);

    if (resizing) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        resizing = false;
    }
}


QVariant TemplateRect::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemSelectedChange) {
        resize_button->setVisible(value.toBool());
    }

    return QGraphicsItem::itemChange(change, value);
}
