#include "marchingcubes.h"
#include <iostream>
#include <QElapsedTimer>
using namespace std;

function<float (const QVector3D point)> MarchingCubes::scalarFieldEvaluator() const
{
    return m_scalarFieldEvaluator;
}

void MarchingCubes::setScalarFieldEvaluator(const function<float(const QVector3D pos)> &scalarFieldEvaluator)
{
    m_scalarFieldEvaluator = scalarFieldEvaluator;
    m_hasScalarField = true;
    setScalarFieldDirty(true);
    setDirty(true);
}

QColor MarchingCubes::color() const
{
    return m_color;
}

MarchingCubes::Mode MarchingCubes::mode() const
{
    return m_mode;
}

float MarchingCubes::alpha() const
{
    return m_alpha;
}

function<QVector4D (const QVector3D point)> MarchingCubes::colorEvaluator() const
{
    return m_colorEvaluator;
}

void MarchingCubes::setColorEvaluator(const function<QVector4D (const QVector3D point)> &colorEvaluator)
{
    setScalarFieldDirty(true);
    m_colorEvaluator = colorEvaluator;
}

MarchingCubes::MarchingCubes()
{

}

MarchingCubes::~MarchingCubes()
{

}

RenderableRenderer *MarchingCubes::createRenderer()
{
    return new MarchingCubesRenderer();
}

float MarchingCubes::threshold() const
{
    return m_threshold;
}

QVector3D MarchingCubes::min() const
{
    return m_min;
}

QVector3D MarchingCubes::max() const
{
    return m_max;
}

bool MarchingCubes::dirty() const
{
    return m_dirty;
}

QVector3D MarchingCubes::numVoxels() const
{
    return m_numVoxels;
}

bool MarchingCubes::hasScalarField() const
{
    return m_hasScalarField;
}

void MarchingCubes::setThreshold(float arg)
{
    if (m_threshold == arg)
        return;

    m_threshold = arg;
    setScalarFieldDirty(true);
    emit thresholdChanged(arg);
}

void MarchingCubes::setMin(QVector3D arg)
{
    if (m_min == arg)
        return;

    m_min = arg;
    setScalarFieldDirty(true);
    emit minChanged(arg);
}

void MarchingCubes::setMax(QVector3D arg)
{
    if (m_max == arg)
        return;

    m_max = arg;
    setScalarFieldDirty(true);
    emit maxChanged(arg);
}

void MarchingCubes::setDirty(bool arg)
{
    if (m_dirty == arg)
        return;

    m_dirty = arg;
    emit dirtyChanged(arg);
}

void MarchingCubes::setNumVoxels(QVector3D arg)
{
    if (m_numVoxels == arg)
        return;

    m_numVoxels = arg;
    setScalarFieldDirty(true);
    emit numVoxelsChanged(arg);
}

void MarchingCubes::setColor(QColor arg)
{
    if (m_color == arg)
        return;

    setScalarFieldDirty(true);
    m_color = arg;
    emit colorChanged(arg);
}

void MarchingCubes::setMode(MarchingCubes::Mode arg)
{
    if (m_mode == arg)
        return;

    m_mode = arg;
    setDirty(true);
    emit modeChanged(arg);
}

void MarchingCubes::setAlpha(float arg)
{
    if (m_alpha == arg)
        return;
    setDirty(true);
    m_alpha = arg;
    emit alphaChanged(arg);
}
bool MarchingCubes::scalarFieldDirty() const
{
    return m_scalarFieldDirty;
}

void MarchingCubes::setScalarFieldDirty(bool scalarFieldDirty)
{
    m_scalarFieldDirty = scalarFieldDirty;
    if(m_scalarFieldDirty) setDirty(true);
}


MarchingCubesRenderer::MarchingCubesRenderer()
{
    m_numberOfVBOs = 4;
}

void MarchingCubesRenderer::synchronize(Renderable *renderable)
{
    MarchingCubes* marchingCubes = static_cast<MarchingCubes*>(renderable);
    if(!m_isInitialized) {
        generateVBOs();
        m_isInitialized = true;
    }

    if(marchingCubes->dirty()) {
        if(marchingCubes->hasScalarField() && marchingCubes->m_scalarFieldDirty) {
            if(marchingCubes->m_colorEvaluator != 0) {
                m_generator.m_colorEvaluator = marchingCubes->m_colorEvaluator;
                m_generator.m_hasColorEvaluator = true;
            } else {
                m_generator.setColor(marchingCubes->color());
                m_generator.m_hasColorEvaluator = false;
            }

            m_generator.setScalarFieldEvaluator(marchingCubes->scalarFieldEvaluator());
            m_generator.generateSurface(marchingCubes->min(), marchingCubes->max(), marchingCubes->numVoxels(), marchingCubes->threshold());
            uploadVBOs();
            marchingCubes->setScalarFieldDirty(false);
        }

        m_color = QVector4D(marchingCubes->color().redF(), marchingCubes->color().greenF(), marchingCubes->color().blueF(), marchingCubes->color().alphaF());
        m_mode = marchingCubes->mode();
        m_alpha = marchingCubes->alpha();
        marchingCubes->setDirty(false);
    }
}

