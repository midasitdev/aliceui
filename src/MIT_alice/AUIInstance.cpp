#include "pch.h"
#include "AUIInstance.h"
#include "AUIWidget.h"
#include "AUIWidgetManager.h"
#include "AUISensor.h"
#include "AUICompass.h"

const float AUIInstance::kHitDistanceScreen = /*(std::numeric_limits< float >::lowest)() +*/ -10000.f;

AUIInstance::AUIInstance( AUIWidgetManager* pWidgetManager, const std::shared_ptr< AUIWidget >& pWidget )
    : m_pWidgetManager( pWidgetManager )
    , m_pWidget( pWidget )
    , m_fHitDist( kHitDistanceScreen )
{
    AUIAssert(GetWidgetManager());
    AUIAssert(pWidget);
	auto pTmp = GetWidget();
	while( pTmp = pTmp->GetParent())
		m_iWidgetDepth++;
}

AUIInstance::~AUIInstance()
{

}

void AUIInstance::CreateInstance()
{
    AUIAssert( IsValid() == false );
    OnCreateInstance();
    m_bValid = true;
    m_bDirty = true;
}

void AUIInstance::DestroyInstance()
{
    AUIAssert( IsValid() == true );
    OnDestroyInstance();
    m_bValid = false;
}

void AUIInstance::UpdateInstance()
{
    AUIAssert( IsValid() == true );
    OnUpdateInstance();
    m_bDirty = false;
}

void AUIInstance::SetDirty()
{
     m_bDirty = true;
     OnSetDirty();
}

void AUIInstance::OnSetDirty()
{
    if ( GetWidget()->IsRoot() )
        return;

    if ( auto pRoot = GetWidget()->GetRoot() )
    {
        if ( auto pRootInst = GetWidgetManager()->FindInstance( pRoot ) )
        {
            pRootInst->SetDirty();
        }
    }
}

void AUIInstance::UpdateHitData( int sx, int sy )
{
    if (false == GetWidget()->HasHitTest())
    {
        m_bHit = false;
        return;
    }

	const auto& aSensors = GetWidget()->GetSensors();
    const auto& aCompasses = GetWidget()->GetCompasses();
    const bool bSensor = aSensors.size() > 0;
    const bool bCompass = aCompasses.size() > 0;
	if( !bSensor && !bCompass )
	{
		m_bHit = false;
		return;
	}

	glm::vec3 vLocalOrg, vLocalDir;
	glm::vec3 vGlobalOrg, vGlobalDir;



	const auto coord =  GetWidget()->GetRootTargetCoord();
	auto pWidget= GetWidget();
	auto pos =  GetWidget()->GetPositionAtRoot().toGlm();

	float fHitDistWeight = 0;
	if(bSensor)
	{
		if ( coord == AUICoordSpace::kScreenSpace)
		{
			vLocalOrg.x = static_cast< float >( sx );
			vLocalOrg.y = static_cast< float >( sy );
			vLocalOrg.z = kHitDistanceScreen;
			vLocalOrg = vLocalOrg - pos;
			vLocalDir.x = 0.0f;
			vLocalDir.y = 0.0f;
			vLocalDir.z = -1.0f;
			fHitDistWeight = kHitDistanceScreen ;//- static_cast< float >( m_iWidgetDepth );
		}
		else if(coord == AUICoordSpace::kWorldPanel)
		{
			auto vp = GetViewport();
			auto matProj = GetProjectionMatrix();
			auto matView = GetViewingMatrix();
			auto matRoot = GetWidget()->GetRootMatrix();

			glm::vec3 sPos = glm::project(glm::vec3(matRoot[3]),matView  , matProj, vp);
			vLocalOrg.x = static_cast< float >( sx ) - sPos.x - pos.x;
			vLocalOrg.y = static_cast< float >( sy ) - (vp[3] - sPos.y - 1.0f) - pos.y;
			vLocalOrg.z = 0.0f;
			vLocalDir.x = 0.0f;
			vLocalDir.y = 0.0f;
			vLocalDir.z = -1.0f;
			fHitDistWeight = kHitDistanceScreen ;//- static_cast< float >( m_iWidgetDepth );
		}
		else
		{
			auto vp = GetViewport();
			auto matProj = GetProjectionMatrix();
			auto matView = GetViewingMatrix() ;
			auto matRoot = GetWidget()->GetRootMatrix();

			glm::mat4 matModel;

			//if ( coord == CoordSpace::Screen)
			//{
			//	matView = glm::mat4();
			//	matProj = glm::mat4();
			//	matModel = glm::translate(pos.toGlm());

			//	vECOrg = glm::vec4(sx,sy,-pos.fZ  + HitDistanceScreen,1);
			//	vECDir = glm::vec4(0,0,-1,0);
			//}
			if( coord == AUICoordSpace::kWorld)
			{
				matModel =  matRoot * glm::translate(pos);
			}
			else if(coord ==  AUICoordSpace::kSteadyScale)
			{
				float fScale =  2.0f / matProj[1][1];
				if(matProj[3][2] != 0.f )
				{
					float fEyeZ =	matView[0][2] * matRoot[3][0] + matView[1][2] * matRoot[3][1] + matView[2][2] * matRoot[3][2] +  matView[3][2];
					fScale *= -fEyeZ ;
				}
				float fViewLen = glm::min(vp[2] ,vp[3]);

				matModel = matRoot * glm::scale(glm::vec3(fScale / fViewLen )) * glm::translate(pos)  ;
			}

			auto matInv = glm::inverse(matModel);
			vLocalOrg = matInv * glm::vec4(GetWidgetManager()->GetMouseOrg(),1);
			vLocalDir = glm::normalize( glm::vec3(matInv * glm::vec4(GetWidgetManager()->GetMouseDir(),0)) );//glm::vec3(glm::dot(lu,rayDir),glm::dot(lv,rayDir),glm::dot(lw,rayDir));
		}
	}



	if( GetWidget()->IsGrabMouseEvent() )
	{
        if (auto pCurSensor = m_wpCurSensor.lock())
        {
            pCurSensor->UpdateHit(vLocalOrg, vLocalDir);
        }
        else
        {
            AUIAssert(pCurSensor); // WTF?
        }
	}
	else
	{
		m_bHit = false;
		m_wpCurSensor.reset();
		for(auto& pSensor : aSensors)
		{
			bool bHit = pSensor->UpdateHit(vLocalOrg, vLocalDir);
			if( !bHit )
				continue;
			auto fHitDist = fHitDistWeight + pSensor->GetHitDistance();
			if( !m_bHit )
			{
				m_bHit = true;
				m_fHitDist = fHitDist;
				m_wpCurSensor = pSensor;
			}
			else if(fHitDist < m_fHitDist )
			{
				m_fHitDist = fHitDist;
				m_wpCurSensor = pSensor;
			}
		}
	}



	for (auto& pCompass : aCompasses)
		UpdateCompass(pCompass.get());
}

