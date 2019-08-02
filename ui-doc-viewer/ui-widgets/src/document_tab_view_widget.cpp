//
// Created by pornosaur on 16.7.19.
//

#include "document_tab_view_widget.h"

using namespace qview;

DocTabViewWidget::DocTabViewWidget(QWidget *parent) : QTabWidget(parent) {
    setUsesScrollButtons(true);
    setTabsClosable(true);
    setMovable(true);
    setDocumentMode(true);
}

void DocTabViewWidget::create_new_tab(const QString &tab_name, const QString &uuid) {
    auto *new_tab = new qview::DocTabWidget(uuid, this);
    int idx = addTab(new_tab, QString());

    setTabText(idx, QApplication::translate("MainWindow", tab_name.toStdString().c_str(), Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
    setTabToolTip(idx, QApplication::translate("MainWindow", tab_name.toStdString().c_str(), Q_NULLPTR));
#endif // QT_NO_TOOLTIP

    //TODO: impl. disconnect while closing tab!
    connect(new_tab, &DocTabWidget::create_new_area, this, &DocTabViewWidget::create_new_area);
    connect(new_tab, &DocTabWidget::remove_area, this, &DocTabViewWidget::remove_area);

    emit inquiry_for_page_image(uuid, 1);
}

void DocTabViewWidget::create_new_area(const area::area_t &area) {
    auto *tab = (DocTabWidget *) currentWidget();
    if (!tab) return;

    emit send_new_area(tab->get_renderer()->get_internal_id(), area);
}

void DocTabViewWidget::remove_area(const QString &area_uuid) {
    auto *tab = (DocTabWidget *) currentWidget();
    if (!tab) return;

    emit send_remove_area(tab->get_renderer()->get_internal_id(), area_uuid);
}

void DocTabViewWidget::rendering_image(const QImage &image) {
    auto *tab = (DocTabWidget *) currentWidget();
    if (!tab) return;

    tab->get_renderer()->set_document_pixmap(image);
}

void DocTabViewWidget::update_area_uuid(const QString &area_uuid) {
    auto *tab = (DocTabWidget *) currentWidget();
    if (!tab) return;

    tab->get_renderer()->set_current_area_uuid(area_uuid);
}