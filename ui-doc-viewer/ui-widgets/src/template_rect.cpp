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

    setBrush(Qt::NoBrush);
    setPen(QPen(QBrush(QColor(0, 0, 0)), 2));
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
    QRectF m_rect(event->pos().x() - 20, event->pos().y() - 20, 40, 40);

    if (!rect().contains(m_rect)) {
        selecting_area();
    } else {
        selecting_area(false);
    }
}

void TemplateRect::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    selecting_area(false);
}
