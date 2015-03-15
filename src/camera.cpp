#include "camera.h"
#include <QDateTime>

QMatrix4x4 Camera::projectionMatrix()
{
    // Calculate aspect ratio

    qreal aspect = qreal(m_viewportSize.width()) / qreal(m_viewportSize.height() ? m_viewportSize.height() : 1);

    // Reset projection
    m_projectionMatrix.setToIdentity();

    // Set perspective projection
    m_projectionMatrix.perspective(m_fieldOfView, aspect, m_nearPlane, m_farPlane);

    return m_projectionMatrix;
}

void Camera::setProjectionMatrix(const QMatrix4x4 &projectionMatrix)
{
    m_projectionMatrix = projectionMatrix;
}

QMatrix4x4 Camera::modelViewMatrix()
{
    m_modelViewMatrix.setToIdentity();
    if(!m_fixedPosition) {
        m_modelViewMatrix.translate(m_position);
    }

    // m_modelViewMatrix.lookAt(m_position, m_position + m_forwardVector, m_upVector);
    m_modelViewMatrix.rotate(90, 1, 0, 0);

    //m_modelViewMatrix.rotate(m_rotation);
    m_modelViewMatrix.rotate(m_tilt, 1, 0, 0);
    m_modelViewMatrix.rotate(m_pan, 0, 0, 1);

    return m_modelViewMatrix;
}

void Camera::setModelViewMatrix(const QMatrix4x4 &modelViewMatrix)
{
    m_modelViewMatrix = modelViewMatrix;
}

bool Camera::fixedPosition() const
{
    return m_fixedPosition;
}

QSize Camera::viewportSize() const
{
    return m_viewportSize;
}

float Camera::fieldOfView() const
{
    return m_fieldOfView;
}

float Camera::farPlane() const
{
    return m_farPlane;
}

float Camera::nearPlane() const
{
    return m_nearPlane;
}

bool Camera::hyperSpeed() const
{
    return m_hyperSpeed;
}

float Camera::moveSpeed() const
{
    return m_moveSpeed;
}

float Camera::hyperSpeedFactor() const
{
    return m_hyperSpeedFactor;
}

bool Camera::movingForward() const
{
    return m_movingForward;
}

bool Camera::movingBackward() const
{
    return m_movingBackward;
}

bool Camera::movingRight() const
{
    return m_movingRight;
}

bool Camera::movingLeft() const
{
    return m_movingLeft;
}

float Camera::mouseSensitivity() const
{
    return m_mouseSensitivity;
}

void Camera::setPosition(QVector3D arg)
{
    if (m_position == arg)
        return;

    m_position = arg;
    emit positionChanged(arg);
}

void Camera::setTilt(float arg)
{
    if (m_tilt == arg)
        return;

    m_tilt = arg;
    emit tiltChanged(arg);
}

void Camera::setPan(float arg)
{
    if (m_pan == arg)
        return;

    m_pan = arg;
    emit panChanged(arg);
}

void Camera::setRoll(float arg)
{
    if (m_roll == arg)
        return;

    m_roll = arg;
    emit rollChanged(arg);
}

void Camera::setFixedPosition(bool arg)
{
    if (m_fixedPosition == arg)
        return;

    m_fixedPosition = arg;
    emit fixedPositionChanged(arg);
}

void Camera::setViewportSize(QSize arg)
{
    if (m_viewportSize == arg)
        return;

    m_viewportSize = arg;
    emit viewportSizeChanged(arg);
}

void Camera::setFieldOfView(float arg)
{
    if (m_fieldOfView == arg)
        return;

    m_fieldOfView = arg;
    emit fieldOfViewChanged(arg);
}

void Camera::setFarPlane(float arg)
{
    if (m_farPlane == arg)
        return;

    m_farPlane = arg;
    emit farPlaneChanged(arg);
}

void Camera::setNearPlane(float arg)
{
    if (m_nearPlane == arg)
        return;

    m_nearPlane = arg;
    emit nearPlaneChanged(arg);
}

void Camera::setHyperSpeed(bool arg)
{
    if (m_hyperSpeed == arg)
        return;

    m_hyperSpeed = arg;
    emit hyperSpeedChanged(arg);
}

void Camera::setMoveSpeed(float arg)
{
    if (m_moveSpeed == arg)
        return;

    m_moveSpeed = arg;
    emit moveSpeedChanged(arg);
}

void Camera::setHyperSpeedFactor(float arg)
{
    if (m_hyperSpeedFactor == arg)
        return;

    m_hyperSpeedFactor = arg;
    emit hyperSpeedFactorChanged(arg);
}

