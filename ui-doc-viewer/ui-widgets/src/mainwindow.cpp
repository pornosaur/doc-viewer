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

    QMetaObject::connectSlotsByName(this);

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
    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::inquiry_for_page_image, doc_controller,
            &qcontroller::DocController::convert_to_qimage);
    connect(doc_controller, &qcontroller::DocController::respond_qimage, ui->tab_widget_doc,
            &qview::DocTabViewWidget::rendering_image);

    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::send_new_area, toolbox_controller,
            &qcontroller::ToolBoxController::request_settings);
    connect(toolbox_controller, &qcontroller::ToolBoxController::send_area, prop_controller,
            &qcontroller::PropertiesController::add_area);

    connect(prop_controller, &qcontroller::PropertiesController::send_area_uuid, ui->tab_widget_doc,
            &qview::DocTabViewWidget::update_area_uuid);
    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::send_remove_area, prop_controller,
            &qcontroller::PropertiesController::remove_area);
    connect(ui->tab_widget_doc, &qview::DocTabViewWidget::send_update_area_struct, prop_controller,
            &qcontroller::PropertiesController::update_area_struct);

    connect(prop_controller, &qcontroller::PropertiesController::send_updated_area, tool_box_area_page,
            &qview::ToolBoxPageArea::update_area_properties);

    connect(ui->combo_box_area_type, &qview::ComboBoxAreaType::send_selection_setting, toolbox_controller,
            &qcontroller::ToolBoxController::update_settings);
}

