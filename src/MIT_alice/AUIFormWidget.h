#pragma once

#include "AUILinearLayoutWidget.h"

class AUITitleBarTitleWidget;

class ALICEUI_API AUIFormWidget : public AUILinearLayoutWidget
{
public:
    AUIFormWidget();
    explicit AUIFormWidget(bool moveable);
    virtual ~AUIFormWidget();
    virtual void SetPosition(const AUIScalar3& pos) override;
    virtual AUIScalar3 GetPosition() const override;
private:
    void InitWidget();


    //////////////////////////////////////////////////////////////////////////
    // Moveable
public:
    void SetMoveable(bool state) { m_bMoveable = state; }
    bool IsMoveable() const { return m_bMoveable; }
private:
    bool m_bMoveable;



    //    //////////////////////////////////////////////////////////////////////////
    //    // Size
    //protected:
    //    virtual void OnSetSize( float& width, float& height, float& length ) override;


        //////////////////////////////////////////////////////////////////////////
        // TitleBar
public:
    void SetTitleCaption(const std::wstring& text);
    AUITitleBarTitleWidget* const GetTitleBarWidget() const { return m_pTitleBar.get(); }
private:
    void OnDraggingTitleBar(AUIWidget* const, float dx, float dy);
    std::shared_ptr< AUITitleBarTitleWidget > m_pTitleBar;
};
