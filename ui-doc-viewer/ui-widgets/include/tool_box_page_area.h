//
// Created by pornosaur on 25.7.19.
//

#ifndef DOC_VIEWER_TOOL_BOX_PAGE_AREA_H
#define DOC_VIEWER_TOOL_BOX_PAGE_AREA_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QCheckBox>
#include <QComboBox>

#include "combo_box_area_type.h"
#include "types_utils.h"

namespace qview {

    class ToolBoxPageArea : public QWidget {
    Q_OBJECT

    private:
        QVBoxLayout *vertical_layout_page_area;
        QFormLayout *form_layout_area;
        QFrame *line_separator;
        QLabel *label_name, *label_type, *label_action, *label_page, *label_page_num, *label_x, *label_y, *label_width,
                *label_height;
        QLineEdit *line_edit_name;
        QLabel *line_edit_x, *line_edit_y, *line_edit_width, *line_edit_height;
        QCheckBox *check_box_ocr, *check_box_conceal, *check_box_extract;
        ComboBoxAreaType *combo_box_type;


    public:
        explicit ToolBoxPageArea(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    public slots:

        void update_area_properties(const area::area_t &area);


    };

}

#endif //DOC_VIEWER_TOOL_BOX_PAGE_AREA_H