void Camera::timerTicked()
{

    long currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    long timeDifference = currentTime-m_lastTime;
    float timeDifferenceSeconds = float(timeDifference)/1000.0;

    m_lastTime = currentTime;

    if(timeDifference > 1000) {
        return;
    }

    QVector3D forwardVector = this->forwardVector();
    QVector3D rightVector = this->rightVector();
    QVector3D translation;
    float speed = m_moveSpeed;
    if(m_hyperSpeed) {
        speed *= m_hyperSpeedFactor;
    }

    // Decide what to do based on velocity
    if(m_movingForward) {
        m_forwardSpeed = speed*timeDifferenceSeconds;
    } else if(m_movingBackward) {
        m_forwardSpeed = -speed*timeDifferenceSeconds;
    } else {
        m_forwardSpeed = 0;
    }

    if(m_movingRight) {
        m_rightSpeed = speed*timeDifferenceSeconds;
    } else if(m_movingLeft) {
        m_rightSpeed = -speed*timeDifferenceSeconds;
    } else {
        m_rightSpeed = 0;
    }

    translation += forwardVector*m_forwardSpeed;
    translation += rightVector*m_rightSpeed;
    setPosition(m_position + translation);
}

void Camera::setMovingForward(bool arg)
{
    m_movingForward = arg;
}

void Camera::setMovingBackward(bool arg)
{
    m_movingBackward = arg;
}

void Camera::setMovingRight(bool arg)
{
    m_movingRight = arg;
}

void Camera::setMovingLeft(bool arg)
{
    m_movingLeft = arg;
}

void Camera::mouseMoved(float deltaX, float deltaY)
{
    deltaX *= m_mouseSensitivity;
    deltaY *= m_mouseSensitivity;
    if(m_tilt - deltaY > -90 && m_tilt - deltaY < 90) {
        setTilt(m_tilt - deltaY);
    }

    setPan(m_pan - deltaX);
}

void Camera::setMouseSensitivity(float arg)
{
    if (m_mouseSensitivity == arg)
        return;

    m_mouseSensitivity = arg;
    emit mouseSensitivityChanged(arg);
}

Camera::Camera(QObject *parent) :
    QObject(parent),
    m_position(QVector3D(0,0,5)),
    m_tilt(0),
    m_pan(0),
    m_roll(0),
    m_fixedPosition(false),
    m_fieldOfView(65.0),
    m_farPlane(2000.0),
    m_nearPlane(0.1),
    m_hyperSpeed(false),
    m_moveSpeed(3.0),
    m_hyperSpeedFactor(4.0),
    m_movingForward(false),
    m_movingBackward(false),
    m_movingLeft(false),
    m_movingRight(false),
    m_forwardSpeed(0),
    m_rightSpeed(0),
    m_lastTime(0),
    m_mouseSensitivity(0.03),
    m_forwardVector(QVector3D(1.0, 0.0, 0.0)),
    m_rotation(QQuaternion(1.0, 0.0, 0.0, 0.0)),
    m_upVector(QVector3D(0.0, 0.0, 1.0))
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerTicked()));
    m_timer.setInterval(16);
    m_timer.start(16);
}

Camera::~Camera()
{

}

QVector3D Camera::position() const
{
    return m_position;
}

float Camera::tilt() const
{
    return m_tilt;
}

float Camera::pan() const
{
    return m_pan;
}

float Camera::roll() const
{
    return m_roll;
}

QVector3D Camera::forwardVector()
{
    float x = cos(m_pan*DEGTORAD)*cos(m_tilt*DEGTORAD);
    float y = sin(m_pan*DEGTORAD)*cos(m_tilt*DEGTORAD);
    float z = sin(m_tilt*DEGTORAD);
    return QVector3D(x,y,z);
}

QVector3D Camera::upVector()
{
    QVector3D forwardVector = this->forwardVector();
    float x = -forwardVector.z()*forwardVector.x()/sqrt(forwardVector.x()*forwardVector.x() + forwardVector.y()*forwardVector.y());
    float y = -forwardVector.z()*forwardVector.y()/sqrt(forwardVector.x()*forwardVector.x() + forwardVector.y()*forwardVector.y());
    float z = sqrt(forwardVector.x()*forwardVector.x() + forwardVector.y()*forwardVector.y());
    return QVector3D(x,y,z);
}

QVector3D Camera::rightVector()
{
    QVector3D forwardVector = this->forwardVector();
    QVector3D upVector = this->upVector();
    return QVector3D::crossProduct(forwardVector, upVector);
}