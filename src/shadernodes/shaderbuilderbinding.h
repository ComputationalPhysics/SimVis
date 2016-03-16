#ifndef SHADERBUILDERBINDING_H
#define SHADERBUILDERBINDING_H

#include "shadernode.h"

#include <QObject>

class ShaderBuilderBinding : public ShaderNode
{
    Q_OBJECT
    Q_PROPERTY(QString property READ property WRITE setProperty NOTIFY propertyChanged)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)

public:
    explicit ShaderBuilderBinding(QObject *parent = 0);

    virtual bool setup(ShaderBuilder *shaderBuilder) override;
    QVariant defaultValue() const;
    QString property() const;

signals:
    void propertyChanged(QString property);

    void defaultValueChanged(QVariant defaultValue);

public slots:
    void setProperty(QString property);

    void setDefaultValue(QVariant defaultValue);

private:
    QString m_property;
    QVariant m_defaultValue = 0.0;
};

#endif // SHADERBUILDERBINDING_H