glm::mat4 AUIInstance::GetRootMatrix() const
{
    AUIAssert(!"Not implemented");
    return glm::mat4(1.0f);
}

glm::mat4 AUIInstance::GetViewingMatrix() const
{
    AUIAssert(!"Not implemented");
    return glm::mat4(1.0f);
}

glm::mat4 AUIInstance::GetProjectionMatrix() const
{
    AUIAssert(!"Not implemented");
    return glm::mat4(1.0f);
}

glm::vec4 AUIInstance::GetViewport() const
{
    AUIAssert(!"Not implemented");
    return glm::vec4(0.0f);
}

glm::mat4 AUIInstance::GetLocalMatrix()
{
	glm::mat4 matLocal;
	const auto coord =  GetWidget()->GetRootTargetCoord();
	auto pWidget= GetWidget();
	auto pos =  GetWidget()->GetPositionAtRoot().toGlm();

	float fHitDistWeight = 0;

	if ( coord == AUICoordSpace::kScreenSpace)
	{
		matLocal = glm::translate(pos)  ;
	}
	else if(coord == AUICoordSpace::kWorldPanel)
	{
		AUIAssert(!"World Panel coordinate is not supported");  // Local과 World간 직접 관계성이 사라진 좌표계 변환이기 때문에, 관련 변환이 존재하지 않음.
	}
	else
	{
		auto matRoot = GetWidget()->GetRootMatrix();

		if( coord == AUICoordSpace::kWorld)
		{
			matLocal =  matRoot * glm::translate(pos);
		}
		else if(coord ==  AUICoordSpace::kSteadyScale)
		{
			auto vp = GetViewport();
			auto matProj = GetProjectionMatrix();
			auto matView = GetViewingMatrix() ;
			float fScale =  2.0f / matProj[1][1];
			if(matProj[3][2] != 0.f )
			{
				float fEyeZ =	matView[0][2] * matRoot[3][0] + matView[1][2] * matRoot[3][1] + matView[2][2] * matRoot[3][2] +  matView[3][2];
				fScale *= -fEyeZ ;
			}
			float fViewLen = glm::min(vp[2] ,vp[3]);

			matLocal = matRoot * glm::scale(glm::vec3(fScale / fViewLen )) * glm::translate(pos)  ;
		}
	}
	return matLocal;
}

void AUIInstance::UpdateCompass(AUICompass* pCompass)
{
    AUIAssert(pCompass);
	const auto coord =  GetWidget()->GetRootTargetCoord();
	if ( coord == AUICoordSpace::kScreenSpace)
	{
		pCompass->CalcControlPosition(glm::vec3(GetWidgetManager()->GetMousePos(),0), glm::vec3(0,0,-1));
	}
	else
	{
		pCompass->CalcControlPosition(GetWidgetManager()->GetMouseOrg(), GetWidgetManager()->GetMouseDir());
	}
}

