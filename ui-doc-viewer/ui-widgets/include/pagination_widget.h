//
// Created by pornosaur on 24.7.19.
//

#ifndef DOC_VIEWER_PAGINATION_WIDGET_H
#define DOC_VIEWER_PAGINATION_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

namespace qview {

    class PaginationWidget : public QWidget {

    private:
        QHBoxLayout *horizontal_layout_pagination;
        QPushButton *button_previous_page, *button_next_page;
        QLabel *label_page, *label_page_description;

    public:
        explicit PaginationWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    };

}

#endif //DOC_VIEWER_PAGINATION_WIDGET_H
