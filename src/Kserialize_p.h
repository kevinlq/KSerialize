﻿#pragma once

#include <QMetaType>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QFile>
#include <QTemporaryFile>
#include <QDir>
#include <QRect>
#include <QRect>
#include <QPoint>
#include <QPointF>
#include <QPolygon>
#include <QLine>
#include <QBitArray>
#include <QUuid>
#include <QLocale>
#include <QTextStream>
#include <QDate>
#include <QDateTime>
#include <QUrl>
#include <QDebug>
#include <QVarLengthArray>
#include <QReadWriteLock>
#include <QException>
#include <QRegularExpression>

#include <QLoggingCategory>

#include "KSerialize.h"
#include <QtCore/private/qobject_p.h>

Q_LOGGING_CATEGORY(logSerialize, "kserial.serialize")
Q_LOGGING_CATEGORY(logDeSerialze, "kserial.deserialize")


template <class Size>
static inline QVariant serializeSize(const Size &size)
{
    return QVariant(QJsonArray{size.width(), size.height()});
}

template <class Size>
static inline Size deserializeSize(const QJsonArray &array)
{
    Size s(-1, -1);
    if(2 == array.size())
    {
        auto width  = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto height = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        s.setWidth(width);
        s.setHeight(height);
    }
    return s;
}

template <class Rect>
static inline QVariant serializeRect(const Rect &r)
{
    return QVariant(QJsonArray{r.x(), r.y(), r.width(), r.height()});
}

template <class Rect>
static inline Rect deserializeRect(const QJsonArray &array)
{
    Rect r(-1, -1, -1, -1);
    if(4 == array.size())
    {
        auto x      = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto y      = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        auto width  = (array[2].type() == QJsonValue::Double) ? array[2].toDouble(-1) : array[2].toInt(-1);
        auto height = (array[3].type() == QJsonValue::Double) ? array[3].toDouble(-1) : array[3].toInt(-1);
        r = Rect(x, y, width, height);
    }
    return r;
}

template <class Point>
static inline QVariant serializePoint(const Point &point)
{
    return QVariant(QJsonArray{point.x(), point.y()});
}

template <class Point>
static inline Point deserializePoint(const QJsonArray &array)
{
    Point p(-1, -1);
    if(2 == array.size())
    {
        auto x = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto y = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        p.setX(x);
        p.setY(y);
    }
    return p;
}

template <class Line>
static inline QVariant serializeLine(const Line &p)
{
    return QVariant(QJsonArray{p.x1(), p.y1(), p.x2(), p.y2()});
}

template <class Line>
static inline Line deserializeLine(const QJsonArray &array)
{
    Line l(-1, -1, -1, -1);
    if(4 == array.size())
    {
        auto x1 = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto y1 = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        auto x2 = (array[2].type() == QJsonValue::Double) ? array[2].toDouble(-1) : array[2].toInt(-1);
        auto y2 = (array[3].type() == QJsonValue::Double) ? array[3].toDouble(-1) : array[3].toInt(-1);
        l = Line(x1, y1, x2, y2);
    }
    return l;
}
template <class Polygon>
static inline QVariant serializePolygon(const Polygon &p)
{
    QVariantList array;
    for (int i = 0; i < p.count(); ++i)
    {
        array << serializePoint(p.at(i));
    }
    return array;
}
template <class BitArray>
static inline QVariant serializeBitArray(const BitArray &b)
{
    QVariantList array;
    for (int i = 0; i < b.count(); ++i)
    {
        array << b.at(i);
    }
    return array;
}

class KException : public QException
{
public:
    KException(const QByteArray &what) : m_what(what) {}
    const char *what() const noexcept final {return m_what.constData();}

    virtual void raise() const override { throw *this;}
    virtual KException *clone() const override {return new KException(QByteArray());}
private:
    QByteArray m_what;
};

class KSerializePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(KSerialize)
public:
    struct AssociationInfo
    {
        AssociationInfo(int key, int value) : keyType(key), valueType(value) {}
        int keyType = QMetaType::UnknownType;
        int valueType = QMetaType::UnknownType;

        bool isValid() const {return keyType != QMetaType::UnknownType && valueType != QMetaType::UnknownType;}
    };

    QVariant serializeValue(int propertyType, const QVariant &value) const;
    QVariant deserializeValue(int propertyType, const QVariant &value) const;

    //! 基本几何类型序列化
    bool canConvertGeometty(int metaTypeId) const;
    QVariant serializeGeometry(int propertyType, const QVariant &value) const;

    //! 基础数据类型
    bool canConvertBasicType(int metaTypeId) const;
    QVariant serializeBasic(int propertyType, const QVariant &value) const;
    QVariant deserializeBasic(int propertyType, const QVariant &value) const;

    //! QObject 指针初始化
    bool canConvertObject(int metaTypeId) const;
    QVariant serializeObject(int propertyType, const QVariant &value) const;
    QVariant deserializeObject(int propertyType, const QVariant &value) const;
    bool deserializeProperties(const QMetaObject *metaObject, QObject *object, const QVariant &value) const;

    //! List 容器 序列化
    bool canConvertList(int metaTypeId) const;
    QVariant serializeList(int propertyType, const QVariant &value) const;
    QVariant deserializeList(int propertyType, const QVariant &value) const;

    //! 解析某个容器组合类型
    AssociationInfo tryParseSequenceInfo(int metaTypeId) const;


    template<class TContainer>
    TContainer deserializeArray(int propertyType, const QJsonArray &array, QObject *parent) const;
};

inline QVariant KSerializePrivate::serializeValue(int propertyType, const QVariant &value) const
{
    Q_UNUSED(propertyType);
    return value;
}

inline QVariant KSerializePrivate::deserializeValue(int propertyType, const QVariant &value) const
{
    Q_UNUSED(propertyType);
    return value;
}

inline bool KSerializePrivate::canConvertGeometty(int metaTypeId) const
{
    static const QVector<int> types {
        QMetaType::QSize,       QMetaType::QSizeF,
        QMetaType::QPoint,      QMetaType::QPointF,
        QMetaType::QLine,       QMetaType::QLineF,
        QMetaType::QRect,       QMetaType::QRectF,
        QMetaType::QPolygon,    QMetaType::QPolygonF,
    };
    return types.contains(metaTypeId);
}

inline QVariant KSerializePrivate::serializeGeometry(int propertyType, const QVariant &value) const
{
    switch (propertyType)
    {
    case QMetaType::QSize:      return serializeSize(value.toSize());
    case QMetaType::QSizeF:     return serializeSize(value.toSizeF());
    case QMetaType::QPoint:     return serializePoint(value.toPoint());
    case QMetaType::QPointF:    return serializePoint(value.toPointF());
    case QMetaType::QLine:      return serializeLine(value.toLine());
    case QMetaType::QLineF:     return serializeLine(value.toLineF());
    case QMetaType::QRect:      return serializeRect(value.toRect());
    case QMetaType::QRectF:     return serializeRect(value.toRectF());
    case QMetaType::QPolygon:   return serializePolygon(value.value<QPolygon>());
    case QMetaType::QPolygonF:  return serializePolygon(value.value<QPolygonF>());
    default:                    throw  KException{ QByteArray("Invalid type id ") +
                         QByteArray(QMetaType::typeName(propertyType))};
    }
}

inline bool KSerializePrivate::canConvertBasicType(int metaTypeId) const
{
    static const QVector<int> types {
        QMetaType::Bool,        QMetaType::QString,
        QMetaType::Int,         QMetaType::UInt,
        QMetaType::Double,      QMetaType::Float,
        QMetaType::QDate,       QMetaType::QTime,
        QMetaType::QDateTime,   QMetaType::QBitArray,
        QMetaType::QUrl,        QMetaType::QLocale,
        QMetaType::QUuid,       QMetaType::QByteArray,
        QMetaType::QFont,       QMetaType::QPixmap,
        QMetaType::QBrush,      QMetaType::QColor,
        QMetaType::QPalette,    QMetaType::QIcon,
        QMetaType::QImage,      QMetaType::QBitmap,
        QMetaType::QCursor,     QMetaType::QPen
    };
    return types.contains(metaTypeId);
}

inline QVariant KSerializePrivate::serializeBasic(int propertyType, const QVariant &value) const
{
    switch (propertyType)
    {
    case QMetaType::Bool:               return value.toBool();
    case QMetaType::QString:            return value.toString();
    case QMetaType::Int:                return value.toInt();
    case QMetaType::UInt:               return value.toUInt();
    case QMetaType::Double:             return value.toDouble();
    case QMetaType::Float:              return value.toFloat();
    case QMetaType::QDate:
    case QMetaType::QTime:
    case QMetaType::QDateTime:
    case QMetaType::QUuid:
    case QMetaType::QUrl:
    case QMetaType::QFont:
    case QMetaType::QPixmap:
    case QMetaType::QBrush:
    case QMetaType::QColor:
    case QMetaType::QPalette:
    case QMetaType::QImage:
    case QMetaType::QIcon:
        return value.toString();
    //    case QMetaType::QBitmap:          return serializeBitArray(value.toBitArray());
    //    case QMetaType::QCursor:            return value.toLocale().name();
    //    case QMetaType::QPen:         return value.toString();
    case QMetaType::QBitArray:          return serializeBitArray(value.toBitArray());
    case QMetaType::QLocale:            return value.toLocale().name();
    case QMetaType::QByteArray:         return value.toString();
    default:                    throw  KException{ QByteArray("Invalid type id ") +
                         QByteArray(QMetaType::typeName(propertyType))};
    }
}

