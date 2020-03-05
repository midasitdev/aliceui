#include "pch.h"
#include "AUIWidget.h"
#include "AUIWidgetManager.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIInstance.h"
#include "AUIDrawable.h"
#include "AUIApplication.h"
#include "AUIWidgetRootInfo.h"
#include "AUITooltip.h"
#include "AUICompass.h"
#include "AUISensor.h"
#include "AUIWidgetSelection.h"
#include "AUIWidgetStyle.h"

constexpr float DefaultWheelDelta = 120.0f;
static AUIRuntimeID gNextRuntimeId = 1;
const AUIWidgetRootInfo AUIWidget::s_DefualtRootInfo;

AUIWidget::AUIWidget()
	: m_bUpdateChildPosition(false)
	, m_bWasDirty(false)
	, m_bShowTooltip(false)
	, m_bDirty(true)
	, m_bNeedUpdateSize(true)
	, m_bAnimRunning(false)
	, m_bUseHitTest(true)
	, m_Opacity(1.0f)
	, m_Color(kAUIColorTransparent)
	, m_bUseHotkeyCopy(false)
	, m_bUseHotkeyPaste(false)
	, m_bUseHotkeyCut(false)
	//, m_bDefault2DCompass(false)
	, m_bDefault2DSensor(false)
	, m_ScrollX(0.0f)
	, m_ScrollY(0.0f)
	, m_PrevUpdateWidth(-1.0f)
	, m_PrevUpdateHeight(-1.0f)
	, m_PrevUpdateWidthSpec(AUIMeasureSpec::kUnspecified)
	, m_PrevUpdateHeightSpec(AUIMeasureSpec::kUnspecified)
	, m_CurTimeTick(std::chrono::milliseconds::zero())
    , m_bForceDepthTest(false)
    , m_bForceDepthMask(false)
    , m_RuntimeID(gNextRuntimeId++)
{
	//m_spRootInfo = std::make_shared<AUIWidgetRootInfo>();

	// Register widget
    if (AUIApplication::Instance().IsInitialized())
	    AUIApplication::Instance().GetWidgetTree().RegisterWidget(this);
}

AUIWidget::~AUIWidget()
{
	// Unregister widget
    if (AUIApplication::Instance().IsInitialized())
    {
        AUIApplication::Instance().GetWidgetTree().ClearChild(this);
        AUIApplication::Instance().GetWidgetTree().UnregisterWidget(this);
    }
}

AUIWidget* AUIWidget::FindByRuntimeID(const AUIRuntimeID id)
{
	return AUIApplication::Instance().GetWidgetTree().FindByRuntimeID(id);
}

void AUIWidget::Create()
{
	AUIAssert(GetWidgetManager());

	OnCreate();
}

void AUIWidget::Destroy()
{
	AUIAssert(GetWidgetManager());

	OnDestroy();
}

void AUIWidget::FocusIn()
{
	SetFocused(true);
	OnFocusIn();
	FocusInSignal.Send(this);
}

void AUIWidget::FocusOut()
{
	SetFocused(false);
	OnFocusOut();
	FocusOutSignal.Send(this);
}

const std::shared_ptr< AUIWidget > AUIWidget::GetNextFocusable()
{
	if (GetParent() != nullptr)
		return GetParent()->GetNextFocusable();
	return shared_from_this();
}

const std::shared_ptr< AUIWidget > AUIWidget::GetPrevFocusable()
{
	if (GetParent() != nullptr)
		return GetParent()->GetPrevFocusable();
	return shared_from_this();
}

AUIWidget* const AUIWidget::GetRoot() const
{
	return AUIApplication::Instance().GetWidgetTree().GetRoot(const_cast<AUIWidget*>(this));
}

void AUIWidget::SetPosition(const AUIScalar3& pos)
{
    m_vPos = pos;
    if (m_bDefault2DSensor)
        UpdateDefault2DSensorSize();
	OnPositionChange();
    //if (IsInstanced())
	{
		if (auto pInst = GetInstance())
			pInst->OnSetPosition();
	}
}

AUIScalar3 AUIWidget::GetPositionAtRoot() const
{
	auto pos = m_vPos;
	for (auto pWidget = GetParent(); pWidget; pWidget = pWidget->GetParent())
	{
		pos += pWidget->GetPosition();
        if (pWidget->IsRootCoord())
            break;
	}
	return pos;
}


void AUIWidget::SetDefaultSize(const AUIScalar2& size)
{
	m_Property.SetDefaultSize(size);
	m_bNeedUpdateSize = true;

	this->OnSetDefaultSize(size);
	GetRoot()->m_bNeedUpdateSize = true;
}

void AUIWidget::OnSetDefaultSize(const AUIScalar2& size)
{

}

bool AUIWidget::OnSetParent(AUIWidget* const pParent)
{
	return true;
}

AUIWidget* const AUIWidget::GetParent() const
{
	return AUIApplication::Instance().GetWidgetTree().GetParent(const_cast<AUIWidget*>(this));
}

bool AUIWidget::IsRoot() const
{
	return (GetParent() == nullptr);
}

bool AUIWidget::IsCreated() const
{
    return (IsInstanced() ||
        (m_LifeState.IsPendingCreate() == true && m_LifeState.IsPendingDestory() == false));
}

bool AUIWidget::IsInstanced() const noexcept
{
	return m_UIState.IsCreated() && m_LifeState.IsCreated();
}

