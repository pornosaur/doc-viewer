//
// Created by pornosaur on 26.4.19.
//

#ifndef PROJECT_DOCUMENT_RENDERER_H
#define PROJECT_DOCUMENT_RENDERER_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QUuid>


#include "template_rect.h"
#include "types_utils.h"

namespace qview {

    class DocumentRenderer : public QGraphicsView {
    Q_OBJECT

    private:
        QString internal_id;

        QGraphicsPixmapItem *doc_pixmap;
        QGraphicsScene *_scene;

        bool adding_area;

        void add_template_area(const QPointF &pos);

        void remove_template_area();

    public:
        explicit DocumentRenderer(const QString &uuid, QWidget *parent = nullptr);

        inline QString get_internal_id() const { return internal_id; }

        void set_current_area_uuid(const QString &ara_uuid);

    public slots:

        void set_document_pixmap(const QImage &image);

    signals:

        void create_new_area(const area::area_t &area);

        void remove_area(const QString &area_uuid);

    protected:
        void mousePressEvent(QMouseEvent *ev) override;

        void mouseReleaseEvent(QMouseEvent *ev) override;

        void keyPressEvent(QKeyEvent *event) override;

    };
}

#endif //PROJECT_DOCUMENT_RENDERER_H
