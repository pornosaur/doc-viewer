//
// Created by pornosaur on 15.7.19.
//

#include <iostream>
#include <QMessageBox>

#include "document_controller.h"

using namespace qcontroller;

DocController::~DocController() {
    //TODO; delete data
}

void DocController::update(void *data) {
    //TODO: update smth
}

QString DocController::create_document(const QString &file_path, const QString &prefix, bool from_list) {
    auto *doc = new qmodel::Document(file_path, prefix);
    doc->set_from_list(from_list);

    documents_map.insert(doc->get_internal_uuid(), doc);

    return doc->get_internal_uuid();
}

void DocController::remove_document(const QString &doc_uuid) {
    emit request_delete_doc(doc_uuid);

    auto *doc = documents_map.take(doc_uuid);
    delete doc;
}

void DocController::_load_document(const QString &doc_path, const QString &prefix, bool from_list) {
    const QString uuid = create_document(doc_path, prefix, from_list);

    emit current_document_changed(uuid, "");
    emit document_changed(doc_path, uuid);
}

void DocController::load_next_document() {
    if (doc_list.empty()) return;

    const QString first_doc = doc_list.front();
    current_doc_path = first_doc;

    if (doc_list_history.size() >= 5) doc_list_history.pop_front();
    doc_list_history << first_doc;
    doc_list.pop_front();

    ++last_num_list;
    _load_document(root_doc_list + first_doc, first_doc, true);
}

void DocController::load_document() {
    const QString file_path = QFileDialog::getOpenFileName(nullptr, "Choose document file", QString(),
                                                           "Image (*.gif *.tiff *.PNG *.png *.JPG *.jpg *.jpeg *.JPEG *.TIFF *.GIF)");
    if (file_path.isEmpty()) return;
    _load_document(file_path);
}

void DocController::load_document_list() {
    const QString file_path = QFileDialog::getOpenFileName(nullptr, "Choose document list file", QString(),
                                                           "Document list (*.txt *.gif)");

    if (file_path.isEmpty()) return;

    root_doc_list = file_path;

    QFileInfo i(root_doc_list);
    doc_list_name = i.baseName();
    root_doc_list.replace(i.fileName(), "");

    load_list_line_num();
    if (QFile f(file_path); f.open(QIODevice::ReadOnly)) {
        QTextStream stream(&f);

        int _i = -1;

        while (!stream.atEnd()) {
            ++_i;
            if (_i < last_num_list) {
                stream.readLine();
                continue;
            }
            doc_list << stream.readLine();
        }

        f.close();
    }


    load_next_document();
}

void DocController::convert_to_qimage(const QString &uuid, int page) {
    auto *doc = documents_map.value(uuid);

    QImage p_image = doc->get_page_image(page);

    emit respond_qimage(p_image);
}

void DocController::save_document_template(const stg::save_t &save_doc) {
    auto *doc = documents_map.value(save_doc.doc_uuid, nullptr);
    if (!doc) return;

    stg::save_t json = save_doc;
    if (json.areas_json.empty()) {
        //TODO: warning about empty areas!
    }

    doc->convert2json(json.doc_json);
    doc->save_to_file(json);

    if (doc->is_from_list()) save_list_line_num();

    emit request_close_delete_doc(save_doc.doc_uuid);
    load_next_document();
}

void DocController::load_previous() {
    emit request_close_delete_doc("");
    if (!doc_list_history.isEmpty()) {
        QString path = doc_list_history.pop();
        --last_num_list;
        _load_document(root_doc_list + path, path);
    }
}

void DocController::save_list_line_num() {
    if (QFile f("./" + doc_list_name + "_setting.set"); f.open(QIODevice::WriteOnly)) {
        QTextStream stream(&f);
        stream << last_num_list << endl;

        f.close();
    }
}

void DocController::load_list_line_num() {
    if (QFile f("./" + doc_list_name + "_setting.set"); f.open(QIODevice::ReadOnly)) {
        QTextStream stream(&f);

        QString line = stream.readLine();
        last_num_list = line.toInt();

        f.close();
    }
}

void DocController::corrupted_doc() {
    if (current_doc_path.isEmpty()) return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Corrupted document", "Is this document noisy or unreadable?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (QFile f("./corrupted_doc.txt"); f.open(QFile::Append)) {
            QTextStream stream(&f);
            stream << current_doc_path << endl;
            f.close();
        }

        save_list_line_num();
        emit request_close_delete_doc("");
        load_next_document();
    }
}