void AUIWidget::UpdateChildPosition()
{
	auto pRoot = GetRoot();
	AUIAssert(pRoot);

	// Already update
	if (pRoot->m_bUpdateChildPosition)
		return;

	pRoot->m_bUpdateChildPosition = true;
	if (pRoot->IsInstanced() == false)
	{
		if (pRoot->IsNeedUpdateSize())
			AUIWidget::CallMeasureAndUpdateSize(pRoot);

		//auto size = pGroupRoot->GetSize();
		//pGroupRoot->MeasureSize( size.x, MeasureSpec::Exactly, size.y, MeasureSpec::Exactly, size.z, MeasureSpec::Exactly );
		pRoot->OnUpdateChildPosition();
		pRoot->m_bUpdateChildPosition = false;
	}
}

const std::vector< std::shared_ptr< AUIWidget > > AUIWidget::GetChildren() const
{
	return AUIApplication::Instance().GetWidgetTree().GetChildren(const_cast<AUIWidget*>(this));
}

std::shared_ptr< AUIWidget > AUIWidget::FindChild(size_t pos) const
{
	if (ChildCount() <= pos)
		return nullptr;

	const auto children = GetChildren();
	return children.at(pos);
}

size_t AUIWidget::ChildCount() const
{
	return AUIApplication::Instance().GetWidgetTree().GetChildCount(const_cast<AUIWidget*>(this));
}

void AUIWidget::OnUpdateChildPosition()
{
	const auto arrChildren = GetChildren();

	for (auto child = arrChildren.begin(); child != arrChildren.end(); child++)
	{
		auto pChildWidget = (*child);
		pChildWidget->OnUpdateChildPosition();
		pChildWidget->Invalidate();
	}
}

void AUIWidget::CallOnUpdateChildPosition(AUIWidget* const pWidget)
{
	if (pWidget == nullptr)
	{
		AUIAssert(!"Invalid widget");
		return;
	}
	pWidget->OnUpdateChildPosition();
	pWidget->m_bUpdateChildPosition = false;
}

void AUIWidget::SetRootTargetCoord(AUICoordSpace eTargetCoord)
{
    //if (!IsRoot())
    //    throw;
    if (auto pInst = GetInstance())
        throw; // can not change target coordinate system during it has instance.
    if (m_spRootInfo)
        m_spRootInfo = std::make_shared<AUIWidgetRootInfo>(*m_spRootInfo);
	else
		m_spRootInfo = std::make_shared<AUIWidgetRootInfo>();
	m_spRootInfo->SetTargetCoord(eTargetCoord);
}

void AUIWidget::SetRootMatrix(const glm::mat4& mat)
{
    //if (!IsRoot())
    //    throw;

	if (m_spRootInfo)
		m_spRootInfo = std::make_shared<AUIWidgetRootInfo>(*m_spRootInfo);
	else
		m_spRootInfo = std::make_shared<AUIWidgetRootInfo>();
	m_spRootInfo->SetMatrix(mat);
    if (auto pInst = GetInstance())
        pInst->OnSetRootMatrix();
}

AUICoordSpace AUIWidget::GetRootTargetCoord() const
{
	return GetRootCoordInfo()->GetTargetCoord();
}

const glm::mat4& AUIWidget::GetRootMatrix() const
{
	//AUIAssert(m_spRootInfo);
	//if (m_spRootInfo)
	//	return m_spRootInfo->GetMatrix();
	//else if (auto pParent = GetParent())
	//	return pParent->GetRootMatrix();
	//else
 //       return s_DefualtRootInfo.GetMatrix();
    return GetRootCoordInfo()->GetMatrix();
}

//const glm::mat4 AUIWidget::GetAccumulatedMatrix() const
//{
//	if (IsRoot())
//		return GetRootMatrix();
//
//	return GetParent()->GetAccumulatedMatrix() * GetRootMatrix();
//}

AUIWidgetManager* AUIWidget::GetWidgetManager() const noexcept
{
	return m_LifeState.GetCurWidgetManager();
}

std::chrono::milliseconds AUIWidget::GetPressTime() const
{
	return GetTimeTick() - m_TimePressStart;
}

void AUIWidget::PreUpdate()
{
	m_bWasDirty = false;

	OnPreUpdate();
}

void AUIWidget::PostUpdate()
{
	OnPostUpdate();

	m_bWasDirty = false;
}

void AUIWidget::SetMaximumSize(const AUIScalar2& size)
{
	m_Property.SetMaximumSize(size);
	m_bNeedUpdateSize = true;

	OnSetDefaultSize(size);
	GetRoot()->m_bNeedUpdateSize = true;
}

void AUIWidget::SetMinimumSize(const AUIScalar2& size)
{
	m_Property.SetMinimumSize(size);
	m_bNeedUpdateSize = true;

	OnSetDefaultSize(size);
	GetRoot()->m_bNeedUpdateSize = true;
}

bool AUIWidget::IsRootCoord() const
{
	auto pParent = GetParent();
	if (pParent == nullptr)
		return true;
	else if (m_spRootInfo)
		return true;
	return false;
}

