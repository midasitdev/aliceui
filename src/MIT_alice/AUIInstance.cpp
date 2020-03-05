#include "pch.h"
#include "AUIInstance.h"
#include "AUIWidget.h"
#include "AUIWidgetManager.h"
#include "AUISensor.h"
#include "AUICompass.h"
#include "AUIWidgetRootInfo.h"

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

//void AUIInstance::UpdateHitData( int sx, int sy )
//{
//    if (false == GetWidget()->HasHitTest())
//    {
//        m_bHit = false;
//        return;
//    }
//
//	const auto& aSensors = GetWidget()->GetSensors();
//    const bool bSensor = aSensors.size() > 0;
//	if( !bSensor )
//	{
//		m_bHit = false;
//		return;
//	}
//
//	glm::vec3 vLocalOrg, vLocalDir;
//	glm::vec3 vGlobalOrg, vGlobalDir;
//
//
//    auto root_coord = GetWidget()->GetRootCoordInfo();
//    auto coord = root_coord->GetTargetCoord();
//    auto& matRoot = root_coord->GetMatrix();
//	auto pWidget= GetWidget();
//    auto pWidgetManager = GetWidgetManager();
//
//	float fHitDistWeight = 0;
//	if(bSensor)
//	{
//		if ( coord == AUICoordSpace::kScreenSpace)
//		{
//			vLocalOrg.x = static_cast< float >( sx );
//			vLocalOrg.y = static_cast< float >( sy );
//			vLocalOrg.z = kHitDistanceScreen;
//			vLocalDir.x = 0.0f;
//			vLocalDir.y = 0.0f;
//			vLocalDir.z = -1.0f;
//			fHitDistWeight = kHitDistanceScreen ;//- static_cast< float >( m_iWidgetDepth );
//		}
//		else if(coord == AUICoordSpace::kWorldPanel)
//		{
//			auto vp = pWidgetManager->GetViewport();
//			auto matProj = pWidgetManager->GetProjectionMatrix();
//			auto matView = pWidgetManager->GetViewingMatrix();
//
//			glm::vec3 sPos = glm::project(glm::vec3(matRoot[3]),matView  , matProj, vp);
//			vLocalOrg.x = static_cast< float >( sx ) - sPos.x ;
//			vLocalOrg.y = static_cast< float >( sy ) - (vp[3] - sPos.y - 1.0f);
//			vLocalOrg.z = 0.0f;
//			vLocalDir.x = 0.0f;
//			vLocalDir.y = 0.0f;
//			vLocalDir.z = -1.0f;
//			fHitDistWeight = kHitDistanceScreen ;//- static_cast< float >( m_iWidgetDepth );
//		}
//		else
//        {
//            auto vp = pWidgetManager->GetViewport();
//            auto matProj = pWidgetManager->GetProjectionMatrix();
//            auto matView = pWidgetManager->GetViewingMatrix();
//
//			glm::mat4 matModel;
//
//			if( coord == AUICoordSpace::kWorld)
//			{
//				matModel =  matRoot ;
//			}
//			else if(coord ==  AUICoordSpace::kSteadyScale)
//			{
//				float fScale =  2.0f / matProj[1][1];
//				if(matProj[3][2] != 0.f )
//				{
//					float fEyeZ =	matView[0][2] * matRoot[3][0] + matView[1][2] * matRoot[3][1] + matView[2][2] * matRoot[3][2] +  matView[3][2];
//					fScale *= -fEyeZ ;
//				}
//				float fViewLen = glm::min(vp[2] ,vp[3]);
//
//				matModel = matRoot * glm::scale(glm::vec3(fScale / fViewLen ));
//			}
//
//			auto matInv = glm::inverse(matModel);
//			vLocalOrg = matInv * glm::vec4(GetWidgetManager()->GetMouseOrg(),1);
//			vLocalDir = glm::normalize( glm::vec3(matInv * glm::vec4(GetWidgetManager()->GetMouseDir(),0)) );
//		}
//	}
//
//		m_bHit = false;
//		//m_wpCurSensor.reset();
//		for(auto& pSensor : aSensors)
//		{
//			bool bHit = pSensor->UpdateHit(vLocalOrg, vLocalDir);
//			if( !bHit )
//				continue;
//			auto fHitDist = fHitDistWeight + pSensor->GetHitDistance();
//			if( !m_bHit )
//			{
//				m_bHit = true;
//				m_fHitDist = fHitDist;
//			//	m_wpCurSensor = pSensor;
//			}
//			else if(fHitDist < m_fHitDist )
//			{
//				m_fHitDist = fHitDist;
//			//	m_wpCurSensor = pSensor;
//			}
//		}
//}