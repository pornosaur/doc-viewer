//
// Created by pornosaur on 26.4.19.
//

#include <iostream>

#include "document_renderer.h"

using namespace qview;


void DocumentRenderer::set_document_pixmap(const QImage &image) {
    doc_pixmap.setPixmap(QPixmap::fromImage(image));
}

void DocumentRenderer::mousePressEvent(QMouseEvent *ev) {
    std::cout << "DOC: CLICKED!!" << std::endl;


}

