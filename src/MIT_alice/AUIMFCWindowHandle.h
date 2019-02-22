#pragma once

#include "AUIMFCHandle.h"
#include "AUIWnd.h"

class ALICEUI_API AUIMFCWindowHandle : public AUIMFCHandle
{
    using SuperClass = AUIMFCHandle;
public:
    AUIMFCWindowHandle();
    ~AUIMFCWindowHandle() noexcept override = default;


    //////////////////////////////////////////////////////////////////////////
    // Widget
public:
    void SetRootWidget(const std::shared_ptr< AUIWidget >& pWidget) override;


    //////////////////////////////////////////////////////////////////////////
    // Activate / Deactivate
public:
    void Activate(AUIHandle* const pParent) override;
    void ActivateModal(AUIHandle* const pParent) override;
    void Deactivate() override;

    //////////////////////////////////////////////////////////////////////////
    // Size / Position
public:
    void SetMinSize(int width, int height) override;
    void SetMaxSize(int width, int height) override;

    //////////////////////////////////////////////////////////////////////////
    // Transparency
public:
    void SetTransparent(bool val) override;
    bool IsTransparent() const override;


    //////////////////////////////////////////////////////////////////////////
    // AUIWnd
private:
    AUIWnd m_wnd;
};
