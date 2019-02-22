#include "pch.h"
#include "AUIStyleNotion.h"
#include "AUIProperty.h"



bool AUIStyleNotion::HasHorizontalAlign() const
{
	auto itrAP = m_mapValues.find(MNV_LAYOUT_ALIGN_PARENT);
	if (itrAP != m_mapValues.end())
	{
		std::array< bool, AUIProperty::kParentOptTotal_ParentOpt > parentOpt;
		if (!itrAP->second.GetValue(parentOpt))
		{
			ASSERT(0);
			return false;
		}
		if (parentOpt[AUIProperty::kParentCenter_ParentOpt] ||
			parentOpt[AUIProperty::kParentCenterHorizontal_ParentOpt] ||
			parentOpt[AUIProperty::kParentLeft_ParentOpt] ||
			parentOpt[AUIProperty::kParentRight_ParentOpt] )
			return true;
	}
	return false;
}

bool AUIStyleNotion::HasVerticalAlign() const
{
	auto itrAP = m_mapValues.find(MNV_LAYOUT_ALIGN_PARENT);
	if (itrAP != m_mapValues.end())
	{
		std::array< bool, AUIProperty::kParentOptTotal_ParentOpt > parentOpt;
		if (!itrAP->second.GetValue(parentOpt))
		{
			ASSERT(0);
			return false;
		}
		if (parentOpt[AUIProperty::kParentCenter_ParentOpt] ||
			parentOpt[AUIProperty::kParentCenterVertical_ParentOpt] ||
			parentOpt[AUIProperty::kParentTop_ParentOpt] ||
			parentOpt[AUIProperty::kParentBottom_ParentOpt] )
			return true;
	}
	return false;
}
