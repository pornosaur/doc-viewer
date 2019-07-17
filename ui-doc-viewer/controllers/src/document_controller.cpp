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

void DocController::load_document() {
    //TODO: loading doc. from file here
    QString file_name = QFileDialog::getOpenFileName(nullptr, "Document");

    std::cout << file_name.toStdString() << std::endl;

    QImage img(file_name);
    emit document_changed(img);
}