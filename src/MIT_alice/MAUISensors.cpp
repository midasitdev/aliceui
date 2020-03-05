#include "pch.h"
#include "MAUISensors.h"

using namespace mit::alice;

template <typename genType>
bool intersectLinePlane(
    genType const & orig, genType const & dir,
    genType const & planeOrig, genType const & planeNormal,
    typename genType::value_type & intersectionDistance)
{
    typename genType::value_type d = glm::dot(dir, planeNormal);
    typename genType::value_type Epsilon = std::numeric_limits<typename genType::value_type>::epsilon();

    if (glm::abs(d) > Epsilon)
    {
        intersectionDistance = glm::dot(planeOrig - orig, planeNormal) / d;
        return true;
    }

    return false;
}

bool MAUISensorUtil::IsIntersectLine(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeLine& line, OUT float& fHitDistance)
{
    // https://en.wikipedia.org/wiki/Skew_lines#Distance_between_two_skew_lines
    auto dir = (glm::vec3)glm::normalize(line.pos[1] - line.pos[0]);
    if (abs(glm::dot(dir, vRayDir)) < 1.0f - glm::epsilon<double>())
    {
        glm::vec3 n = glm::normalize(glm::cross(dir, vRayDir));
        glm::vec3 n1 = glm::normalize(glm::cross(dir, glm::normalize(glm::cross(vRayDir, dir))));
        glm::vec3 n2 = glm::normalize(glm::cross(vRayDir, n));
        auto disp = abs(glm::dot((vRayOrg - (glm::vec3)line.pos[0]), n));
        if (disp < fRayRad)
        {
            if (glm::dot((vRayOrg - (glm::vec3)line.pos[0]), n2) / glm::dot(dir, n2) > 0.0f)
            {
                fHitDistance = (glm::dot(((glm::vec3)line.pos[0] - vRayOrg), n1) / glm::dot(vRayDir, n1));
                return true;
            }
        }
    }
    else
    {
        //////////////////////////////////////////////////////////////////////////
        //평행한 경우        
    }
    return false;
}

bool MAUISensorUtil::IsIntersectCircle(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeCircle& circle, OUT float& fHitDistance)
{
    glm::dvec3 dir(0.f);
    if (glm::distance(circle.norm, glm::dvec3(1.0f, 0.0f, 0.0f)) < glm::epsilon<double>())
        dir = glm::normalize(glm::cross(circle.norm, glm::dvec3(0.0f, 1.0f, 0.0f)));
    else
        dir = glm::normalize(glm::cross(circle.norm, glm::dvec3(1.0f, 0.0f, 0.0f)));

    ShapeArc arc;
    arc.pos = circle.pos;
    arc.norm = circle.norm;
    arc.radius = circle.radius;
    arc.dir = dir;
    arc.angle[0] = 0.0f;
    arc.angle[1] = 360.0f;
    return IsIntersectArc(vRayOrg, vRayDir, fRayRad, arc, fHitDistance);
}

bool MAUISensorUtil::IsIntersectArc(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeArc& arc, float& fHitDistance)
{
    if (!intersectLinePlane(vRayOrg, vRayDir, (glm::vec3)arc.pos, (glm::vec3)arc.norm, fHitDistance))
    {
        if (!intersectLinePlane(vRayOrg, vRayDir, (glm::vec3)arc.pos, -(glm::vec3)arc.norm, fHitDistance))
        {
            AUIAssertFail();
            return false;
        }
    }

    auto vHitPos = vRayOrg + vRayDir * fHitDistance;
    auto distance = glm::distance(vHitPos, (glm::vec3)arc.pos);
    if (arc.radius < distance + fRayRad && arc.radius > distance - fRayRad)
    {
        auto dir = glm::normalize(vHitPos - (glm::vec3)arc.pos);
        auto angle = glm::degrees(glm::acos(glm::dot(dir, (glm::vec3)arc.dir)));
        if (glm::dot(glm::cross((glm::vec3)arc.dir, dir), (glm::vec3)arc.norm) < 0.0f)
        {
            angle += 180.0f;
        }
        if ((angle > arc.angle[0] && angle < arc.angle[1]) ||
            (angle < arc.angle[0] && angle > arc.angle[1]))
            return true;
    }
    return false;
}

