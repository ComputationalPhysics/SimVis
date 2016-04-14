/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef SPHEREGEOMETRYNEW_H
#define SPHEREGEOMETRYNEW_H

#include <Qt3DRender/qgeometry.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

class QSphereGeometryPrivate;
class QAttribute;
class QBuffer;

class QT3DRENDERSHARED_EXPORT SphereGeometryNew : public QGeometry
{
    Q_OBJECT
    Q_PROPERTY(int rings READ rings WRITE setRings NOTIFY ringsChanged)
    Q_PROPERTY(int slices READ slices WRITE setSlices NOTIFY slicesChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(bool generateTangents READ generateTangents WRITE setGenerateTangents NOTIFY generateTangentsChanged)
    Q_PROPERTY(Qt3DRender::QAttribute *positionAttribute READ positionAttribute CONSTANT)
    Q_PROPERTY(Qt3DRender::QAttribute *normalAttribute READ normalAttribute CONSTANT)
    Q_PROPERTY(Qt3DRender::QAttribute *texCoordAttribute READ texCoordAttribute CONSTANT)
    Q_PROPERTY(Qt3DRender::QAttribute *tangentAttribute READ tangentAttribute CONSTANT)
    Q_PROPERTY(Qt3DRender::QAttribute *indexAttribute READ indexAttribute CONSTANT)

public:
    void init();

    bool m_generateTangents;
    int m_rings;
    int m_slices;
    float m_radius;
    QAttribute *m_positionAttribute;
    QAttribute *m_normalAttribute;
    QAttribute *m_texCoordAttribute;
    QAttribute *m_tangentAttribute;
    QAttribute *m_indexAttribute;
    QBuffer *m_vertexBuffer;
    QBuffer *m_indexBuffer;

public:
    explicit SphereGeometryNew(QNode *parent = Q_NULLPTR);
    ~SphereGeometryNew();

    void updateVertices();
    void updateIndices();

    bool generateTangents() const;
    int rings() const;
    int slices() const;
    float radius() const;

    QAttribute *positionAttribute() const;
    QAttribute *normalAttribute() const;
    QAttribute *texCoordAttribute() const;
    QAttribute *tangentAttribute() const;
    QAttribute *indexAttribute() const;

public Q_SLOTS:
    void setRings(int rings);
    void setSlices(int slices);
    void setRadius(float radius);
    void setGenerateTangents(bool gen);

Q_SIGNALS:
    void radiusChanged(float radius);
    void ringsChanged(int rings);
    void slicesChanged(int slices);
    void generateTangentsChanged(bool generateTangents);

protected:
    SphereGeometryNew(QSphereGeometryPrivate &dd, QNode *parent = Q_NULLPTR);

private:
    Q_DECLARE_PRIVATE(QSphereGeometry)
};

} // Qt3DRender

QT_END_NAMESPACE

#endif // SPHEREGEOMETRYNEW_H
