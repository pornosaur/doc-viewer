//
// Created by pornosaur on 1.4.19.
//

#ifndef DOC_VIEWER_MAINWINDOW_H
#define DOC_VIEWER_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDataWidgetMapper>
#include <QtWidgets/QGraphicsPixmapItem>
#include <controllers/include/properties_controller.h>

#include "Observable.h"
#include "document_controller.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public utils::Observable {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow() override;

    void mousePressEvent(QMouseEvent *ev) override;

    void connect_signals() override;

private:
    Ui::MainWindow *ui;

    /* Controllers */
    qcontroller::DocController *doc_controller;
    qcontroller::PropertiesController *prop_controller;



};

#endif //DOC_VIEWER_MAINWINDOW_H
