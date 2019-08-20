//
// Created by pornosaur on 1.4.19.
//

#ifndef DOC_VIEWER_MAINWINDOW_H
#define DOC_VIEWER_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDataWidgetMapper>
#include <QtWidgets/QGraphicsPixmapItem>
#include <controllers/include/properties_controller.h>
#include <controllers/include/toolbox_controller.h>

#include "Observable.h"
#include "document_controller.h"
#include "tool_box_page_area.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public utils::Observable {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow() override;

    void connect_signals() override;

private:
    Ui::MainWindow *ui;

    qview::ToolBoxPageArea *tool_box_area_page;

    /* Controllers */
    qcontroller::DocController *doc_controller;
    qcontroller::PropertiesController *prop_controller;
    qcontroller::ToolBoxController *toolbox_controller;


    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void save_doc_template(bool checked);

    void save_doc_template_as();

};

#endif //DOC_VIEWER_MAINWINDOW_H
