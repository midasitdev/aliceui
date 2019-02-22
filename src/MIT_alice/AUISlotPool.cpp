#include "pch.h"
#include "AUISlotPool.h"

AUISlotPool::AUISlotPool()
{

}

AUISlotPool::AUISlotPool(const AUISlotPool& cp)
{
    *this = cp;
}

AUISlotPool::~AUISlotPool()
{
    DisconnectAll(true);
}

void AUISlotPool::DisconnectAll(bool wait)
{
    for (auto&& c : m_SlotPool)
        c.Disconnect(false);
    if (wait)
    {
        for (auto&& c : m_SlotPool)
            c.Disconnect(true);
    }
    m_SlotPool.clear();
}

void AUISlotPool::SetSignalOpen(bool state)
{
    m_bSignalOpen = state;

    for (auto& s : m_SlotPool)
        s.SetEnabled(IsSignalOpen());
}

AUISlotPool& AUISlotPool::operator=(const AUISlotPool& cp)
{
    m_SlotPool = std::move(cp.m_SlotPool);
    m_bSignalOpen = cp.m_bSignalOpen;
    return *this;
}

void AUISlotPool::_AddSlot(AUISlot& c)
{
    c.SetEnabled(m_bSignalOpen);
    if (c.IsValid())
        m_SlotPool.emplace_back(std::move(c));
}
