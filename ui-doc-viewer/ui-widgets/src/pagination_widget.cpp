//
// Created by pornosaur on 24.7.19.
//

#include <QApplication>

#include "pagination_widget.h"

using namespace qview;

PaginationWidget::PaginationWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f) {
    setObjectName(QStringLiteral("horizontal_layout_pagination"));
    setMinimumSize(QSize(80, 0));
    setMaximumSize(QSize(200, 16777215));
    setContentsMargins(0, 0, 0, 0);

    horizontal_layout_pagination = new QHBoxLayout(this);
    horizontal_layout_pagination->setSpacing(2);
    horizontal_layout_pagination->setObjectName(QStringLiteral("horizontal_layout_pagination"));
    horizontal_layout_pagination->setContentsMargins(5, 0, 0, 0);

    button_previous_page = new QPushButton(this);
    button_previous_page->setObjectName(QStringLiteral("button_previous_page"));

    QSizePolicy size_button(QSizePolicy::Fixed, QSizePolicy::Fixed);
    size_button.setHorizontalStretch(0);
    size_button.setVerticalStretch(0);
    size_button.setHeightForWidth(button_previous_page->sizePolicy().hasHeightForWidth());

    button_previous_page->setSizePolicy(size_button);
    button_previous_page->setMaximumSize(20, 20);

    QIcon icon_button_prev;
    icon_button_prev.addFile(QStringLiteral("images/arrow_left.png"), QSize(), QIcon::Normal, QIcon::Off);
    button_previous_page->setIcon(icon_button_prev);
    button_previous_page->setIconSize(QSize(20, 20));

    horizontal_layout_pagination->addWidget(button_previous_page);

    label_page = new QLabel(this);
    label_page->setObjectName(QStringLiteral("label_page"));
    label_page->setMinimumSize(QSize(20, 20));

    horizontal_layout_pagination->addWidget(label_page);

    button_next_page = new QPushButton(this);
    button_next_page->setObjectName(QStringLiteral("button_next_page"));
    button_next_page->setMaximumSize(QSize(20, 20));
    button_next_page->setSizePolicy(size_button);


    QColor color_button(button_next_page->palette().color(QPalette::Button));
    color_button.setAlpha(0);

    QPalette palette_button(color_button);
    button_next_page->setPalette(palette_button);
    button_previous_page->setPalette(palette_button);

    QIcon icon_button_next;
    icon_button_next.addFile(QStringLiteral("images/arrow_right.png"), QSize(), QIcon::Normal, QIcon::Off);
    button_next_page->setIcon(icon_button_next);

    horizontal_layout_pagination->addWidget(button_next_page);

    label_page_description = new QLabel(this);
    label_page_description->setObjectName(QStringLiteral("label_page_description"));

    QFont font_label;
    font_label.setPointSize(8);
    label_page_description->setFont(font_label);

    horizontal_layout_pagination->addWidget(label_page_description);

#ifndef QT_NO_TOOLTIP
    button_previous_page->setToolTip(QApplication::translate("MainWindow", "Previous page", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    button_previous_page->setText(QString());
    label_page->setText(QString());
#ifndef QT_NO_TOOLTIP
    button_next_page->setToolTip(QApplication::translate("MainWindow", "Next page", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    button_next_page->setText(QString());
    label_page_description->setText(QApplication::translate("MainWindow", "page from ", Q_NULLPTR));
}