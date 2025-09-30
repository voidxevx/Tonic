#include "Camera.h"

namespace apothic::graphics
{
    /* Camera interface class */
    Camera::Camera(unsigned int screenWidth, unsigned int screenHeight)
        : m_ScreenWidth(screenWidth)
        , m_ScreenHeight(screenHeight)
    {}

    void Camera::SetScreenWidthHeight(unsigned int screenWidth, unsigned int screenHeight)
    {
        m_ScreenWidth = screenWidth;
        m_ScreenHeight = screenHeight;
        OnScreenUpdate(m_ScreenWidth, m_ScreenHeight);
    }



    OrthographicCamera::OrthographicCamera(unsigned int screenWidth, unsigned int screenHeight)
        : Camera(screenWidth, screenHeight)
    {
        m_ViewMatrix = argon::orthographicViewMatrix(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight, -1.0f, 1.0f);
    }

    OrthographicCamera::~OrthographicCamera()
    {
        free(m_ViewMatrix);
        m_ViewMatrix = nullptr;
    }

    void OrthographicCamera::OnScreenUpdate(unsigned int newWidth, unsigned int newHeight)
    {
        free(m_ViewMatrix);
        m_ViewMatrix = argon::orthographicViewMatrix(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight, -1.0f, 1.0f);
    }

}