const AUIWidgetRootInfo* AUIWidget::GetRootCoordInfo() const
{
    //AUIAssert(m_spRootInfo);
    if (m_spRootInfo)
    	return m_spRootInfo.get();
    auto pRootInfo = m_spRootInfo.get();
    auto pParent = GetParent();

    while (!pRootInfo && pParent)
    {
        pRootInfo = pParent->m_spRootInfo.get();
        pParent = pParent->GetParent();
    }
    return pRootInfo?pRootInfo:&s_DefualtRootInfo;
}

void AUIWidget::SetScrollTo(const SkScalar& x, const SkScalar& y)
{
	if (m_ScrollX != x || m_ScrollY != y)
	{
		const auto oldX = m_ScrollX;
		const auto oldY = m_ScrollY;
		m_ScrollX = x;
		m_ScrollY = y;
		OnScrollChanged(m_ScrollX, m_ScrollY, oldX, oldY);
		//UpdateSize();
		UpdateChildPosition();
	}
}

void AUIWidget::SetTooltipText(const std::wstring& message)
{
	if (nullptr == m_pTooltip)
	{
		m_pTooltip = std::make_shared< AUITooltip >();
	}
	AUIAssert(m_pTooltip);
	m_pTooltip->SetMessage(message);
}


bool AUIWidget::Update()
{
	AUIAssert(GetWidgetManager());

	auto hasChanged = false;

	if (IsDirty())
	{
		m_bDirty = false;
		UpdateStyle();
		OnUpdate();

		hasChanged = true;
	}

	return hasChanged;
}

void AUIWidget::Invalidate() noexcept
{
	m_bDirty = true;
	if (auto pWM = GetWidgetManager())
		pWM->SetDirty();
}

void AUIWidget::InvalidateChildren() noexcept
{
	const auto& children = GetChildren();
	for (auto& child : children)
	{
		child->Invalidate();
	}
}

bool AUIWidget::HitTest(glm::vec3& hit) const
{
	const auto boundRect = SkRect::MakeLTRB(
		SkScalarRoundToScalar(GetRangeMinX()),
		SkScalarRoundToScalar(GetRangeMinY()),
		SkScalarRoundToScalar(GetRangeMaxX()),
		SkScalarRoundToScalar(GetRangeMaxY()));

	if (AUISkiaUtil::IsInRect(boundRect,
		SkScalarRoundToScalar(GetMouseLocPosX()),
		SkScalarRoundToScalar(GetMouseLocPosY())))
	{
		hit = glm::vec3(SkScalarRoundToScalar(GetMouseLocPosX()), SkScalarRoundToScalar(GetMouseLocPosY()), 0);
		return true;
	}
	return false;
}

SkPoint AUIWidget::GetMouseLocPos() const
{
    AUIAssert(m_bDefault2DSensor);
    AUIAssert(0 < m_aSensors.size());
    auto pSensor = static_cast<AUIRectangleSensor*>(m_aSensors[0].get());
    const auto pos = pSensor->GetHitPosOnRect();
    return SkPoint::Make(pos.x, pos.y) ;
}

bool AUIWidget::HasMouseLocPos() const
{
    AUIAssert(0 < m_aSensors.size());
    return m_bDefault2DSensor;
}

//SkScalar AUIWidget::GetMouseAbsPosX() const
//{
//    return this->GetMouseAbsPos().fX;
//}
//
//SkScalar AUIWidget::GetMouseAbsPosY() const
//{
//    return this->GetMouseAbsPos().fY;
//}

SkScalar AUIWidget::GetMouseLocPosX() const
{
    AUIAssert(m_bDefault2DSensor);
    AUIAssert(0 < m_aSensors.size());
    auto pSensor = static_cast<AUIRectangleSensor*>(m_aSensors[0].get());
    const auto pos = pSensor->GetHitPosOnRect();
    return pos.x;
}

SkScalar AUIWidget::GetMouseLocPosY() const
{
    AUIAssert(m_bDefault2DSensor);
    AUIAssert(0 < m_aSensors.size());
    auto pSensor = static_cast<AUIRectangleSensor*>(m_aSensors[0].get());
    const auto pos = pSensor->GetHitPosOnRect();
    return pos.y;
}

void AUIWidget::NotifyUIStateChange()
{
    // Notify state change of widget
    AUIApplication::Instance().GetWidgetTree().NotifyUIStateChange(this);
}

void AUIWidget::SetStyleSheet(std::shared_ptr<const AUIWidgetStyle> style){
	if (style)
		m_pStyleUpdator = std::make_shared<AUIStyleUpdator>(style);
	else
		return;

	auto def_style_notion = style->GetDefaultFeature();
	SetStyleNotion(def_style_notion);

	Invalidate();
}

std::shared_ptr<const AUIWidgetStyle> AUIWidget::GetStyleSheet() const
{
	if (m_pStyleUpdator)
		return std::dynamic_pointer_cast<const AUIWidgetStyle, const AUIStateFeature<AUIStyleNotion>>(m_pStyleUpdator->GetStateFeature());
	return nullptr;
}

void AUIWidget::UpdateStyle()
{
	if (!m_pStyleUpdator)
		return;

	auto curr_state = GetUIState();
	auto pNotion = m_pStyleUpdator->GetUpdateFeature(curr_state);
	if (pNotion)
		SetStyleNotion(*pNotion);
}

void AUIWidget::SetStyleNotion(const AUIStyleNotion& notion)
{
	auto& mapNotion = notion.GetValueMap();

	for (auto itr : mapNotion)
	{
		auto& key = itr.first;
		auto& value = itr.second;

		OnSetStyleNotion(key, value);
	}
}

