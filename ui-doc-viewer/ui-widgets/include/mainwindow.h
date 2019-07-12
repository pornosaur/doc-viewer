//
// Created by pornosaur on 1.4.19.
//

#ifndef DOC_VIEWER_MAINWINDOW_H
#define DOC_VIEWER_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDataWidgetMapper>
#include <QtWidgets/QGraphicsPixmapItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *ev);

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem pixmap;


private slots:
    void on_code_edit_editingFinished();
    void set_image_graphics(QImage &img);
};

#endif //DOC_VIEWER_MAINWINDOW_H
