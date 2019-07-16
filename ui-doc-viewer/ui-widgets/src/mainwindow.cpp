//
// Created by pornosaur on 1.4.19.
//

#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "document.h"
#include "document_tab_widget.h"
#include "document_page_property.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QMetaObject::connectSlotsByName(this);

    doc_controller = new qcontroller::DocController();
    subscribe(doc_controller);

    //TODO: Creating new tab like this
    auto *tab1 = new qview::DocTabWidget();
    ui->tab_widget_doc->addTab(tab1, QString());
    ui->tab_widget_doc->setTabText(ui->tab_widget_doc->indexOf(tab1),
                                   QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));

    //TODO: Creating page property like this
    auto *page1 = new qview::DocPageProperty();
    ui->tool_box_property->addItem(page1, QStringLiteral("Property"));
    ui->tool_box_property->setItemText(ui->tool_box_property->indexOf(page1),
                                       QApplication::translate("MainWindow", "Property", Q_NULLPTR));

    connect_signals();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connect_signals() {
    /* ui connections */
    connect(ui->action_load_document, SIGNAL(triggered()), this, SLOT(action_load_document()));
    connect(this, SIGNAL(load_document(const QString&)), doc_controller, SLOT(load_document(const QString&)));
    connect(doc_controller, SIGNAL(document_changed(const QImage & )), this, SLOT(received_image(const QImage &)));
//    connect(this, SIGNAL())
}

void MainWindow::action_load_document() {
    QString file_name = QFileDialog::getOpenFileName(this, "Document");


    emit load_document(file_name);
}

void MainWindow::received_image(const QImage &image) {
    auto *tab = (qview::DocTabWidget *) ui->tab_widget_doc->currentWidget();

    tab->get_renderer()->set_document_pixmap(image);
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    std::cout << "CLICKED!!" << std::endl;
}
