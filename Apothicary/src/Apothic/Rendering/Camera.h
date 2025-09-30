#pragma once
#include "DataTypes.h"

namespace apothic::graphics
{
    /* interface class -- not instantiated for any purpose */
    class Camera
    {
    public:
        virtual ~Camera() {}

        inline const unsigned int GetWidth() const { return m_ScreenWidth; }
        inline const unsigned int GetHeight() const { return m_ScreenHeight; }

        /* called when onResizeEvent to update projections */
        void SetScreenWidthHeight(unsigned int screenWidth, unsigned int screenHeight);
        virtual void OnScreenUpdate(unsigned int newWidth, unsigned int newHeight) = 0;

    protected:
        Camera(unsigned int screenWidth, unsigned int screenHeight);
        unsigned int m_ScreenWidth, m_ScreenHeight;
    };

    /* Orthographic camera -> used for 2d projections */
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(unsigned int screenWidth, unsigned int screenHeight);
        ~OrthographicCamera();

        inline argon::mat4* GetViewMatrix() const { return m_ViewMatrix; }
        virtual void OnScreenUpdate(unsigned int newWidth, unsigned int newHeight) override;
    private:
        argon::mat4* m_ViewMatrix;
    };

    /* Perspective Camera -> used for 3d projections */
    /* TODO u_MVP set per-instance*/
    /*class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(unsigned int screenWidth, unsigned int screenHeight);
        ~PerspectiveCamera() {}

        const argon::mat4& GetViewMatrix(const argon::vec4& vertexPosition) const;
        virtual void OnScreenUpdate(unsigned int newWidth, unsigned int newHeight) override;
    };*/
    

}