void AUIWidget::OnSetStyleNotion(unsigned int uiKey, const AUIStyleNotionValue& value)
{
	bool bState;
	int iState;
	float fState;
	AUISizePolicy ePolicy;
	std::array< bool, AUIProperty::kGravityOptTotal_GravityOpt > gravityOpt;
	std::array< bool, AUIProperty::kParentOptTotal_ParentOpt > parentOpt;
	//mit::alice::TextHorzAlign eTexHorzAlign;
	//mit::alice::TextVertAlign eTexVertAlign;
	switch (uiKey)
	{
	case MNV_NONE:
		break;
	case 	MNV_VISIBLE:
	{
		if (value.GetValue(bState))
			SetVisible(bState);

	}
	break;
	case 	MNV_DRAGGABLE:
	{
		if (value.GetValue(bState))
			SetDraggable(bState);

	}
	break;
	case 	MNV_IGNORED:
	{
		if (value.GetValue(bState))
			SetIgnored(bState);
	}
	break;
	case 	MNV_DEFAULT_WIDTH:
	{
		if (value.GetValue(iState))
			SetDefaultWidth((SkScalar)iState);
	}
	break;
	case 	MNV_DEFAULT_HEIGHT:
	{
		if (value.GetValue(iState))
			SetDefaultHeight((SkScalar)iState);
	}
	break;
	case 	MNV_BACKGROUND_COLOR:
	{

	}
	break;
	case	MNV_UNDERLINE:
	{

	}
	break;
	case 	MNV_COLOR:
	{

	}
	break;
	case 	MNV_OPACITY:
	{
		if (value.GetValue(fState))
			SetOpacity(fState);
	}
	break;
	case 	MNV_MARGIN_LEFT:
	{
		if (value.GetValue(iState))
			SetMarginLeft((SkScalar)iState);
	}
	break;
	case 	MNV_MARGIN_RIGHT:
	{
		if (value.GetValue(iState))
			SetMarginRight((SkScalar)iState);
	}
	break;
	case 	MNV_MARGIN_TOP:
	{
		if (value.GetValue(iState))
			SetMarginTop((SkScalar)iState);
	}
	break;
	case 	MNV_MARGIN_BOTTOM:
	{
		if (value.GetValue(iState))
			SetMarginBottom((SkScalar)iState);
	}
	break;
	case 	MNV_PADDING_LEFT:
	{
		if (value.GetValue(iState))
			SetPaddingLeft((SkScalar)iState);
	}
	break;
	case 	MNV_PADDING_RIGHT:
	{
		if (value.GetValue(iState))
			SetPaddingRight((SkScalar)iState);
	}
	break;
	case 	MNV_PADDING_TOP:
	{
		if (value.GetValue(iState))
			SetPaddingTop((SkScalar)iState);
	}
	break;
	case 	MNV_PADDING_BOTTOM:
	{
		if (value.GetValue(iState))
			SetPaddingBottom((SkScalar)iState);
	}
	break;
	case 	MNV_WIDTH_POLICY:
	{
		if (value.GetValue(ePolicy))
			SetSizePolicyWidth((AUISizePolicy)ePolicy);

	}
	break;
	case 	MNV_HEIGHT_POLICY:
	{
		if (value.GetValue(ePolicy))
			SetSizePolicyHeight((AUISizePolicy)ePolicy);
	}
	break;
	case MNV_GRAVITY_OPTION:
	{
		if (value.GetValue(gravityOpt))
		{
			if(gravityOpt[AUIProperty::kGravityCenter_GravityOpt])
				SetPropGravityCenter(true);
			if (gravityOpt[AUIProperty::kGravityCenterVertical_GravityOpt])
				SetPropGravityCenterVertical(true);
			if (gravityOpt[AUIProperty::kGravityCenterHorizontal_GravityOpt])
				SetPropGravityCenterHorizontal(true);
			if (gravityOpt[AUIProperty::kGravityLeft_GravityOpt])
				SetPropGravityLeft(true);
			if (gravityOpt[AUIProperty::kGravityTop_GravityOpt])
				SetPropGravityTop(true);
			if (gravityOpt[AUIProperty::kGravityRight_GravityOpt])
				SetPropGravityRight(true);
			if (gravityOpt[AUIProperty::kGravityBottom_GravityOpt])
				SetPropGravityBottom(true);
		}
	}
	break;
	case 	MNV_LAYOUT_GRAVITY_OPTION:
	{
		if (value.GetValue(gravityOpt))
		{
			if(gravityOpt[AUIProperty::kGravityCenter_GravityOpt])
				SetPropLayoutGravityCenter(true);
			if (gravityOpt[AUIProperty::kGravityCenterVertical_GravityOpt])
				SetPropLayoutGravityCenterVertical(true);
			if (gravityOpt[AUIProperty::kGravityCenterHorizontal_GravityOpt])
				SetPropLayoutGravityCenterHorizontal(true);
			if (gravityOpt[AUIProperty::kGravityLeft_GravityOpt])
				SetPropLayoutGravityLeft(true);
			if (gravityOpt[AUIProperty::kGravityTop_GravityOpt])
				SetPropLayoutGravityTop(true);
			if (gravityOpt[AUIProperty::kGravityRight_GravityOpt])
				SetPropLayoutGravityRight(true);
			if (gravityOpt[AUIProperty::kGravityBottom_GravityOpt])
				SetPropLayoutGravityBottom(true);
		}
	}
	break;
	case	MNV_LAYOUT_ALIGN_PARENT:
	{
		if (value.GetValue(parentOpt))
		{
			if(parentOpt[AUIProperty::kParentLeft_ParentOpt])
				SetPropParentLeft(true);
			if (parentOpt[AUIProperty::kParentTop_ParentOpt])
				SetPropParentTop(true);
			if (parentOpt[AUIProperty::kParentRight_ParentOpt])
				SetPropParentRight(true);
			if (parentOpt[AUIProperty::kParentBottom_ParentOpt])
				SetPropParentBottom(true);
			if (parentOpt[AUIProperty::kParentCenterHorizontal_ParentOpt])
				SetPropParentCenterHorizontal(true);
			if (parentOpt[AUIProperty::kParentCenterVertical_ParentOpt])
				SetPropParentCenterVertical(true);
			if (parentOpt[AUIProperty::kParentCenter_ParentOpt])
				SetPropParentCenter(true);
		}
	}
	break;
	case 	MNV_TEXT_HORZONTAL_ALIGN:
	case 	MNV_TEXT_VERTICAL_ALIGN:
	case 	MNV_FONT_SIZE:
	case 	MNV_FONT_FAMILY:
	case 	MNV_BACKGROUND_IMAGE:
	{}
	}
}


