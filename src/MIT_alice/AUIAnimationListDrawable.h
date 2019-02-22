#pragma once

#include "AUIDrawable.h"

#include <chrono>

class ALICEUI_API AUIAnimationListDrawable : public AUIDrawable
{
    using Time = std::chrono::milliseconds;
public:
    AUIAnimationListDrawable();
    virtual ~AUIAnimationListDrawable();

    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;
    virtual bool IsRefreshDraw() const override {
        return IsRunning();
    }


    //////////////////////////////////////////////////////////////////////////
    // State
public:
    bool IsRunning() const { return m_bRunning; }
    void Start();
    void Stop();
private:
    bool m_bRunning;
    Time m_StartTime;

    //////////////////////////////////////////////////////////////////////////
    // Option
public:
    bool IsRepeat() const {
        return m_bRepeat;
    }
    void SetRepeat(bool repeat) {
        m_bRepeat = repeat;
    }
    size_t GetRunCount() const {
        return m_RunCount;
    }
private:
    bool m_bRepeat;
    size_t m_RunCount;



    //////////////////////////////////////////////////////////////////////////
    // Frame Data
public:
    struct FrameData final
    {
        std::shared_ptr< AUIDrawable > fDrawable;
        Time fDuration;

        FrameData() noexcept : fDuration(0) {}
        FrameData(const std::shared_ptr< AUIDrawable >& _pDrawable, const Time& _duration) noexcept : fDrawable(_pDrawable), fDuration(_duration) {}
        FrameData(FrameData&& _framedata) = default;
        FrameData(const FrameData& _framedata) = default;
        FrameData& operator=(const FrameData&) = default;
        FrameData& operator=(FrameData&&) = default;
    };
    void ClearFrameData()
    {
        m_ItemData.clear();
    }
    void EmplaceFrameData(const std::shared_ptr< AUIDrawable >& pDrawable, const int& duration)
    {
        m_ItemData.emplace_back(pDrawable, Time(duration));
    }
    void EmplaceFrameData(const std::shared_ptr< AUIDrawable >& pDrawable, const Time& duration)
    {
        m_ItemData.emplace_back(pDrawable, duration);
    }
    void EmplaceFrameData(const FrameData& framedata)
    {
        m_ItemData.emplace_back(framedata);
    }
    size_t GetFrameCount() const
    {
        return m_ItemData.size();
    }
    Time GetTotalDuration() const {
        Time totalTime(0);
        for (const auto& item : m_ItemData) {
            totalTime += item.fDuration;
        }
        return totalTime;
    }
private:
    std::vector< FrameData > m_ItemData;
};
