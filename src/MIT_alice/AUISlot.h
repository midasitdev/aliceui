#pragma once

#include <atomic>
#include <memory>
#include <thread>
#include <mutex>

#include "AUIAPIDef.h"
#include "AUIDebug.h"

class ALICEUI_API AUISlot final
{
public:
    AUISlot() noexcept;
    ~AUISlot();

    // Copy
    AUISlot(const AUISlot& other);
    AUISlot& operator=(const AUISlot& other);

    // Move
    AUISlot(AUISlot&&) noexcept = default;
    AUISlot& operator=(AUISlot&&) noexcept = default;

    //////////////////////////////////////////////////////////////////////////
    // Create
public:
    [[nodiscard]] static AUISlot CreateSlot(bool lockfree);


    //////////////////////////////////////////////////////////////////////////
    // Slot Info
public:
    struct ALICEUI_API Info final
    {
        const bool fLockFree = true;
        bool fValid = true;
        int fCallCount = 0;
        std::mutex fMutex;

        Info() = delete;
        Info(bool lockfree) : fLockFree(lockfree) {}
        ~Info();
        bool Disconnect(bool wait);
    };
    AUISlot(const std::shared_ptr<Info>& info) noexcept;
    std::weak_ptr<Info> GetInfo() const {
        return m_pInfo;
    }
private:
    std::shared_ptr<Info> m_pInfo;


    //////////////////////////////////////////////////////////////////////////
    // Slot Status
public:
    bool IsEnabled() const {
        return m_bEnabled;
    }
    void SetEnabled(bool status) {
        m_bEnabled = status;
    }
private:
    bool m_bEnabled = true;


    //////////////////////////////////////////////////////////////////////////
    // Slot status control
public:
    bool IsValid() const;
    bool Disconnect(bool wait = false);


    //////////////////////////////////////////////////////////////////////////
    // Slot Emission
private:
    struct LockGuard final
    {
        const std::shared_ptr<Info>& fInfo;

        LockGuard() = delete;
        LockGuard(const std::shared_ptr<Info>& info) noexcept : fInfo(info) {
            if (false == fInfo->fLockFree)
                fInfo->fMutex.lock();
        }
        ~LockGuard() {
            if (false == fInfo->fLockFree)
                fInfo->fMutex.unlock();
        }
    };
public:
    template<typename _Func, typename... _Arg>
    inline void Emit(_Func&& func, _Arg... args)
    {
        if (IsEnabled() == false)
            return;
        if (m_pInfo == nullptr)
            return;
        LockGuard guard(m_pInfo);
        if (m_pInfo->fValid == false)
            return;

        ++m_pInfo->fCallCount;
        func(std::forward<_Arg>(args)...);
        --m_pInfo->fCallCount;
    }
};