void AUIWidget::CallMeasureAndUpdateSize(AUIWidget* const pWidget)
{
	if (nullptr == pWidget)
	{
		AUIAssert(pWidget);
		return;
	}

	const auto isRoot = pWidget->IsRoot();
	const auto defaultSize = pWidget->GetDefaultSize();
	const auto width = defaultSize.fX;
	const auto height = defaultSize.fY;
	AUIMeasureSpec widthSpec = AUIMeasureSpec::kUnspecified;
	AUIMeasureSpec heightSpec = AUIMeasureSpec::kUnspecified;
	AUIMeasureSpec depthSpec = AUIMeasureSpec::kUnspecified;

	switch (pWidget->GetSizePolicyWidth())
	{
	case AUISizePolicy::kFixed:
		widthSpec = AUIMeasureSpec::kExactly;
		break;
	case AUISizePolicy::kContent:
		widthSpec = AUIMeasureSpec::kAtMost;
		break;
	case AUISizePolicy::kParent:    // Measure as root
	default:
		widthSpec = AUIMeasureSpec::kUnspecified;
		break;
	}

	switch (pWidget->GetSizePolicyHeight())
	{
	case AUISizePolicy::kFixed:
		heightSpec = AUIMeasureSpec::kExactly;
		break;
	case AUISizePolicy::kContent:
		heightSpec = AUIMeasureSpec::kAtMost;
		break;
	case AUISizePolicy::kParent:    // Measure as root
	default:
		heightSpec = AUIMeasureSpec::kUnspecified;
		break;
	}

	// Recursive call
	OnCallMeasureAndUpdateSize(pWidget, width, widthSpec, height, heightSpec);

	pWidget->m_bNeedUpdateSize = false;
	pWidget->m_bUpdateChildPosition = true;
	pWidget->Invalidate();
}

AUIScalar2 AUIWidget::GetDefaultMeasureSize(const SkScalar width, AUIMeasureSpec widthSpec, const SkScalar height, AUIMeasureSpec heightSpec) const
{
	const auto spWidth = GetSizePolicyWidth();
	const auto spHeight = GetSizePolicyHeight();

	auto res = GetDefaultSize();

	if (widthSpec == AUIMeasureSpec::kExactly)
	{
		if (spWidth != AUISizePolicy::kFixed)
			res.fX = width;
	}
	else if (widthSpec == AUIMeasureSpec::kAtMost)
	{
		if (spWidth == AUISizePolicy::kParent)
			res.fX = width;
		else if (spWidth == AUISizePolicy::kFixed)
			res.fX = (std::min)(res.fX, width);
		else if (spWidth == AUISizePolicy::kContent)
			res.fX = (std::min)(res.fX, width);
	}
	else if (widthSpec == AUIMeasureSpec::kUnspecified)
	{
		res.fX = res.fX;  // Use default size
	}
	else
	{
        AUIAssertFail();
	}

	if (heightSpec == AUIMeasureSpec::kExactly)
	{
		if (spHeight != AUISizePolicy::kFixed)
			res.fY = height;
	}
	else if (heightSpec == AUIMeasureSpec::kAtMost)
	{
		if (spHeight == AUISizePolicy::kParent)
			res.fY = height;
		else if (spHeight == AUISizePolicy::kFixed)
			res.fY = (std::min)(res.fY, height);
		else if (spHeight == AUISizePolicy::kContent)
			res.fY = (std::min)(res.fY, height);  // Use default size
	}
	else if (heightSpec == AUIMeasureSpec::kUnspecified)
	{
		res.fY = res.fY;  // Use default size
	}
	else
    {
        AUIAssertFail();
	}

	res = AUIScalar2::Bigger(res, GetMinimumSize());
	res = AUIScalar2::Smaller(res, GetMaximumSize());

	return res;
}

void AUIWidget::OnPreMeasureSize()
{

}

void AUIWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
	const auto defaultSize = GetDefaultMeasureSize(width, widthSpec, height, heightSpec);
	SetMeasureSize(defaultSize);
}

