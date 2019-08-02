//
// Created by pornosaur on 25.7.19.
//

#ifndef DOC_VIEWER_TYPES_UTILS_H
#define DOC_VIEWER_TYPES_UTILS_H

#include <QVariant>
#include <QMetaEnum>
#include <QString>

#include <string>
#include <functional>

namespace area {
    Q_NAMESPACE

    enum class Type : unsigned int {
        ITERATION_BEGIN,    //Add new type above begin
        TEXT,
        IMAGE,
        LOGO,
        SYNC,
        ITERATION_END
    };

    Q_ENUM_NS(Type)

    enum class Actions : unsigned int {
        OCR = 0x01,
        CONCEAL = 0x02,
        EXTRACT = 0x04,
        CLIPPING = 0x08
    };

    struct area_dimension_t {

        float _x, _y;
        float _w, _h;

        area_dimension_t(float x, float y, float w, float h) : _x(x), _y(y), _w(w), _h(h) {}

        area_dimension_t(float x, float y) : area_dimension_t(x, y, 10, 10) {}

        area_dimension_t() : area_dimension_t(-1, -1) {}
    };

    struct area_t {
        std::string name;
        Type type;
        Actions actions;
        area_dimension_t dimension;
        unsigned int page;

        area_t() : name(""), type(Type::TEXT), actions(Actions::OCR), dimension(area_dimension_t()), page(1) {}
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

#endif //DOC_VIEWER_TYPES_UTILS_H