inline QVariant KSerializePrivate::deserializeBasic(int propertyType, const QVariant &value) const
{
    const auto v = value;
    switch (propertyType)
    {
    case QMetaType::Bool:               return v.toBool();
    case QMetaType::QString:            return v.toString();
    case QMetaType::Int:                return v.toInt();
    case QMetaType::UInt:               return v.toUInt();
    case QMetaType::Double:             return v.toDouble();
    case QMetaType::Float:              return v.toFloat();
    case QMetaType::QDate:              return v.toDate();
    case QMetaType::QTime:              return v.toTime();
    case QMetaType::QDateTime:          return v.toDateTime();
    case QMetaType::QUuid:              return v.toUuid();
    case QMetaType::QUrl:               return v.toUrl();
    case QMetaType::QBitArray:          return v.toBitArray();
    case QMetaType::QLocale:            return v.toLocale();
    case QMetaType::QByteArray:         return v.toByteArray();
    case QMetaType::QFont:              return v;
    case QMetaType::QColor:             return v;
    default:    			throw KException(QByteArray("Failed to deserialze JSON-value to type ") +
                         QMetaType::typeName(propertyType) +
                         QByteArray("because the given JSON-value failed strict validation"));
    }
}

inline bool KSerializePrivate::canConvertObject(int metaTypeId) const
{
    auto flags = QMetaType(metaTypeId).flags();
    return flags.testFlag(QMetaType::PointerToQObject);
}

inline QVariant KSerializePrivate::serializeObject(int propertyType, const QVariant &value) const
{
    Q_Q(const KSerialize);
    QVariantMap rValue;
    auto object = value.value<QObject*>();
    if (!object)
    {
        qCDebug(logSerialize) << __FUNCTION__ << "line:" <<__LINE__
                             << "object is null." << propertyType;
        return rValue;
    }

    const QMetaObject *metaObject = object->metaObject();
    if(nullptr == metaObject)
    {
        throw KException(QByteArray("Unable to get metaobject for type ") + QMetaType::typeName(propertyType));
    }

    int i = metaObject->indexOfProperty("objectName") + 1;
    for(; i < metaObject->propertyCount(); i++)
    {
        auto property = metaObject->property(i);
        rValue[QString::fromUtf8(property.name())] = q->serializeSubtype(property, property.read(object));
    }
    return rValue;
}

inline QVariant KSerializePrivate::deserializeObject(int propertyType, const QVariant &value) const
{
    if(value.isNull())
    {
        return QVariant::fromValue<QObject*>(nullptr);
    }

    auto metaObject = QMetaType(propertyType).metaObject();
    if (!metaObject)
    {
        throw KException(QByteArray("Unable to get metaobject for type ") +
                         QMetaType::typeName(propertyType));
    }

    auto object = metaObject->newInstance(Q_ARG(QObject*, parent));
    if (!object)
    {
        throw KException(QByteArray("Failed to construct object of type ") +
                                       metaObject->className() +
                                       QByteArray(" (Does the constructor \"Q_INVOKABLE class(QObject*);\" exist?)"));
    }

    deserializeProperties(metaObject, object, value);

    return QVariant::fromValue(object);
}

