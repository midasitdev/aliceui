#include "pch.h"
#include "AUISensor.h"
#include "AUIScalar.h"
#include "AUIWidget.h"

namespace
{
    template <typename genType>
    bool IsIntersectLinePlane(genType const & orig, genType const & dir, genType const & planeOrig, genType const & planeNormal, typename genType::value_type & intersectionDistance)
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
}

void AUISensor::Invalidate()
{
    if (auto pWidget = m_pWidget)
    {
        pWidget->_invalidate_sensor();
    }
}

void AUIRectangleSensor::SetMatrix(const glm::mat4& matSensor)
{
    m_matSensor = matSensor;
    m_matSensorInv = glm::inverse(matSensor);
    m_IsBasePlane = glm::isIdentity(m_matSensorInv, glm::epsilon<float>());
    Invalidate();
}

bool AUIRectangleSensor::UpdateHit( const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale)
{
    // 2D Optimization
    const auto isDefaultPlane = (std::abs(vRayDir.z - (-1.0f)) < glm::epsilon<float>()) && glm::isNormalized(vRayDir, glm::epsilon<float>());
    if (m_IsBasePlane && isDefaultPlane)
    {
        m_fHitDistance = vRayOrg.z;
        auto vHitPos = glm::vec2(vRayOrg.x, vRayOrg.y);
        if (vHitPos.x < m_vRectangle[0] ||
            vHitPos.x >= m_vRectangle[2] ||
            vHitPos.y < m_vRectangle[1] ||
            vHitPos.y >= m_vRectangle[3])
            return false;
        m_vHitPos = vHitPos;
        return true;
    }

	auto vLocalEyePos = glm::vec3(m_matSensorInv * glm::vec4(vRayOrg,1));
	auto vLocalEyeDir = glm::vec3(m_matSensorInv * glm::vec4(vRayDir,0));
	auto vLocalPlaneNorm = vLocalEyeDir.z < 0 ? glm::vec3(0,0,1) : glm::vec3(0,0,-1);

	if( !IsIntersectLinePlane(vLocalEyePos,vLocalEyeDir,glm::vec3(0,0,0),vLocalPlaneNorm, m_fHitDistance ) )  //문제 있는듯..?
    {
        //그랩중에는 이런경우엔 문제가 발생할지도.  일단 m_vHitPos는 유지하게 둔다.
		return false;
	}

	auto vHitPos = glm::vec2(vLocalEyePos +  vLocalEyeDir * m_fHitDistance);
	if( vHitPos.x < m_vRectangle[0] ||
		vHitPos.x >= m_vRectangle[2] ||
		vHitPos.y < m_vRectangle[1] ||
		vHitPos.y >= m_vRectangle[3] )
		return false;
	m_vHitPos = vHitPos;
	return true;
}


bool AUIBoxSensor::UpdateHit( const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fScale)
{
	auto vLocalRayOrg = glm::vec3(m_matSensorInv * glm::vec4(vRayOrg,1));
	auto vLocalRayDir = glm::vec3(m_matSensorInv * glm::vec4(vRayDir,0));
	bool bHit = false;

	glm::vec3 vHitPos(0.f);
    float fHitDistance = (std::numeric_limits<float>::max)();
	for( int i =0; i< 3; i++)
    {
        glm::vec3 vPlaneAxis(0.f), vPlanePos(0.f);

		vPlaneAxis[i] = 1;

		if( glm::dot(vPlaneAxis, vLocalRayDir) > 0 )
		{
			vPlanePos = m_vBoxMin;
			vPlaneAxis[i] = -1;
		}
		else
		{
            vPlanePos = m_vBoxMax;
        }

		float fDistance;
		if( !IsIntersectLinePlane(vLocalRayOrg, vLocalRayDir, vPlanePos, vPlaneAxis, fDistance ) )
			continue;
		if( fDistance > fHitDistance )
			continue;
        //위의 방식으로는 계산시 오차가 있어서 약간의 offset을 둠
        //각 plane에 해당하는 사항만 검사하는 걸로 수정!
        float fOffset = 0.05f;
		auto vPos = vLocalRayOrg +  vLocalRayDir * fDistance;
		if( vPos.x < m_vBoxMin.x - fOffset ||
			vPos.x > m_vBoxMax.x + fOffset ||
			vPos.y < m_vBoxMin.y - fOffset  ||
			vPos.y > m_vBoxMax.y + fOffset  ||
			vPos.z < m_vBoxMin.z - fOffset  ||
			vPos.z > m_vBoxMax.z + fOffset   )
			continue;

		vHitPos = vPos;
		fHitDistance =  fDistance;
		bHit = true;
	}

	// Sensor 좌표계에서 Widget 좌표계로 수정.. 할 필요 없지.
	if( bHit )
	{
		m_vHitPos = vHitPos;
		m_fHitDistance = fHitDistance;
	}
	//히트하지 못할경우 마지막 좌표값을 유지하게 된다. 문제가 있을경우 수정. 혹은 그랩 시에는 현재 잡고있는 플레인을 유지해야할지도 모르지..

	return bHit;
}
