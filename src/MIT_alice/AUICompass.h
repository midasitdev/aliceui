#pragma once

#include "AUIAPIDef.h"

#include <glm/glm.hpp>

class ALICEUI_API AUICompass
{
protected:
    AUICompass() = default;
public:
    virtual ~AUICompass() = default;
    virtual void CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) = 0;
    virtual glm::vec3 GetPosition() const = 0;
};

class ALICEUI_API AUIPlaneCompass : public AUICompass
{
public:
    AUIPlaneCompass() = default;
    ~AUIPlaneCompass() override = default;

    void SetPlane(const glm::vec3& pos, const glm::vec3& norm, const glm::vec3& refdir);
    void CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
    glm::vec3 GetPosition() const override {
        return glm::vec3(m_vPlanePosition.x, m_vPlanePosition.y, 0.0f);
    }

    glm::vec2 GetCurrentPlanePosition() const {
        return m_vPlanePosition;
    }
private:
    glm::vec3 m_vPlanePos;
    glm::vec3 m_vPlaneNorm;

    glm::mat4 m_matPlane;
    glm::mat4 m_matPlaneInv;
    glm::vec2 m_vPlanePosition;

    // Optimization Hint
    bool m_IsBasePlane = true;
};
