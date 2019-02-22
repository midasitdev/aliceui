#pragma once


#include "MITAliceDef.h"

namespace mit::alice
{
    class MITALICE_API MAUISphereCompass : public AUICompass
    {
    public:
        MAUISphereCompass() = default;
        ~MAUISphereCompass() override = default;

        void CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
        glm::vec3 GetPosition() const override {
            return m_vCurrPosition;
        }

        void SetSphere(const glm::vec3& pos, float radius) {
            m_vSpherePos = pos;
            m_fSphereRadius = radius;
        }
    private:
        glm::vec3 m_vSpherePos;
        float m_fSphereRadius = 0.0f;
        glm::vec3 m_vCurrPosition;
        glm::vec3 m_vCurrDirection;
    };

    class MITALICE_API MAUIStraightLineCompass : public AUICompass
    {
    public:
        MAUIStraightLineCompass() = default;
        ~MAUIStraightLineCompass() override = default;

        void CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
        glm::vec3 GetPosition() const override {
            return m_CurPos;
        }

        void SetStraightLine(const glm::vec3& pos, const glm::vec3& dir) {
            m_vPos = pos;
            m_vDir = dir;
        }
        glm::vec3 GetCurrentPosition() const {
            return m_CurPos;
        }
        float GetCurrentDisp() const {
            return m_fDisp;
        }
    private:
        glm::vec3 m_vPos;
        glm::vec3 m_vDir;
        glm::vec3 m_CurPos;
        float m_fDisp = 0.0f;
    };

    class MITALICE_API MAUICircleBoundaryCompass : public AUICompass
    {
    public:
        MAUICircleBoundaryCompass() = default;
        ~MAUICircleBoundaryCompass() override = default;

        void CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
        glm::vec3 GetPosition() const override {
            return m_center;    // Bad..?
        }

        void SetCircle(const glm::vec3& center, const glm::vec3& norm) {
            m_center = center;
            m_norm = norm;
        }

        glm::vec3 GetCurrentDir() const {
            return m_curDir;
        }
    private:
        glm::vec3 m_center;
        glm::vec3 m_norm;
        float m_fRadius = 0.0f;
        glm::vec3 m_curDir;
    };
}
