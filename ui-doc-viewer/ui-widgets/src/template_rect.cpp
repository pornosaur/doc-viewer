//
// Created by pornosaur on 17.7.19.
//

#include <QPen>
#include <QCursor>
#include <QtMath>

#include "template_rect.h"

using namespace qview;


QPen TemplateRect::unselected_pen = QPen(QBrush(QColor(0, 0, 0)), 2);

QPen TemplateRect::selected_pen = QPen(QBrush(QColor(255, 0, 0)), 3);


TemplateRect::TemplateRect(const QRectF &rect, QGraphicsItem *parent) : QGraphicsRectItem(
        QRectF(QPointF(0, 0), rect.size()), parent) {
    init();
    moveBy(rect.x(), rect.y());
}

TemplateRect::TemplateRect(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent)
        : QGraphicsRectItem(0, 0, w, h, parent) {
    init();
    moveBy(x, y);
}

void TemplateRect::setForceResizing(bool flag) {
    resizing = flag;
    setFlag(QGraphicsItem::ItemIsMovable, !flag);
}

void TemplateRect::init() {
    setAcceptHoverEvents(true);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

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

    qreal pos_mouse_x = pos.x() >= scene()->width() ? scene()->width() : pos.x();
    qreal w = (pos_mouse_x - x());
    w = (w <= 0) ? 10 : w;

    qreal pos_mouse_y = pos.y() >= scene()->height() ? scene()->height() : pos.y();
    qreal h = (pos_mouse_y - y());
    h = h <= 0 ? 10 : h;

    new_rect.setWidth(w);
    new_rect.setHeight(h);
    new_rect = new_rect.normalized();

    resize_button->setRect(new_rect.bottomRight().x() - resize_button->rect().width(),
                           new_rect.bottomRight().y() - resize_button->rect().height(),
                           resize_button->rect().width(), resize_button->rect().height());

    setRect(new_rect);

    has_changed = true;
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
        setForceResizing(true);
    }
}

void TemplateRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);

    if (!resizing && (!(x() >= 0 && (x() + rect().width()) <= scene()->width()) ||
                      !(y() >= 0 && (y() + rect().height()) <= scene()->height()))) {
        qreal s_x = x() < 0 ? 0 : x();
        s_x = (x() + rect().width()) > scene()->width() ? scene()->width() - rect().width() : s_x;

        qreal s_y = y() < 0 ? 0 : y();
        s_y = (y() + rect().height()) > scene()->height() ? scene()->height() - rect().height() : s_y;

        setPos(s_x, s_y);

        has_changed = true;
    }

    if (resizing) resize_area(event->scenePos());
}

void TemplateRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);

    if (resizing) {
        setForceResizing(false);
    }
}


QVariant TemplateRect::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemSelectedChange) {
        resize_button->setVisible(value.toBool());
    } else if (change == QGraphicsItem::ItemPositionChange) {
        has_changed = true;
    }

    return QGraphicsItem::itemChange(change, value);
}
