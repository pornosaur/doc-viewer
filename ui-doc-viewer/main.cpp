//
// Created by pornosaur on 1.4.19.
//

#include <QApplication>
#include <QMetaObject>

#include "mainwindow.h"
#include "document_renderer.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