void MarchingCubesRenderer::render()
{
    if(m_triangleIndexCount == 0) {
        return;
    }

    QMatrix4x4 modelViewProjectionMatrix = m_projectionMatrix*m_modelViewMatrix;
    program().setUniformValue("modelViewProjectionMatrix", modelViewProjectionMatrix);
    program().setUniformValue("lightPosition", QVector3D(10, 0, 10));
    program().setUniformValue("uniformColor", m_color);
    program().setUniformValue("alpha", m_alpha);

    // Tell OpenGL which VBOs to use
    glFunctions()->glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program().attributeLocation("a_position");
    program().enableAttributeArray(vertexLocation);
    glFunctions()->glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(MarchingCubesVBOData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    vertexLocation = program().attributeLocation("a_normal");
    program().enableAttributeArray(vertexLocation);
    glFunctions()->glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(MarchingCubesVBOData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    vertexLocation = program().attributeLocation("a_color");
    program().enableAttributeArray(vertexLocation);
    glFunctions()->glVertexAttribPointer(vertexLocation, 4, GL_FLOAT, GL_FALSE, sizeof(MarchingCubesVBOData), (const void *)offset);

    // Draw cube geometry using indices from VBO 1
    if(m_mode == MarchingCubes::FRONT_AND_BACK || m_mode == MarchingCubes::FRONT) {
        glFunctions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
        program().setUniformValue("normalVectorSign", 1.0f);
        glDrawElements(GL_TRIANGLES, m_triangleIndexCount, GL_UNSIGNED_INT, 0);
    }

    if(m_mode == MarchingCubes::FRONT_AND_BACK || m_mode == MarchingCubes::BACK) {
        glFunctions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[2]);
        program().setUniformValue("normalVectorSign", -1.0f);
        glDrawElements(GL_TRIANGLES, m_triangleIndexCount, GL_UNSIGNED_INT, 0);
    }

    if(m_mode == MarchingCubes::LINES) {
        glFunctions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[3]);
        program().setUniformValue("normalVectorSign", 1.0f);
        glDrawElements(GL_LINES, m_lineIndexCount, GL_UNSIGNED_INT, 0);
    }

    program().disableAttributeArray(vertexLocation);
}

void MarchingCubesRenderer::uploadVBOs()
{
    if(m_generator.m_data.size() == 0) return;
    // Transfer vertex data to VBO 0
    glFunctions()->glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glFunctions()->glBufferData(GL_ARRAY_BUFFER, m_generator.m_data.size() * sizeof(MarchingCubesVBOData), &m_generator.m_data[0], GL_STATIC_DRAW);

    // Transfer index data for front triangles to VBO 1
    glFunctions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    glFunctions()->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_generator.m_trianglesFront.size() * sizeof(Triangle), &m_generator.m_trianglesFront[0], GL_STATIC_DRAW);

    // Transfer index data for back triangles to VBO 2
    glFunctions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[2]);
    glFunctions()->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_generator.m_trianglesBack.size() * sizeof(Triangle), &m_generator.m_trianglesBack[0], GL_STATIC_DRAW);

    // Transfer index data for back triangles to VBO 2
    glFunctions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[3]);
    glFunctions()->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_generator.m_lines.size() * sizeof(TriangleLines), &m_generator.m_lines[0], GL_STATIC_DRAW);

    m_triangleIndexCount = 3*m_generator.m_trianglesFront.size();
    m_lineIndexCount = 6*m_generator.m_lines.size();
}

void MarchingCubesRenderer::beforeLinkProgram()
{
    program().addShaderFromSourceFile(QOpenGLShader::Vertex, ":/org.compphys.SimVis/renderables/marchingcubes/marchingcubes.vsh");
    program().addShaderFromSourceFile(QOpenGLShader::Fragment, ":/org.compphys.SimVis/renderables/marchingcubes/marchingcubes.fsh");
}