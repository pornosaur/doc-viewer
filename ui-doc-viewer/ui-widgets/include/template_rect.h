//
// Created by pornosaur on 17.7.19.
//

#ifndef DOC_VIEWER_TEMPLATE_RECT_H
#define DOC_VIEWER_TEMPLATE_RECT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QKeyEvent>

#include <iostream>


namespace qview {

    class TemplateRect : public QGraphicsRectItem {

    private:
        QString _uuid;

        bool contains = false, resizing = false, has_changed = false;

        static QPen selected_pen, unselected_pen;

        QGraphicsRectItem *resize_button;


        void selecting_area(bool select = true);

        void resize_area(const QPointF &pos);

        void init();

    protected:
        void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;


    public:
        explicit TemplateRect(const QRectF &rect, QGraphicsItem *parent = nullptr);

        TemplateRect(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);

        void setForceResizing(bool flag = true);

        inline QString get_uuid() const { return _uuid; }

        inline void set_uuid(const QString &uuid) { _uuid = uuid; }

        inline qreal get_width() const { return rect().width(); }

        inline qreal get_height() const { return rect().height(); }

        inline bool is_changed() const { return has_changed; }

        inline void set_changed(bool flag) { has_changed = flag; }

    };

}

#endif //DOC_VIEWER_TEMPLATE_RECT_H
