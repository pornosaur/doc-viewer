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

/*    ui->doc_view->setScene(new QGraphicsScene());
    ui->doc_view->scene()->addItem(&pixmap);

    ui->doc_view->setMouseTracking(true);*/

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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::set_image_graphics(QImage &img) {
    pixmap.setPixmap(QPixmap::fromImage(img.rgbSwapped()));
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    std::cout << "CLICKED!!" << std::endl;
}
