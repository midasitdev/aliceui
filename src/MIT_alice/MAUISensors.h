#pragma once


#include "MITAliceDef.h"
#include "../MIT_alice/MAUI1DShapeDef.h"

namespace mit::alice
{
    class MITALICE_API MAUISensorUtil
    {
    public:
        bool static IsIntersectLine(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeLine& line, float& fHitDistance);
        bool static IsIntersectCircle(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeCircle& circle, float& fHitDistance);
        bool static IsIntersectArc(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeArc& arc, float& fHitDistance);
        bool static IsIntersectEllipse(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeEllipse& ellipse, float& fHitDistance);
        bool static IsIntersectEllipseArc(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeEllipseArc& ellipseArc, float& fHitDistance);
    };

    class MITALICE_API MAUISphereSensor : public AUISensor
    {
    public:
        MAUISphereSensor() = default;
        ~MAUISphereSensor() override = default;

        inline void GetBoundingSphere(glm::vec3& c, float& r) const override
        {
            c = m_vSpherePos;
            r = m_fSphereRadius;

        }
        inline bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale = 1.0f) override;
        float GetHitDistance() const override {
            return m_fHitDistance;
        }
        glm::vec3 GetHitPos() const  {
            return m_vHitPos;
        }
        //void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
        //    // TODO
        //}

        glm::vec3 GetHidDir() const {
            return m_vHitDir;
        }
        void SetSphere(const glm::vec3& pos, float radius) {
            m_vSpherePos = pos;
            m_fSphereRadius = radius;
            Invalidate();
        }
    private:
        glm::vec3 m_vHitDir;
        glm::vec3 m_vSpherePos;
        glm::vec3 m_vHitPos;
        float m_fHitDistance = 0.0f;
        float m_fSphereRadius = 0.0f;
    };

    class MITALICE_API MAUICircleBoundarySensor : public AUISensor
    {
    public:
        MAUICircleBoundarySensor() = default;
        ~MAUICircleBoundarySensor() override = default;

        inline void GetBoundingSphere(glm::vec3& c, float& r) const override
        {
            c = glm::vec3(m_matSensor[3]);
            r = m_fRadius;

        }
        void SetMatrix(const glm::mat4& matSensor)  {
            m_matSensor = matSensor;
            m_matSensorInv = glm::inverse(matSensor);
            Invalidate();
        }
        inline bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale = 1.0f) override;
        float GetHitDistance() const override {
            return m_fHitDistance;
        }
        glm::vec3 GetHitPos() const  {
            return m_vHitPos;
        }
        //void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
        //    // TODO
        //}

        void SetCircle(float radius) {
            m_fRadius = radius;
            Invalidate();
        }
    private:
        glm::mat4 m_matSensor = glm::mat4(1.f);
        glm::mat4 m_matSensorInv = glm::mat4(1.f);
        glm::vec3 m_vHitPos;
        float m_fRadius = 0.0f;
        float m_fBoundarySize = 5.0f;
        float m_fHitDistance = 0.0f;
    };

    class MITALICE_API MAUILineSensor : public AUISensor
    {
    public:
        MAUILineSensor() = default;
        ~MAUILineSensor() override = default;

        inline void GetBoundingSphere(glm::vec3& c, float& r) const override
        {
            c = (m_line.pos[1] + m_line.pos[0]) * 0.5;
            r = float(glm::length(m_line.pos[1] - m_line.pos[0]) * 0.5);
        }
        inline bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale = 1.0f) override;
        float GetHitDistance() const override {
            return m_fHitDistance;
        }
        glm::vec3 GetHitPos() const  {
            return m_vHitPos;
        }

        void SetLine(const ShapeLine& Line)
        {
            m_line = Line;
            Invalidate();
        }

    private:

        mit::alice::ShapeLine m_line;
        glm::vec3 m_vHitPos;
        float m_fHitDistance = 0.0f;
    };


    class MITALICE_API MAUIArcSensor : public AUISensor
    {
    public:
        MAUIArcSensor() = default;
        ~MAUIArcSensor() override = default;

        inline void GetBoundingSphere(glm::vec3& c, float& r) const override
        {
            c = m_arc.pos;
            r = (float)m_arc.radius;
        }
        inline bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale = 1.0f) override;
        float GetHitDistance() const override {
            return m_fHitDistance;
        }
        glm::vec3 GetHitPos() const {
            return m_vHitPos;
        }

        void SetArc(const ShapeArc& arc)
        {
            m_arc = arc;
            Invalidate();
        }

    private:

        mit::alice::ShapeArc m_arc;
        glm::vec3 m_vHitPos;
        float m_fHitDistance = 0.0f;
    };
}
