//
// Created by pornosaur on 17.7.19.
//

#ifndef DOC_VIEWER_TEMPLATE_RECT_H
#define DOC_VIEWER_TEMPLATE_RECT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

#include <iostream>


namespace qview {

    class TemplateRect : public QGraphicsRectItem {
    private:
        bool contains = false;

        static QPen selected_pen, unselected_pen;


        void selecting_area(bool select = true);

        void init();

    public:
        explicit TemplateRect(const QRectF &rect, QGraphicsItem *parent = nullptr);

        TemplateRect(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

    protected:
        void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    };

}

#endif //DOC_VIEWER_TEMPLATE_RECT_H
