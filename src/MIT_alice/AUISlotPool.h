#pragma once

#include "AUISlot.h"
#include <vector>

class ALICEUI_API AUISlotPool
{
public:
    AUISlotPool();
    virtual ~AUISlotPool();

    //////////////////////////////////////////////////////////////////////////
    // Copy / Move
public:
    AUISlotPool(const AUISlotPool& cp);
    AUISlotPool& operator=(const AUISlotPool& cp);
    AUISlotPool(AUISlotPool&&) noexcept = default;
    AUISlotPool& operator=(AUISlotPool&&) noexcept = default;

    //////////////////////////////////////////////////////////////////////////
    // Slot control
public:
    void SetSignalOpen(bool state);
    bool IsSignalOpen() const noexcept {
        return m_bSignalOpen;
    }
private:
    bool m_bSignalOpen = true;


    //////////////////////////////////////////////////////////////////////////
    // Connection to signal & generate slot
public:
    void DisconnectAll(bool wait = false);

    template<typename _Signal, typename... _Arg>
    inline AUISlot Connect(_Signal& s, _Arg... ars)
    {
        auto c = s.Bind(std::forward<_Arg>(ars)...);
        _AddSlot(c);
        return c;
    }
    //////////////////////////////////////////////////////////////////////////
    // Slot pool
private:
    void _AddSlot(AUISlot& c);
    std::vector<AUISlot> m_SlotPool;
};
