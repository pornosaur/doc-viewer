//
// Created by pornosaur on 1.4.19.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "document.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QMetaObject::connectSlotsByName(this);

    ui->doc_view->setScene(new QGraphicsScene());
    ui->doc_view->scene()->addItem(&pixmap);

    ui->doc_view->setMouseTracking(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_code_edit_editingFinished() {
//    std::cout << "TEXT: " << ui->code_edit->text().toStdString() << std::endl;
}

void MainWindow::set_image_graphics(QImage &img) {
    pixmap.setPixmap(QPixmap::fromImage(img.rgbSwapped()));
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    std::cout << "CLICKED!!" << std::endl;
}
