//
// Created by pornosaur on 25.7.19.
//

#ifndef DOC_VIEWER_TYPES_UTILS_H
#define DOC_VIEWER_TYPES_UTILS_H

#include <QVariant>
#include <QMetaEnum>
#include <QString>

#include <jsoncpp/json/json.h>

#include <string>
#include <functional>

namespace area {
    Q_NAMESPACE

    enum class Type : unsigned int {
        TRANSIENT,
        ITERATION_BEGIN,    //Add new type above begin
        TEXT,
        IMAGE,
        LOGO,
        SYNC,
        ITERATION_END
    };

    Q_ENUM_NS(Type)

    enum class Actions : unsigned int {
        TRANSIENT = 0x00,
        OCR = 0x01,
        CONCEAL = 0x02,
        EXTRACT = 0x04,
        CLIPPING = 0x08
    };

    Q_ENUM_NS(Actions)

    struct tool_box_t {
        Type _type;
        Actions _actions;

        explicit tool_box_t(Type type = Type::TRANSIENT, Actions actions = Actions::TRANSIENT) : _type(type),
                                                                                                 _actions(actions) {}
    };

    struct area_dimension_t {
        float _x, _y;
        float _w, _h;

        bool was_set;

        area_dimension_t(float x, float y, float w, float h) : _x(x), _y(y), _w(w), _h(h), was_set(true) {}

        area_dimension_t(float x, float y) : area_dimension_t(x, y, 10, 10) {}

        area_dimension_t() : area_dimension_t(-1, -1) { was_set = false; }
    };


    template<typename T>
    inline T operator&(T lhs, T rhs) {
        using _T = std::underlying_type_t<T>;
        return static_cast<T>(static_cast<_T>(lhs) & static_cast<_T>(rhs));
    }

    template<typename T>
    inline T operator|(T lhs, T rhs) {
        using _T = std::underlying_type_t<T>;
        return static_cast<T>(static_cast<_T>(lhs) | static_cast<_T>(rhs));
    }

    template<typename T>
    inline T &operator|=(T &lhs, T rhs) {
        lhs = lhs | rhs;
        return lhs;
    }

    template<typename T>
    inline T &operator++(T &lhs) {
        return (lhs = static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) + 1));
    }

    template<typename QEnum>
    const char *enum_to_str(const QEnum &value) {
        return QMetaEnum::fromType<QEnum>().valueToKey(static_cast<int>(value));
    }

    template<typename T>
    inline bool is_action_set(const T &in, T test) {
        return ((in & test) == test);
    }

    inline void append_str(std::string &str, const std::string &append) {
        str = str.empty() ? append : str + "+" + append;
    }

    struct area_t {
        bool read_only;
        std::string name;
        Type type;
        Actions actions;
        area_dimension_t dimension;
        size_t page;

        area_t(bool _ro, std::string _name, Type _type, Actions _actions, area_dimension_t dim, size_t _page)
                : read_only(_ro), name(std::move(_name)), type(_type), actions(_actions), dimension(dim), page(_page) {}

        area_t(qreal x, qreal y) : area_t(false, "", Type::TRANSIENT, Actions::TRANSIENT,
                                          area_dimension_t(x, y), 0) {}

        area_t() : area_t(false, "", Type::TRANSIENT, Actions::TRANSIENT,
                          area_dimension_t(), 0) {}

        [[nodiscard]]
        inline int type_index() const {
            return (static_cast<int>(type) - (static_cast<int>(Type::ITERATION_BEGIN) + 1));
        }

        inline std::string get_type_str() { return area::enum_to_str(type); }

        std::string get_actions_str() {
            std::string actions_str;

            if (is_action_set(actions, Actions::OCR)) append_str(actions_str, "OCR");
            if (is_action_set(actions, Actions::CONCEAL)) append_str(actions_str, "CONCEAL");
            if (is_action_set(actions, Actions::EXTRACT)) append_str(actions_str, "EXTRACT");
            if (is_action_set(actions, Actions::CLIPPING)) append_str(actions_str, "CLIPPING");

            return actions_str;
        }
    };
}

namespace stg {

    struct save_t {
        QString path, doc_uuid;
        Json::Value doc_json, areas_json;
    };

}

namespace std {
    template<>
    struct hash<QString> {
        std::size_t operator()(const QString &s) const {
            return qHash(s);
        }
    };
}

Q_DECLARE_METATYPE(area::Type)

Q_DECLARE_METATYPE(area::Actions)

#endif //DOC_VIEWER_TYPES_UTILS_H
