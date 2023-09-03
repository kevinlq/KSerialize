#pragma once

#include <QObject>
#include "KSerialize_global.h"

class KSERIALIZE_EXPORT SerializationHelper
{
    Q_DISABLE_COPY(SerializationHelper)
public:
    SerializationHelper() = default;
    virtual ~SerializationHelper() = default;

    virtual QVariant getProperty(const char *name) const = 0;
    virtual QVariant serializeSubtype(const QMetaProperty &property, const QVariant &value) const = 0;
    virtual QVariant serializeSubtype(int propertyType, const QVariant &value, const QByteArray &traceHint = {}) const = 0;

    virtual QVariant deserializeSubtype(const QMetaProperty &property, const QJsonValue &value, QObject *parent) const = 0;
    virtual QVariant deserializeSubtype(int propertyType, const QJsonValue &value, QObject *parent, const QByteArray &traceHint = {}) const = 0;
};
