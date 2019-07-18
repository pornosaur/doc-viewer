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

    auto lb_p = rect().bottomRight();
    auto *it = new QGraphicsRectItem(lb_p.x() - 5, lb_p.y() - 5, 10, 10, this);
    childItems().push_back(it);

    QPen p(QBrush(QColor(0, 0, 0, 255)), 2);
    setPen(p);

    QBrush b(QColor(0, 0, 0, 20), Qt::Dense3Pattern);
    setBrush(b);
}

void TemplateRect::selecting_area(bool select) {
    if (!contains && select) {
        contains = true;

        setPen(selected_pen);
        setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
    } else if (contains && !select) {
        contains = false;

        setPen(unselected_pen);
        setCursor(QCursor(Qt::CursorShape::ArrowCursor));
    }
}


void TemplateRect::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsRectItem::hoverMoveEvent(event);

    QRectF m_rect(event->pos().x() - 20, event->pos().y() - 20, 40, 40);

    if (!rect().contains(m_rect)) {
        selecting_area();
    } else {
        selecting_area(false);
    }
}

void TemplateRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QGraphicsRectItem::hoverLeaveEvent(event);

    selecting_area(false);
}
