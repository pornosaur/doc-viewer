//
// Created by pornosaur on 15.7.19.
//

#include <iostream>
#include "document_controller.h"

using namespace qcontroller;

DocController::~DocController() {
    //TODO; delete data
}

void DocController::update(void *data) {
    //TODO: update smth
}

void DocController::load_document(const QString &doc_path) {
    //TODO: loading doc. from file here

    std::cout << doc_path.toStdString() << std::endl;

    QImage img(doc_path);
    emit document_changed(img);
}