inline bool KSerializePrivate::deserializeProperties(const QMetaObject *metaObject, QObject *object, const QVariant &value) const
{
    Q_Q(const KSerialize);

    QSet<QByteArray> reqProps;
    auto i = metaObject->indexOfProperty("objectName") + 1;
    for(; i < metaObject->propertyCount(); i++)
    {
        auto property = metaObject->property(i);
        reqProps.insert(property.name());
    }

    auto jsValue = QJsonValue::fromVariant(value);
    if(jsValue.isArray())
    {
        qCWarning(logDeSerialze) << __FUNCTION__ << "line:" <<__LINE__
                                 << "value is json array." << jsValue.type();
        return false;
    }
    auto jsArray = jsValue.toObject();

    auto index = 0;
    for (auto it = jsArray.constBegin(); it != jsArray.constEnd(); it++)
    {
        if (it.key() == QStringLiteral("@class"))
        {
            continue;
        }
        const auto key = it.key().toUtf8();
        const auto propIndex = metaObject->indexOfProperty(key);
        if (propIndex != -1)
        {
            const auto property = metaObject->property(propIndex);

            const auto v = q->deserializeSubtype(property, it.value(), object);
            const auto bResult = property.write(object,  v);
            if(!bResult)
            {
                qCWarning(logDeSerialze) << __FUNCTION__ << "line:" <<__LINE__
                                         << " write property false, " << key
                                         << "userType:" << property.userType() << QMetaType::typeName(property.userType())
                                         << "value:" << v;
            }
            reqProps.remove(property.name());
        }
        else
        {
            object->setProperty(key, q->deserializeSubtype(QMetaType::UnknownType, it.value(), object, "[" + QByteArray::number(index++) + "]"));
        }
    }
    return true;
}

inline bool KSerializePrivate::canConvertList(int metaTypeId) const
{
    return QVariant{metaTypeId, nullptr}.canConvert(QMetaType::QVariantList);
}

inline QVariant KSerializePrivate::serializeList(int propertyType, const QVariant &value) const
{
    Q_Q(const KSerialize);
    if (!value.canConvert<QVariantList>())
    {
        throw KException( QByteArray("type ") +
                         QMetaType::typeName(propertyType) +
                         QByteArray(" cannot convert."));
    }

    auto index = 0;
    QJsonArray array;

    for (const auto &element : value.value<QSequentialIterable>())
    {
        array.append(QJsonValue::fromVariant(q->serializeSubtype(element.userType(), element,"[" + QByteArray::number(index++) + "]")));
    }
    return array;
}

inline QVariant KSerializePrivate::deserializeList(int propertyType, const QVariant &value) const
{
    qCDebug(logDeSerialze) << __FUNCTION__ << "line:" <<__LINE__
                         << "name:" << QMetaType::typeName(propertyType)
                         << "type:" << propertyType << " value->userType:" << value.userType()
                         << " value:" << value;
    QVariant list{};

    const auto array = QJsonValue::fromVariant(value).toArray();
    if(QMetaType::QStringList == propertyType)
    {
        return deserializeArray<QVariantList>(QMetaType::QString, array, nullptr);
    }
    else if (QMetaType::QJsonValue == propertyType)
    {
        return deserializeArray<QVariantList>(QMetaType::QVariant, array, nullptr);
    }
    else
    {
        const auto customType = tryParseSequenceInfo(propertyType);
        if( QMetaType::UnknownType != customType.valueType)
        {
            return deserializeArray<QVariantList>(customType.valueType, array, nullptr);
        }

        qCDebug(logDeSerialze) << __FUNCTION__ << "line:"
                             << "un support,Invalid type id " << QMetaType::typeName(propertyType);

        throw  KException{ QByteArray("un support,Invalid type id ") +
                         QByteArray(QMetaType::typeName(propertyType))};
    }

    return list;
}

inline KSerializePrivate::AssociationInfo KSerializePrivate::tryParseSequenceInfo(int metaTypeId) const
{
    if (metaTypeId == QMetaType::QVariantMap ||
        metaTypeId == QMetaType::QVariantHash)
    {
        return AssociationInfo{QMetaType::QString, QMetaType::UnknownType};
    }
    else
    {
        // QList<float>, QList<double>, QList<bool>
        static const QRegularExpression mapTypeRegex{
            QStringLiteral(R"__(^((?![0-9_])(?:\w|::)*\w)\s*<\s*(.*?)\s*>$)__"),
            QRegularExpression::UseUnicodePropertiesOption
        };
        auto match = mapTypeRegex.match(QString::fromUtf8(QMetaType::typeName(metaTypeId)));
        if (match.hasMatch())
        {
            // parse match, using <> and , rules
            return {QMetaType::type(match.captured(1).toUtf8().trimmed()),
                    QMetaType::type(match.captured(2).toUtf8().trimmed())};
        }
    }

    return {QMetaType::UnknownType, QMetaType::UnknownType};
}

template<class TContainer>
TContainer KSerializePrivate::deserializeArray(int propertyType, const QJsonArray &array, QObject *parent) const
{
    Q_Q(const KSerialize);
    TContainer list;

    auto index = 0;
    for (const auto &element : array)
    {
        auto value =(q->deserializeSubtype(propertyType, element, parent, "[" + QByteArray::number(index++) + "]"));
        list.append(value);
    }
    return list;
}

