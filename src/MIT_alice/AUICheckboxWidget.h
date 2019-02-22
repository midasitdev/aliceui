#pragma once


#include "AUICommonDef.h"
#include "AUIDrawableWidget.h"

class ALICEUI_API AUICheckboxWidget : public AUIDrawableWidget
{
    typedef AUIDrawableWidget SuperWidget;
public:
    AUICheckboxWidget();
    explicit AUICheckboxWidget(bool state);
    virtual ~AUICheckboxWidget();

	//////////////////////////////////////////////////////////////////////////
	// Create & Destroy
public:
	virtual void OnDestroy() override;

    //////////////////////////////////////////////////////////////////////////
    // State
public:
    void SetUseIndeterminate(bool use) { m_bUseIndeterminate = use; }
    bool IsUseIndeterminate() const { return m_bUseIndeterminate; }
    void SetLocked(bool locked);
    bool IsLocked() const;

private:
    bool m_bUseIndeterminate;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    virtual void OnDraw(SkCanvas* const canvas) override;


    //////////////////////////////////////////////////////////////////////////
    // Mouse event
protected:
    virtual void OnMouseEnter() override;
    virtual void OnMouseLeave() override;
    virtual bool OnMouseLBtnDown(MAUIMouseEvent::EventFlag flag) override;
    virtual bool OnMouseLBtnUp(MAUIMouseEvent::EventFlag flag) override;


    //////////////////////////////////////////////////////////////////////////
    // State & animation
protected:
    bool IsPrevChecked() const { return m_bPrevChecked; }
    void SetPrevChecked(bool state) { m_bPrevChecked = state; }
    bool IsPrevCheckedIndeterminate() const { return m_bPrevCheckedIndeterminate; }
    void SetPrevCheckedIndeterminate(bool state) { m_bPrevCheckedIndeterminate = state; }

private:
    bool m_bPrevChecked;
    bool m_bPrevCheckedIndeterminate;

    //////////////////////////////////////////////////////////////////////////
    // Drawable
public:
    virtual void SetBackgroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable) override;
    virtual void SetForegroundDrawable(const std::shared_ptr< AUIDrawable >& pDrawable) override;
    void SetCheckAnimDrawable(const std::shared_ptr< AUIDrawable >& pDrawable) { m_pCheckAnimDrawable = pDrawable; Invalidate(); }
    AUIDrawable* const GetCheckAnimDrawable() const { return m_pCheckAnimDrawable.get(); }
    void SetAnimTickLength(std::chrono::milliseconds tick) { m_AnimTickLength = tick; }
    std::chrono::milliseconds GetAnimTickLength() const { return m_AnimTickLength; }
private:
    std::shared_ptr< AUIDrawable > m_pCheckAnimDrawable;
    std::chrono::milliseconds m_AnimTickLength;
};
