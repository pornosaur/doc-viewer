//
// Created by pornosaur on 1.4.19.
//

#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "document.h"
#include "document_tab_widget.h"
#include "document_page_property.h"
#include "pagination_widget.h"
#include "document_tab_view_widget.h"
#include "tool_box_page_area.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //QMetaObject::connectSlotsByName(this);

    /*
    if (QFile f("train.txt"); f.open(QFile::ReadOnly)){
        QTextStream rs(&f);
        if (QFile w("doc_list_train.txt"); w.open(QFile::WriteOnly)) {
            QTextStream ws(&w);

            while (!rs.atEnd()) {
                QStringList l = rs.readLine().split(' ');
                if (l.size() != 2) continue;

                int type = l.at(1).toInt();
                if (type == 1 || type == 11 || type == 14) ws << "images/" + l.at(0) << endl;
            }

            f.close();
            w.close();
        }
    }
     */

    std::cout << "FINISHED" << std::endl;

    doc_controller = new qcontroller::DocController();
    prop_controller = new qcontroller::PropertiesController();
    toolbox_controller = new qcontroller::ToolBoxController();


    //TODO: Creating page property like this
    tool_box_area_page = new qview::ToolBoxPageArea();
    ui->tool_box_property->addItem(tool_box_area_page, QStringLiteral("Area"));
    ui->tool_box_property->setItemText(ui->tool_box_property->indexOf(tool_box_area_page),
                                       QApplication::translate("MainWindow", "Area", Q_NULLPTR));
    ui->tool_box_property->setItemToolTip(ui->tool_box_property->indexOf(tool_box_area_page),
                                          QApplication::translate("MainWindow", "Selected area", Q_NULLPTR));

    auto *p = new qview::PaginationWidget();
    ui->statusbar_info->addWidget(p);

    connect_signals();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connect_signals() {
    /* ui connections */
    connect(ui->action_load_document, SIGNAL(triggered()), doc_controller, SLOT(load_document()));
    connect(doc_controller, &qcontroller::DocController::document_changed, ui->tab_widget_doc,
            &qview::DocTabViewWidget::create_new_tab);
    connect(doc_controller, &qcontroller::DocController::current_document_changed, prop_controller,
            &qcontroller::PropertiesController::set_current_selected_area);

    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::inquiry_for_page_image, doc_controller,
            &qcontroller::DocController::convert_to_qimage);
    connect(doc_controller, &qcontroller::DocController::respond_qimage, ui->tab_widget_doc,
            &qview::DocTabViewWidget::rendering_image);

    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::send_new_area, toolbox_controller,
            &qcontroller::ToolBoxController::request_settings);
    connect(toolbox_controller, &qcontroller::ToolBoxController::send_area, prop_controller,
            &qcontroller::PropertiesController::create_new_area);

    connect(doc_controller, &qcontroller::DocController::request_delete_doc, prop_controller,
            &qcontroller::PropertiesController::remove_doc_template);
    connect(doc_controller, &qcontroller::DocController::request_close_delete_doc, ui->tab_widget_doc,
            &qview::DocTabViewWidget::close_tab);
    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::request_close_tab, doc_controller,
            &qcontroller::DocController::remove_document);

    connect(prop_controller, &qcontroller::PropertiesController::send_created_area, ui->tab_widget_doc,
            &qview::DocTabViewWidget::update_area_uuid);

    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::send_remove_area, prop_controller,
            &qcontroller::PropertiesController::remove_area);
    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::send_update_area_struct, prop_controller,
            QOverload<const QString &, const QString &, const area::area_t &>::of(
                    &qcontroller::PropertiesController::update_area_struct));

    connect(prop_controller, &qcontroller::PropertiesController::send_updated_area, tool_box_area_page,
            &qview::ToolBoxPageArea::update_area_properties);

    connect(ui->combo_box_area_type, &qview::ComboBoxAreaType::send_selection_setting, toolbox_controller,
            &qcontroller::ToolBoxController::update_settings);

    connect(ui->group_box_area_actions, &qview::GroupBoxAreaActions::send_area_actions_changes, toolbox_controller,
            &qcontroller::ToolBoxController::update_settings);

    connect(tool_box_area_page, &qview::ToolBoxPageArea::send_update_area_properties, prop_controller,
            QOverload<const area::area_t &>::of(&qcontroller::PropertiesController::update_area_struct));

    connect(ui->action_save, &QAction::triggered, this, &MainWindow::save_doc_template);
    connect(ui->action_save_as, &QAction::triggered, this, &MainWindow::save_doc_template_as);

    connect(prop_controller, &qcontroller::PropertiesController::send_save_request, doc_controller,
            &qcontroller::DocController::save_document_template);

    connect(ui->action_load, &QAction::triggered, prop_controller, &qcontroller::PropertiesController::load_template);
    connect(ui->action_load_document_list, &QAction::triggered, doc_controller,
            &qcontroller::DocController::load_document_list);
}

void MainWindow::save_doc_template(bool checked) {
    prop_controller->save_template(checked);
}

void MainWindow::save_doc_template_as() {
    save_doc_template(true);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {


    switch (event->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            prop_controller->save_template(false);
            break;
        case Qt::Key_Backspace:
            doc_controller->load_previous();
            break;
        case Qt::Key_Escape:
            doc_controller->corrupted_doc();
            break;
    }

    QMainWindow::keyPressEvent(event);
}