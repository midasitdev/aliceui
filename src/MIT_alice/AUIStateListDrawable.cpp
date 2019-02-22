#include "pch.h"
#include "AUIStateListDrawable.h"
#include "AUIDrawable.h"
#include "AUIAnimationListDrawable.h"

AUIStateListDrawable::AUIStateListDrawable()
    : m_bRefreshDraw(false)
{

}

AUIStateListDrawable::~AUIStateListDrawable()
{

}

void AUIStateListDrawable::OnDraw(SkCanvas* const canvas)
{
    m_bRefreshDraw = false;
	const auto padding = GetDrawPadding();
	//canvas->translate( padding.left(), padding.top() );
	const auto bound = GetDrawBound();
	canvas->clipRect(SkRect::MakeLTRB(bound.left() + padding.left(), bound.top() + padding.top(), bound.right() - padding.right(), bound.bottom() - padding.bottom()));


	//if (m_pTransitionAnimDrawable)
	//{
	//	m_pTransitionAnimDrawable->Draw(canvas);
	//	// term
	//	//m_pTransitionAnimDrawable->Stop();
	//	if (false == m_pTransitionAnimDrawable->IsRunning() ||
	//		(m_pTransitionAnimDrawable->IsRunning() && m_pTransitionAnimDrawable->GetRunCount() > 0))
	//	{
	//		m_pTransitionAnimDrawable = nullptr;
	//	}
	
	if (m_pCurDrawable)
		m_pCurDrawable->Draw(canvas);

}

void AUIStateListDrawable::OnChangeDrawUIState()
{
	if (!m_pStateUpdtator)
		return;
	const auto& state = GetDrawUIState();
	auto pFeature = m_pStateUpdtator->GetUpdateFeature(state);
	if (pFeature)
		m_pCurDrawable = pFeature->_drawable;

    m_bRefreshDraw = true;
}

void AUIStateListDrawable::SetStateImgsrc(std::shared_ptr<AUIStateImgSrc> pSrc)
{
	m_pStateUpdtator = std::make_shared<AUIStateImgSrcUpdator>(pSrc);
	const auto pFeature = pSrc->_default_feature();
	m_pCurDrawable = pFeature._drawable;
}

void AUIStateListDrawable::OnSetDrawBound()
{
	const auto bound = GetDrawBound();
	const auto padding = GetDrawPadding();
	const auto subbound = SkRect::MakeLTRB(bound.left() + padding.left(), bound.top() + padding.top(), bound.right() - padding.right(), bound.bottom() - padding.bottom());


	if(m_pCurDrawable)
		m_pCurDrawable->SetDrawBound(subbound);
}

AUIStateImgSrcUpdator::AUIStateImgSrcUpdator(std::shared_ptr<AUIStateImgSrc> pSrc)
    : AUIStateFeatureUpdator<AUIImageSrcData>(pSrc)
{

}
