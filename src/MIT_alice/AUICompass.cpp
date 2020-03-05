#include "pch.h"
#include "AUICompass.h"
#include "AUIScalar.h"

void AUIPlaneCompass::SetPlane(const glm::vec3& pos, const glm::vec3& norm, const glm::vec3& refdir)
{
	m_vPlaneCenterPos = pos;
	m_vPlaneNorm = glm::normalize(norm);
	m_vPlaneRefDir = glm::normalize(refdir);

    const glm::vec3 w = glm::normalize(norm);
    const glm::vec3 v = glm::normalize(glm::cross(w, refdir));
    const glm::vec3 u = glm::normalize(glm::cross(v, w));

    const glm::mat4 matPlane(glm::vec4(u, 0), glm::vec4(v, 0), glm::vec4(w, 0), glm::vec4(pos, 1.0));
    m_matPlane = matPlane;
    m_matPlaneInv = glm::inverse(m_matPlane);
    m_IsBasePlane = glm::isIdentity(m_matPlaneInv, glm::epsilon<float>());
}

std::tuple<const glm::vec3, const glm::vec3, const glm::vec3> AUIPlaneCompass::GetPlane() const
{
	return { m_vPlaneCenterPos, m_vPlaneNorm, m_vPlaneRefDir };
}

void AUIPlaneCompass::CalcControlPosition( const glm::vec3& vRayOrg, const glm::vec3& vRayDir )
{
    // 2D Optimization
    const auto isDefaultPlane = (std::abs(vRayDir.z - (-1.0f)) < glm::epsilon<float>()) && glm::isNormalized(vRayDir, glm::epsilon<float>());
    if (m_IsBasePlane && isDefaultPlane)
    {
        m_vPlanePosition = glm::vec2(vRayOrg.x, vRayOrg.y);
        return;
    }

	auto vLocalEyePos = glm::vec3(m_matPlaneInv * glm::vec4(vRayOrg,1));
	auto vLocalEyeDir = glm::vec3(m_matPlaneInv * glm::vec4(vRayDir,0));
	auto vLocalPlaneNorm = vLocalEyeDir.z < 0 ? glm::vec3(0,0,1) : glm::vec3(0,0,-1);
	float fDistance;
	if( !glm::intersectRayPlane(vLocalEyePos,vLocalEyeDir,glm::vec3(0,0,0),vLocalPlaneNorm, fDistance ) ) 
	{
		m_vPlanePosition = glm::vec2(0,0);
		return;
	}
	m_vPlanePosition = glm::vec2(vLocalEyePos +  vLocalEyeDir * fDistance);
	//m_vPlanePosition = m_matPlaneInv * glm::vec4( vPos , 1); 

}
