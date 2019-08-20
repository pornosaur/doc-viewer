//
// Created by pornosaur on 1.8.19.
//

#include <iostream>
#include <QFileDialog>
#include <fstream>

#include "properties_controller.h"

using namespace qcontroller;

QString PropertiesController::current_area_uuid = "";
QString PropertiesController::current_doc_uuid = "";

PropertiesController::PropertiesController() {}

PropertiesController::~PropertiesController() {
    //TODO: maybe call saving to file procedure.

    qDeleteAll(areas_map);
    areas_map.clear();
}

void PropertiesController::set_current_selected_area(const QString &doc_uuid, const QString &area_uuid) {
    current_doc_uuid = doc_uuid.isEmpty() ? current_doc_uuid : doc_uuid;
    current_area_uuid = area_uuid.isEmpty() ? current_area_uuid : area_uuid;
}

void PropertiesController::create_new_area(const QString &doc_uuid, const area::area_t &area_struct) {
    qmodel::AreaGroup *area_group = areas_map.value(doc_uuid, nullptr);

    if (!area_group) {
        area_group = new qmodel::AreaGroup(doc_uuid);
        areas_map.insert(doc_uuid, area_group);
    }

    auto area_uuid = area_group->create_area_uuid(area_struct);
    if (!area_uuid.isEmpty()) set_current_selected_area(doc_uuid, area_uuid);

    emit send_created_area(area_uuid, area_struct);
}

void PropertiesController::add_area(const QString &doc_uuid, const area::area_t &area_struct) {
    qmodel::AreaGroup *area_group = areas_map.value(doc_uuid, nullptr);

    if (!area_group) {
        area_group = new qmodel::AreaGroup(doc_uuid);
        areas_map.insert(doc_uuid, area_group);
    }

    auto area_uuid = area_group->create_area_uuid(area_struct);
    if (!area_uuid.isEmpty()) set_current_selected_area(doc_uuid, area_uuid);

    emit send_area_uuid(area_uuid, area_struct);
}

void PropertiesController::remove_area(const QString &doc_uuid, const QString &area_uuid) {
    auto *area_group = areas_map.value(doc_uuid, nullptr);
    if (area_group) area_group->remove_area(area_uuid);

    set_current_selected_area("", "");
}

void PropertiesController::update_area_struct(const QString &doc_uuid, const QString &area_uuid,
                                              const area::area_t &area_struct) {
    auto *area_group = areas_map.value(doc_uuid, nullptr);

    bool updated = false;
    area::area_t _area_struct = area_struct;
    if (area_group) {
        updated = area_group->update_area_struct(area_uuid, _area_struct);
        set_current_selected_area(doc_uuid, area_uuid);
    }
    if (updated) emit send_updated_area("", _area_struct);
}

void PropertiesController::update_area_struct(const area::area_t &area_struct) {
    if (current_area_uuid.isEmpty() || current_doc_uuid.isEmpty()) return;

    update_area_struct(current_doc_uuid, current_area_uuid, area_struct);
}

void PropertiesController::_save_template(const stg::save_t &json_data) {
    auto *area_g = areas_map.value(json_data.doc_uuid, nullptr);
    if (!area_g) return;

    stg::save_t json = json_data;
    area_g->convert2json(json.areas_json);

    emit send_save_request(json);
}

void PropertiesController::load_template() {
    const QString file_path = QFileDialog::getOpenFileName(nullptr, "Choose template file", QString(),
                                                           "Template (*.template)");
    if (file_path.isEmpty()) return;

    Json::Value root;
    auto *area_g = areas_map.value(current_doc_uuid, nullptr);
    if (!area_g) {
        area_g = new qmodel::AreaGroup(current_doc_uuid);
        areas_map.insert(current_doc_uuid, area_g);
    }

    auto areas = area_g->load_from_file(file_path, root);

    for (const auto *it : areas) {
        emit send_created_area(it->get_area_uuid(), it->get_area_struct());
    }
}

void PropertiesController::remove_doc_template(const QString &doc_uuid) {
    auto *area_g = areas_map.take(doc_uuid);
    delete area_g;
}

void PropertiesController::save_template(bool checked) {
    QString path = "";
    if (checked) {
        QFileDialog dialog;
        dialog.setOption(QFileDialog::ShowDirsOnly, true);
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        dialog.setAcceptMode(QFileDialog::AcceptSave);

        dialog.exec();
        if (!dialog.selectedFiles().empty()) path = dialog.selectedFiles().at(0);
    } else {
        path = "./templates/";
        //TODO: default path!
    }

    stg::save_t json;
    json.path = path;
    json.doc_uuid = current_doc_uuid;

    _save_template(json);
}
