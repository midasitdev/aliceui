#include "pch.h"
#include "AUISlot.h"

AUISlot::AUISlot() noexcept
{
}

AUISlot::~AUISlot()
{
    // At least 2 ('this' and from original MSignal)
    if (2 >= m_pInfo.use_count())
        Disconnect();
}

AUISlot::AUISlot(const std::shared_ptr<Info>& info) noexcept
    : m_pInfo(info)
{

}

AUISlot::AUISlot(const AUISlot& other)
{
    *this = other;
}

AUISlot AUISlot::CreateSlot(bool lockfree)
{
    return AUISlot(std::make_shared<Info>(lockfree));
}

bool AUISlot::Disconnect(bool wait)
{
    if (m_pInfo == nullptr)
        return false;

    LockGuard guard(m_pInfo);
    return m_pInfo->Disconnect(wait);
}

bool AUISlot::IsValid() const
{
    if (m_pInfo == nullptr)
        return false;
    LockGuard guard(m_pInfo);
    return m_pInfo->fValid;
}

AUISlot& AUISlot::operator=(const AUISlot& other)
{
    m_pInfo = other.m_pInfo;
    m_bEnabled = other.m_bEnabled;
    return *this;
}

AUISlot::Info::~Info()
{
    Disconnect(false);
}

bool AUISlot::Info::Disconnect(bool wait)
{
    const auto isPrevValid = fValid;
    fValid = false;
    if (wait)
    {
        // Thread wait
        while (fCallCount > 0)
            std::this_thread::yield();
    }
    return isPrevValid;
}