bool MAUISensorUtil::IsIntersectEllipse(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeEllipse& ellipse, float& fHitDistance)
{
    return false;
}

bool MAUISensorUtil::IsIntersectEllipseArc(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const ShapeEllipseArc& ellipseArc, float& fHitDistance)
{
    return false;
}


bool MAUISphereSensor::UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale)
{
    auto vLocalEyePos = glm::vec3(glm::vec4(vRayOrg, 1));
    auto vLocalEyeDir = glm::vec3(glm::vec4(vRayDir, 0));
    if (!glm::intersectRaySphere(vLocalEyePos, vLocalEyeDir, m_vSpherePos, m_fSphereRadius, m_fHitDistance))
    {
        //그랩중에는 이런경우엔 문제가 발생할지도.  일단 m_vHitDir는 유지하게 둔다.
        return false;
    }
    m_vHitPos = vLocalEyePos + vLocalEyeDir * m_fHitDistance;
    m_vHitDir = glm::normalize(vLocalEyePos + vLocalEyeDir * m_fHitDistance - m_vSpherePos);
    return true;
}

bool MAUICircleBoundarySensor::UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale)
{
    auto vLocalEyePos = glm::vec3(m_matSensorInv * glm::vec4(vRayOrg, 1));
    auto vLocalEyeDir = glm::vec3(m_matSensorInv * glm::vec4(vRayDir, 0));
    auto vLocalPlaneNorm = vLocalEyeDir.z < 0 ? glm::vec3(0, 0, 1) : glm::vec3(0, 0, -1);
    if (!intersectLinePlane(vLocalEyePos, vLocalEyeDir, glm::vec3(0.0f, 0.0f, 0.0f), vLocalPlaneNorm, m_fHitDistance))
    {
        return false;
    }

    auto vHitPos = vLocalEyePos + vLocalEyeDir * m_fHitDistance;
    auto distance = glm::length(vHitPos);
    if (m_fRadius > distance + m_fBoundarySize ||
        m_fRadius < distance - m_fBoundarySize)
        return false;

    m_vHitPos = vHitPos;
    return true;
}

bool MAUILineSensor::UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale)
{
    float fRad = fScale * 5.f;   //screen에서의 5pixel;


    if (MAUISensorUtil::IsIntersectLine(vRayOrg, vRayDir, fRad, m_line, m_fHitDistance))
    {
        m_vHitPos = vRayOrg + m_fHitDistance * vRayDir;
        return true;
    }
    //for (auto line : m_arrLines)
    //{
    //}

    //for (auto circle : m_arrCircle)
    //{
    //    if (MAUISensorUtil::IsIntersectCircle(vRayOrg, vRayDir, fRad, circle, m_fHitDistance))
    //    {
    //        m_vHitPos = vRayOrg + m_fHitDistance * vRayDir;
    //        return true;
    //    }
    //}

    //for (auto arc : m_arrArc)
    //{
    //    if (MAUISensorUtil::IsIntersectArc(vRayOrg, vRayDir, fRad, arc, m_fHitDistance))
    //    {
    //        m_vHitPos = vRayOrg + m_fHitDistance * vRayDir;
    //        return true;
    //    }
    //}

    //for (auto ellipse : m_arrEllipse)
    //{
    //    if (MAUISensorUtil::IsIntersectEllipse(vRayOrg, vRayDir, fRad, ellipse, m_fHitDistance))
    //    {
    //        m_vHitPos = vRayOrg + m_fHitDistance * vRayDir;
    //        return true;
    //    }
    //}

    //for (auto ellipseArc : m_arrEllipseArc)
    //{
    //    if (MAUISensorUtil::IsIntersectEllipseArc(vRayOrg, vRayDir, fRad, ellipseArc, m_fHitDistance))
    //    {
    //        m_vHitPos = vRayOrg + m_fHitDistance * vRayDir;
    //        return true;
    //    }
    //}

    return false;
}

bool mit::alice::MAUIArcSensor::UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale)
{
    float fRad = fScale * 5.f;   //screen에서의 5pixel;
    if (MAUISensorUtil::IsIntersectArc(vRayOrg, vRayDir, fRad, m_arc, m_fHitDistance))
    {
        m_vHitPos = vRayOrg + m_fHitDistance * vRayDir;
        return true;
    }
    return false;
}
