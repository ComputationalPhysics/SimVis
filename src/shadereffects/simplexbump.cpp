#include "simplexbump.h"

SimplexBump::SimplexBump()
{

}

SimplexBump::~SimplexBump()
{

}

QString SimplexBump::fragmentShaderDefines()
{
    QString defines;

    if(m_enabled) {
        defines.append("\n#define SIMPLEXBUMP\n");
    }

    return defines;
}

QString SimplexBump::vertexShaderDefines()
{
    QString defines;
    return defines;
}

QString SimplexBump::fragmentShaderLibrary()
{
    QString shaderLibrary;
    // Remember to include dependencies here
    shaderLibrary.append(contentFromFile(":/org.compphys.SimVis/renderables/shadereffects/simplex2.glsl"));
    shaderLibrary.append(contentFromFile(":/org.compphys.SimVis/renderables/shadereffects/simplexbump.glsl"));
    return shaderLibrary;
}

QString SimplexBump::vertexShaderLibrary()
{
    QString shaderLibrary;
    return shaderLibrary;
}

SimplexBump *SimplexBump::clone()
{
    SimplexBump *copy = new SimplexBump();
    copy->setIntensity(intensity());
    copy->setScale(scale());
    copy->setShadersDirty(shadersDirty());
    return copy;
}

void SimplexBump::setUniformValues(QOpenGLShaderProgram &shaderProgram)
{
    shaderProgram.setUniformValue("cp_bumpIntensity", m_intensity);
    shaderProgram.setUniformValue("cp_bumpScale", m_scale);
}

float SimplexBump::intensity() const
{
    return m_intensity;
}

float SimplexBump::scale() const
{
    return m_scale;
}

void SimplexBump::setIntensity(float arg)
{
    if (m_intensity == arg)
        return;

    m_intensity = arg;
    m_shadersDirty = true;
    emit intensityChanged(arg);
}

void SimplexBump::setScale(float arg)
{
    if (m_scale == arg)
        return;

    m_scale = arg;
    m_shadersDirty = true;
    emit scaleChanged(arg);
}
