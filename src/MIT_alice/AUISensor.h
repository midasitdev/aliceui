#pragma once

#include "AUIAPIDef.h"

#include <glm/glm.hpp>
class AUIWidget;
class ALICEUI_API AUISensor
{
protected:
    AUISensor() noexcept = default;
public:
    virtual ~AUISensor() noexcept = default;
    void _set_owner_widget(AUIWidget*  pWidget) {
        m_pWidget = std::move(pWidget);
    }
protected:
    void Invalidate();

private:
    AUIWidget* m_pWidget = nullptr;
public:

    inline virtual bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale = 1.0f) = 0;
    inline virtual void GetBoundingSphere(glm::vec3& c, float& r ) const = 0;
    virtual float GetHitDistance()  const = 0;
    //virtual void SetAABB(float left, float top, float right, float bottom, float front, float back) = 0;
    //virtual glm::vec3 GetHitPos() const = 0;
};
//
//class ALICEUI_API AUIPanelSensor : public AUISensor
//{
//public:
//    AUIPanelSensor() = default;
//    ~AUIPanelSensor() override = default;
//
//    inline bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override
//    {
//
//        return false;
//    }
//    float GetHitDistance() const override {
//        return m_fHitDistance;
//    }
//    glm::vec3 GetHitPos() const  {
//        return { m_vHitPos, 0.0f };
//    }
//    glm::vec2 GetHitPosOnRect() const
//    {
//        return m_vHitPos - glm::vec2(m_vRectangle);
//    }
//    //     void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
//    //         this->SetRectangle(left, top, right - left, bottom - top);
//    //     }
//
//    void SetRectangle(float x, float y, float width, float height) {
//        m_vRectangle = glm::vec4(x, y, x + width, y + height);
//    }
//private:
//    glm::vec2 m_vHitPos;
//    glm::vec4 m_vRectangle;
//    float m_fHitDistance = 0.0f;
//
//    // Optimization Hint
//    bool m_IsBasePlane = true;
//};

class ALICEUI_API AUIRectangleSensor : public AUISensor
{
public:
    AUIRectangleSensor() = default;
    ~AUIRectangleSensor() override = default;

    void SetMatrix(const glm::mat4& matSensor) ;
    inline bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale = 1.0f) override;
    inline void GetBoundingSphere(glm::vec3& c, float& r) const override
    {
        auto w = m_vRectangle[2] - m_vRectangle[0];
        auto h = m_vRectangle[3] - m_vRectangle[1];

        r = glm::sqrt(w * w + h * h) * 0.5f;
        auto o = glm::vec4(
            m_vRectangle[0] + w * 0.5f,
            m_vRectangle[1] + h * 0.5f,
            0.f, 1.f);

        c = glm::vec3(m_matSensor * o);
    }
    float GetHitDistance() const override {
        return m_fHitDistance;
    }
    glm::vec3 GetHitPos() const  {
        return { m_vHitPos, 0.0f };
    }
    glm::vec2 GetHitPosOnRect() const
    {
        return m_vHitPos - glm::vec2(m_vRectangle);
    }
//     void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
//         this->SetRectangle(left, top, right - left, bottom - top);
//     }

    void SetRectangle(float x, float y, float width, float height) {
        m_vRectangle = glm::vec4(x, y, x + width, y + height);
        Invalidate();
    }
private:
    glm::vec2 m_vHitPos;
    glm::mat4 m_matSensor = glm::mat4(1.f);
    glm::mat4 m_matSensorInv = glm::mat4(1.f);
    glm::vec4 m_vRectangle;
    float m_fHitDistance = 0.0f;

    // Optimization Hint
    bool m_IsBasePlane = true;
};

class ALICEUI_API AUIBoxSensor : public AUISensor
{
public:
    AUIBoxSensor() = default;
    ~AUIBoxSensor() override = default;

    inline void GetBoundingSphere(glm::vec3& c, float& r) const override
    {
        auto d = m_vBoxMax - m_vBoxMin;

        r = glm::length(d) * 0.5f;
        auto o = m_vBoxMin + d * 0.5f;

        c = glm::vec3(m_matSensor * glm::vec4(o,1.f));
    }
    void SetMatrix(const glm::mat4& matSensor)  {
        m_matSensor = matSensor;
        m_matSensorInv = glm::inverse(matSensor);
    }

    inline bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale = 1.0f) override;
    float GetHitDistance() const override {
        return m_fHitDistance;
    }
    glm::vec3 GetHitPos() const  {
        return m_vHitPos;
    }
//     void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
//         this->SetBox({ left, top, front }, { right, bottom, back });
//     }

    void SetBox(glm::vec3 minBox, glm::vec3 maxBox) {
        m_vBoxMin = minBox;
        m_vBoxMax = maxBox;
        Invalidate();
    }
private:
    glm::vec3 m_vHitPos;
    glm::mat4 m_matSensor = glm::mat4(1.f);
    glm::mat4 m_matSensorInv = glm::mat4(1.f);
    glm::vec3 m_vBoxMin;
    glm::vec3 m_vBoxMax;
    float m_fHitDistance = 0.0f;
};
