//
// Created by pornosaur on 26.4.19.
//

#ifndef PROJECT_DOCUMENT_RENDERER_H
#define PROJECT_DOCUMENT_RENDERER_H

#include <QtWidgets/QGraphicsView>

namespace qview {

    class DocumentRenderer : public QGraphicsView {

    public:
        explicit DocumentRenderer(QWidget *parent = nullptr) : QGraphicsView(parent) {
            
        };

    protected:
        void mousePressEvent(QMouseEvent *ev) override;
    };
}

#endif //PROJECT_DOCUMENT_RENDERER_H