void AUIWidget::OnPostMeasureSize()
{

}

void AUIWidget::OnCallMeasureAndUpdateSize(AUIWidget* const pWidget, SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
	if (nullptr == pWidget)
	{
		AUIAssert(pWidget);
		return;
	}

	pWidget->OnBeforeMeasureSize();

	pWidget->OnPreMeasureSize();
	pWidget->OnMeasureSize(width, widthSpec, height, heightSpec);
	pWidget->SetSize(pWidget->GetMeasureSize());
	pWidget->OnPostMeasureSize();

	pWidget->OnAfterMeasureSize(pWidget->GetWidth(), pWidget->GetHeight());
}

bool AUIWidget::IsGrabMouseEvent()
{
	if (IsInstanced() == false)
		return false;
	AUIAssert(GetWidgetManager());
	return GetWidgetManager()->GetWidgetSelection().Exist(shared_from_this());
}

void AUIWidget::GrabMouseEvent()
{
	if (IsInstanced() == false)
		return;
	AUIAssert(GetWidgetManager());
	GetWidgetManager()->GetWidgetSelection().Clear();
	GetWidgetManager()->GetWidgetSelection().PushBack(shared_from_this());
	GetWidgetManager()->SetGrabMouseEvent(true);
}

void AUIWidget::ReleaseMouseEvent()
{
	if (IsInstanced() == false)
		return;
	AUIAssert(GetWidgetManager());
	GetWidgetManager()->GetWidgetSelection().Clear();
	GetWidgetManager()->SetGrabMouseEvent(false);
}

void AUIWidget::ClearPreviewMouseEventCallback()
{
    m_PreviewMouseCallback = {};
}

void AUIWidget::SetupPreviewMouseEventCallback(std::function<bool(MAUIMouseEvent)>&& func)
{
    AUIAssert(false == HasPreviewMouseEventCallback());
    m_PreviewMouseCallback = std::move(func);
}

bool AUIWidget::HasPreviewMouseEventCallback() const
{
    return static_cast<bool>(m_PreviewMouseCallback);
}

bool AUIWidget::OnPreviewMouseEvent(const MAUIMouseEvent& evt)
{
	if (IsFreezed())
		return false;

	bool handled = false;

	// Send event
    if (m_PreviewMouseCallback) {
        handled = m_PreviewMouseCallback(evt);
    }

	return handled;
}

bool AUIWidget::OnMouseEvent(const MAUIMouseEvent& evt)
{
	if (IsFreezed())
		return false;
    UpdateCompass();

	bool handled = false;

	// Send event
	const auto flag = evt.fFlag;
	const auto delta = float(evt.fParam) / float(DefaultWheelDelta);

	switch (evt.fType)
	{
	case MAUIMouseEvent::kLBtnDown_EventType:
		handled = MouseLBtnDown(flag);
		break;
	case MAUIMouseEvent::kLBtnUp_EventType:
		handled = MouseLBtnUp(flag);
		break;
	case MAUIMouseEvent::kLBtnDblClk_EventType:
		handled = MouseLBtnDblClk(flag);
		break;
	case MAUIMouseEvent::kMBtnDown_EventType:
		handled = MouseMBtnDown(flag);
		break;
	case MAUIMouseEvent::kMBtnUp_EventType:
		handled = MouseMBtnUp(flag);
		break;
	case MAUIMouseEvent::kMBtnDblClk_EventType:
		handled = MouseMBtnDblClk(flag);
		break;
	case MAUIMouseEvent::kRBtnDown_EventType:
		handled = MouseRBtnDown(flag);
		break;
	case MAUIMouseEvent::kRBtnUp_EventType:
		handled = MouseRBtnUp(flag);
		break;
	case MAUIMouseEvent::kRBtnDblClk_EventType:
		handled = MouseRBtnDblClk(flag);
		break;
	case MAUIMouseEvent::kMove_EventType:
		handled = MouseMove(flag);
		break;
	case MAUIMouseEvent::kWheel_EventType:
		handled = MouseWheel(flag, delta);
		break;
	default:
		break;
	}

	return handled;
}

bool AUIWidget::OnKeyboardEvent(const AUIKeyboardEvent& evt)
{
	if (IsFreezed())
		return false;

	bool handled = false;
	switch (evt.fType)
	{
	case AUIKeyboardEvent::kKeyDown_EventType:
		handled = KeyDown(evt.fMaskcode, evt.fKeycode, evt.fRepCount, evt.fCharcode);
		break;
	case AUIKeyboardEvent::kKeyUp_EventType:
		handled = KeyUp(evt.fMaskcode, evt.fKeycode, evt.fRepCount, evt.fCharcode);
		break;
	case AUIKeyboardEvent::kChar_EventType:
		handled = KeyChar(evt.fMaskcode, evt.fKeycode, evt.fRepCount, evt.fCharcode);
		break;
	case AUIKeyboardEvent::kIMECompStart_EventType:
		handled = KeyIMEStart();
		break;
	case AUIKeyboardEvent::kIMEComp_EventType:
		handled = KeyIMEComp(evt.fCharcode, evt.fParam);
		break;
	case AUIKeyboardEvent::kIMECompEnd_EventType:
		handled = KeyIMEEnd();
		break;
	case AUIKeyboardEvent::kIMEChar_EventType:
		handled = KeyIMEChar(evt.fCharcode, evt.fParam);
		break;
	default:
		break;
	}

	return handled;
}

