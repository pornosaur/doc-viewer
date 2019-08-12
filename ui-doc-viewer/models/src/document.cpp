//
// Created by pornosaur on 3.4.19.
//

#include <experimental/filesystem>
#include <QUuid>
#include <fstream>
#include <QFile>
#include <QDir>
#include <iostream>

#include "document.h"

using namespace qmodel;

namespace fs = std::experimental::filesystem;

Document::Document(QString file_path) : doc_path(std::move(file_path)) {
    internal_uuid = QUuid::createUuid().toString();

    QFileInfo info(doc_path);
    doc_name = info.baseName();

    doc_img = QImage(doc_path); //TODO: temporary solution
}

QImage Document::get_page_image(int page) {
    QImage image(doc_img);

    return std::move(image);
}

bool Document::convert2json(Json::Value &doc_json) {
    doc_json = Json::Value(Json::objectValue);

    doc_json["id"] = doc_id.toStdString();
    doc_json["original_doc"] = doc_path.toStdString();
    doc_json["page_num"] = static_cast<int>(total_pages);
    doc_json["areas"] = Json::Value(Json::arrayValue);

    return true;
}


void Document::save_to_file(const stg::save_t &save_doc) {
    Json::StreamWriterBuilder writer_builder;
    writer_builder["commentStyle"] = "None";
    writer_builder["indentation"] = "   ";

    Json::Value final_doc_json = save_doc.doc_json;
    final_doc_json["areas"] = save_doc.areas_json;

    std::string file_name_path = save_doc.path.toStdString();
    if (file_name_path.back() != QDir::separator()) file_name_path += "/";
    file_name_path += doc_name.toStdString() + ".template";

    std::unique_ptr<Json::StreamWriter> writer(writer_builder.newStreamWriter());
    std::ofstream file_stream(file_name_path);
    writer->write(final_doc_json, &file_stream);
}
