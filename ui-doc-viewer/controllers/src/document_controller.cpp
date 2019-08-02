//
// Created by pornosaur on 15.7.19.
//

#include <iostream>
#include <utility>

#include "document_controller.h"

using namespace qcontroller;

DocController::~DocController() {
    //TODO; delete data
}

void DocController::update(void *data) {
    //TODO: update smth
}

QString DocController::create_document(const QString &file_path) {
    auto *doc = new qmodel::Document(file_path);
    documents_map.insert(doc->get_internal_uuid(), doc);

    return doc->get_internal_uuid();
}

void DocController::load_document() {
    const QString file_path = QFileDialog::getOpenFileName(nullptr, "Choose document file");
    const QString uuid = create_document(file_path);

    emit document_changed(file_path, uuid);
}

void DocController::convert_to_qimage(const QString &uuid, int page) {
    auto *doc = documents_map.value(uuid);

    QImage p_image = doc->get_page_image(page);

    emit respond_qimage(p_image);
}
