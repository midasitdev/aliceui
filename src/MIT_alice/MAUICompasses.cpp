#include "pch.h"
#include "MAUICompasses.h"

using namespace mit::alice;


void MAUISphereCompass::CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir)
{
    glm::intersectRaySphere(vRayOrg, vRayDir, m_vSpherePos, m_fSphereRadius, m_vCurrPosition, m_vCurrDirection);
}

void MAUIStraightLineCompass::CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir)
{
    // https://en.wikipedia.org/wiki/Skew_lines#Distance_between_two_skew_lines
    glm::vec3 n = glm::normalize(glm::cross(m_vDir, vRayDir));
    glm::vec3 n2 = glm::normalize(glm::cross(vRayDir, n));
    if (glm::dot(m_vDir, n2) > AUITolerance::GetGlobalTolerance())
    {
        m_fDisp = (glm::dot((vRayOrg - m_vPos), n2) / glm::dot(m_vDir, n2));
        m_CurPos = m_vPos + m_fDisp * m_vDir;
    }
}

void MAUICircleBoundaryCompass::CalcControlPosition(const glm::vec3& vRayOrg, const glm::vec3& vRayDir)
{
    float fHitDistance;
    if (glm::dot(vRayDir, m_norm) > 0.0f)
    {
        if (!glm::intersectRayPlane(vRayOrg, vRayDir, m_center, -m_norm, fHitDistance))
        {
            ASSERT(0);
            m_curDir = glm::vec3(0.f);
            return;
        }
    }
    else
    {
        if (!glm::intersectRayPlane(vRayOrg, vRayDir, m_center, m_norm, fHitDistance))
        {
            ASSERT(0);
            m_curDir = glm::vec3(0.f);
            return;
        }
    }
    auto curPos = vRayOrg + vRayDir * fHitDistance;
    m_curDir = glm::normalize(curPos - m_center);
}
