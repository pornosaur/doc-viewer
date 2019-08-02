//
// Created by pornosaur on 3.4.19.
//

#include <experimental/filesystem>
#include <QUuid>

#include "document.h"

using namespace qmodel;

namespace fs = std::experimental::filesystem;

Document::Document(QString file_path) : doc_path(std::move(file_path)) {
    internal_uuid = QUuid::createUuid().toString();

    doc_img = QImage(doc_path); //TODO: temporary solution
}

QImage Document::get_page_image(int page) {
    QImage image(doc_img);

    return std::move(image);
}

