#pragma once

#include "AUIAPIDef.h"

#include <glm/glm.hpp>

class ALICEUI_API AUISensor
{
protected:
    AUISensor() noexcept = default;
public:
    virtual ~AUISensor() noexcept = default;
    virtual void SetMatrix(const glm::mat4& matSensor) = 0;
    virtual bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) = 0;
    virtual float GetHitDistance()  const = 0;
    virtual void SetAABB(float left, float top, float right, float bottom, float front, float back) = 0;
    virtual glm::vec3 GetHitPos() const = 0;
};

class ALICEUI_API AUIRectangleSensor : public AUISensor
{
public:
    AUIRectangleSensor() = default;
    ~AUIRectangleSensor() override = default;

    void SetMatrix(const glm::mat4& matSensor) override;
    bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
    float GetHitDistance() const override {
        return m_fHitDistance;
    }
    glm::vec3 GetHitPos() const override {
        return { m_vHitPos, 0.0f };
    }
    void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
        this->SetRectangle(left, top, right - left, bottom - top);
    }

    void SetRectangle(float x, float y, float width, float height) {
        m_vRectangle = glm::vec4(x, y, x + width, y + height);
    }
private:
    glm::vec2 m_vHitPos;
    glm::mat4 m_matSensorInv;
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

    void SetMatrix(const glm::mat4& matSensor) override {
        m_matSensorInv = glm::inverse(matSensor);
    }
    bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
    float GetHitDistance() const override {
        return m_fHitDistance;
    }
    glm::vec3 GetHitPos() const override {
        return m_vHitPos;
    }
    void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
        this->SetBox({ left, top, front }, { right, bottom, back });
    }

    void SetBox(glm::vec3 minBox, glm::vec3 maxBox) {
        m_vBoxMin = minBox;
        m_vBoxMax = maxBox;
    }
private:
    glm::vec3 m_vHitPos;
    glm::mat4 m_matSensorInv;
    glm::vec3 m_vBoxMin;
    glm::vec3 m_vBoxMax;
    float m_fHitDistance = 0.0f;
};
