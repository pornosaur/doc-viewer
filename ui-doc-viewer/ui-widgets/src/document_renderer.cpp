//
// Created by pornosaur on 26.4.19.
//

#include <iostream>
#include <QMouseEvent>


#include "document_renderer.h"

using namespace qview;


void DocumentRenderer::set_document_pixmap(const QImage &image) {
    doc_pixmap.setPixmap(QPixmap::fromImage(image));
    setGeometry(0,0, image.width(), image.height());

}

void DocumentRenderer::mousePressEvent(QMouseEvent *ev) {
    std::cout << "DOC: CLICKED!!" << std::endl;

    QRect r(0,0,300,300);
    const QPoint p = ev->pos();
    if (r.contains(p)) {
        std::cout << "CONTAINS" << std::endl;

    }


}