void AUIWidget::OnTickTimeEvent(const std::chrono::milliseconds& prevTickTime, const std::chrono::milliseconds& curTickTime)
{
	if (IsFreezed())
		return;

	m_CurTimeTick = curTickTime;
	TickTime(prevTickTime, curTickTime);
}

bool AUIWidget::OnSetCursorEvent(AUICursorIcon& cursoricon)
{
	if (IsFreezed())
		return false;

	bool handled = false;

	handled = OnChangeCursorIcon(cursoricon);

	return handled;
}

bool AUIWidget::OnChangeCursorIcon(AUICursorIcon& cursoricon)
{
	return true;
}

void AUIWidget::MouseEnter()
{
	AUIAssert(IsMouseHover() == false);
	SetHovered(true);

	OnMouseEnter();
    EnterSignal.Send(this);
}

void AUIWidget::MouseLeave()
{
	AUIAssert(IsMouseHover() == true);

	OnMouseLeave();

	m_TimePressStart = std::chrono::milliseconds(0);

	ResetMouseState();
    LeaveSignal.Send(this);
}

void AUIWidget::MouseHover()
{
	AUIAssert(IsMouseHover() == true);

	OnMouseHover();
}

bool AUIWidget::MouseLBtnDblClk(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	handled = OnMouseLBtnDblClk(flag);

	if (IsClickable())
	{
		if (false == IsDisabled())
		{
			DblClickSignal.Send(this);
		}
		m_TimePressStart = std::chrono::milliseconds();
	}

	SetMouseLDown(false);
	return handled;
}

bool AUIWidget::MouseLBtnDown(MAUIMouseEvent::EventFlag flag)
{
	SetMouseLDown(true);
	SetPressed(true);

	bool handled = false;
	handled = OnMouseLBtnDown(flag);

	if (IsDraggable())
	{
		//SetPrevDragPos( GetMouseAbsPosX(), GetMouseAbsPosY() );
		//if ( m_fDragDiffMinX <= 0.0f && m_fDragDiffMinY <= 0.0f )
		//{
		SetDragging(true);
		GrabMouseEvent();
		//}
		handled = true;
	}
	if (IsClickable())
	{
		if (std::chrono::milliseconds::zero() == m_TimePressStart)
			m_TimePressStart = GetTimeTick();
		if (false == IsDisabled())
		{
			PressSignal.Send(this);
		}
	}

	return handled;
}

bool AUIWidget::MouseLBtnUp(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	handled = OnMouseLBtnUp(flag);

	if (IsDragging())
	{
		if (IsDraggable())
		{
			ReleaseMouseEvent();
			handled = true;
		}
		SetDragging(false);
	}
	if (IsClickable())
	{
		if (false == IsDisabled() && IsMouseLDown())
		{
			ClickSignal.Send(this);
		}
		m_TimePressStart = std::chrono::milliseconds::zero();
	}

	SetMouseLDown(false);
	SetPressed(false);
    SetHovered(false);

	return handled;
}

bool AUIWidget::MouseRBtnDblClk(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	handled = OnMouseRBtnDblClk(flag);
	SetMouseRDown(false);
	return handled;
}

bool AUIWidget::MouseRBtnDown(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	SetMouseRDown(true);
	SetPressed(true);
	handled = OnMouseRBtnDown(flag);
	return handled;
}

bool AUIWidget::MouseRBtnUp(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	handled = OnMouseRBtnUp(flag);

    if (IsClickable())
    {
        if (false == IsDisabled() && IsMouseRDown())
        {
            MouseRBtnClickSignal.Send(this);
        }
    }

	SetMouseRDown(false);
	SetPressed(false);
	return handled;
}

bool AUIWidget::MouseMBtnDblClk(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	handled = OnMouseMBtnDblClk(flag);
	SetMouseMDown(false);
	return handled;
}

bool AUIWidget::MouseMBtnDown(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	SetMouseMDown(true);
	SetPressed(true);
	handled = OnMouseMBtnDown(flag);
	return handled;
}

bool AUIWidget::MouseMBtnUp(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	handled = OnMouseMBtnUp(flag);
	SetMouseMDown(false);
	SetPressed(false);
	return handled;
}

bool AUIWidget::MouseMove(MAUIMouseEvent::EventFlag flag)
{
	bool handled = false;
	handled = OnMouseMove(flag);

	if (IsDraggable())
	{
		if (IsDragging() == false && IsMouseLDown())
		{
			//const auto diffX = std::abs( GetMouseAbsPosX() - GetPrevDragPosX() );
			//const auto diffY = std::abs( GetMouseAbsPosY() - GetPrevDragPosY() );

			//if ( std::abs( diffX ) >= m_fDragDiffMinX || std::abs( diffY ) >= m_fDragDiffMinY )
			//{
			SetDragging(true);
			GrabMouseEvent();
			// }
		}

		if (IsDragging() == true)
		{
			OnDragging();
			DragSignal.Send(this);
			//SetPrevDragPos( GetMouseAbsPosX(), GetMouseAbsPosY() );
			//SetPrevDragLocPos( GetMouseLocPosX(), GetMouseLocPosY() );
			//glm::vec3 Pos; glm::vec3 Norm;
			//GetCurMouseLocalRay( Pos, Norm);
			//SetPrevLocalRay(Pos, Norm);
			handled = true;
		}
	}

	return handled;
}

