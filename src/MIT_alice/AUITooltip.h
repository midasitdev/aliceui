#pragma once

#include "AUIAPIDef.h"
#include "AUIBasicEnumDef.h"


class ALICEUI_API AUITooltip : public std::enable_shared_from_this<AUITooltip>
{
public:
    AUITooltip();
    virtual ~AUITooltip();


    //////////////////////////////////////////////////////////////////////////
    // Show Duration
public:
    void SetShowDuration(const std::chrono::milliseconds& duration) { m_ShowDuration = duration; }
    std::chrono::milliseconds GetShowDuration() const { return m_ShowDuration; }
private:
    std::chrono::milliseconds m_ShowDuration;


    //////////////////////////////////////////////////////////////////////////
    // Message
public:
    void SetMessage(const std::wstring& message) { m_Message = message; }
    std::wstring GetMessage() const { return m_Message; }
private:
    std::wstring m_Message;

public:
    void SetPopupOpt(AUIPopupPos opt) {
        m_PopupOpt = opt;
    }
    AUIPopupPos GetPopupOpt() const {
        return m_PopupOpt;
    }
private:
    AUIPopupPos m_PopupOpt = AUIPopupPos::kOptimal;
};
