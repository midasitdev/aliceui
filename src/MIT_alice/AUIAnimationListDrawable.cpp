#include "pch.h"
#include "AUIAnimationListDrawable.h"

AUIAnimationListDrawable::AUIAnimationListDrawable()
    : m_bRunning(false)
    , m_bRepeat(false)
    , m_StartTime(0)
	, m_RunCount(0)
{

}

AUIAnimationListDrawable::~AUIAnimationListDrawable()
{

}

void AUIAnimationListDrawable::Start()
{
    m_bRunning = true;
    m_StartTime = std::chrono::duration_cast<Time>(std::chrono::system_clock::now().time_since_epoch());
	m_RunCount = 0;
}

void AUIAnimationListDrawable::Stop()
{
    m_bRunning = false;
	m_RunCount = 0;
}

void AUIAnimationListDrawable::OnDraw( SkCanvas* const canvas )
{
    if (false == IsRunning())
        return;
    if (0 == m_ItemData.size())
        return;

    const auto curTime = std::chrono::duration_cast<Time>(std::chrono::system_clock::now().time_since_epoch());
    const auto diffTime = curTime - m_StartTime;

    AUIAssert(m_ItemData.size() > 0);
    bool isLast = false;
    Time tmpTime(0);
    FrameData targetFrame = m_ItemData[0];
    for (size_t idx = 0 ; idx < m_ItemData.size() ; ++idx)
    {
        const auto& item = m_ItemData[idx];
        tmpTime += item.fDuration;
        if (diffTime > tmpTime)
        {
            targetFrame = item;
            if (m_ItemData.size() - 1 == idx)
                isLast = true;
        }
        else
        {
            break;
        }
    }
    if (targetFrame.fDrawable)
    {
        targetFrame.fDrawable->SetDrawBound(GetDrawBound());
        targetFrame.fDrawable->SetDrawPadding(GetDrawPadding());
        targetFrame.fDrawable->SetDrawUIState(GetDrawUIState());
        targetFrame.fDrawable->Draw(canvas);
    }

    if (isLast)
    {
		m_RunCount++;
        if (false == IsRepeat())
            Stop();
        else
            Start();
    }
}