bool AUIWidget::MouseWheel(MAUIMouseEvent::EventFlag flag, float delta)
{
	bool handled = false;
	handled = OnMouseWheel(flag, delta);
	return handled;
}

bool AUIWidget::KeyDown(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode)
{
	return OnKeyDown(mask, keycode, repcount, charcode);
}

bool AUIWidget::KeyUp(AUIKeyboardEvent::MaskCode mask, unsigned int keycode, unsigned int repcount, unsigned int charcode)
{
	bool handled = false;
	if (mask & AUIKeyboardEvent::kCtrlOn_MaskCode)
	{
		if (keycode == MAUIKeycode::kKey_C && IsUseHotkeyCopy())
		{
			handled |= OnCopy();
		}
		else if (keycode == MAUIKeycode::kKey_V && IsUseHotkeyPaste())
		{
			handled |= OnPaste();
		}
		else if (keycode == MAUIKeycode::kKey_X && IsUseHotkeyCut())
		{
			handled |= OnCut();
		}
	}
	if (handled == false)
		return OnKeyUp(mask, keycode, repcount, charcode);
	return handled;
}

bool AUIWidget::KeyChar(AUIKeyboardEvent::MaskCode mask, unsigned int charcode, unsigned int repcount, unsigned int flag)
{
	return OnChar(mask, charcode, repcount, flag);
}

bool AUIWidget::KeyIMEStart()
{
	return OnKeyIMEStart();
}

bool AUIWidget::KeyIMEComp(unsigned int charcode, int64_t param)
{
	return OnKeyIMEComp(charcode, param);
}

bool AUIWidget::KeyIMEEnd()
{
	return OnKeyIMEEnd();
}

bool AUIWidget::KeyIMEChar(unsigned int charcode, int64_t param)
{
	return OnKeyIMEChar(charcode, param);
}

void AUIWidget::TickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime)
{
	OnTickTime(prevTime, curTime);

	if (IsClickable())
	{
		if (false == IsDisabled())
		{
			if (IsMouseLDown())
			{
				if (GetPressTime() > std::chrono::milliseconds::zero())
				{
					PressSignal.Send(this);
				}
			}
		}
	}
}

void AUIWidget::OnTickTime(const std::chrono::milliseconds& prevTime, const std::chrono::milliseconds& curTime)
{
	/* Implement in subclass */
}

void AUIWidget::StartAnimRunning()
{
	m_AnimStartTick = GetTimeTick();
	m_bAnimRunning = true;
	Invalidate();
}

void AUIWidget::StopAnimRunning()
{
	m_bAnimRunning = false;
	Invalidate();
}

void AUIWidget::ResetAnimRunning()
{
    m_AnimStartTick = std::chrono::milliseconds::zero();
    m_bAnimRunning = false;
    Invalidate();
}

void AUIWidget::_invalidate_sensor()
{
    if (IsInstanced())
        GetWidgetManager()->InvalidateSensor(this);
}

void AUIWidget::AddCompass(const std::shared_ptr< AUICompass >& pCompass)
{
	m_aCompasses.emplace_back(pCompass);
    UpdateCompass();
}
void AUIWidget::UpdateCompass()
{
    auto pWidgetManager = GetWidgetManager();
    if (!pWidgetManager)
        return;
    const auto org = glm::vec3(pWidgetManager->GetMouseOrg());
    const auto dir = glm::vec3(pWidgetManager->GetMouseDir());

    for (auto& pCompass : m_aCompasses)
        pCompass->CalcControlPosition(org, dir);
}

void AUIWidget::UpdateSize()
{
	const auto pRootWidget = GetRoot();
	AUIAssert(pRootWidget);

	pRootWidget->m_bNeedUpdateSize = true;
	if (pRootWidget->IsCreated() == false)
		CallMeasureAndUpdateSize(this);
}

//const AUISensor* AUIWidget::GetCurSensor() const
//{
//	auto pInst = GetInstance();
//	if (!pInst)
//		return nullptr;
//
//	return pInst->GetCurSensor();
//}

void AUIWidget::LoadDefault2DSensor()
{
	//m_bDefault2DCompass = true;
	m_bDefault2DSensor = true;

	//auto pPlaneCompass = std::make_shared<AUIPlaneCompass>();
	//pPlaneCompass->SetPlane(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 0, 0));
	//AddCompass(pPlaneCompass);

	auto pRectangleSensor = std::make_shared<AUIRectangleSensor>();
	AddSensor(pRectangleSensor);

	UpdateDefault2DSensorSize();
}

void AUIWidget::UpdateDefault2DSensorSize()
{
	AUIAssert(m_bDefault2DSensor);
    AUIAssert(0 < m_aSensors.size());
    auto pRectSensor = static_cast<AUIRectangleSensor*>(m_aSensors[0].get());

    auto pos = GetPositionAtRoot();

    pRectSensor->SetRectangle(pos.fX, pos.fY, GetWidth(), GetHeight());
    //m_aSensors[0]->SetAABB(0.0f, 0.0f, GetWidth(), GetHeight(), 0.0f, 0.0f);
}

AUIInstance* AUIWidget::GetInstance() const
{
	return m_LifeState.GetCurInstance().lock().get();
}

AUIDrawable* AUIWidget::GetAsDrawable() const
{
    return nullptr;
}
