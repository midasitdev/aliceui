#pragma once

#include <functional>
#include <mutex>
#include <memory>
#include <vector>
#include "AUISlot.h"

template<typename _FunctionType, bool _IsLockFree = true>
class AUISignal final
{
public:
    AUISignal() noexcept : m_bLockFree(_IsLockFree) {}
    ~AUISignal() {
        DisconnectAll(true);
    }
    // Move
    AUISignal(AUISignal&& other) : m_bLockFree(other.m_bLockFree) {
        if (other.IsLockFree())
        {
            m_SignalTargets = std::move(other.m_SignalTargets);
        }
        else
        {
            std::unique_lock< std::mutex > guardThis(m_mutexSignalTargets, std::defer_lock);
            std::unique_lock< std::mutex > guardOther(other.m_mutexSignalTargets, std::defer_lock);
            std::lock(guardThis, guardOther);
            m_SignalTargets = std::move(other.m_SignalTargets);
        }
    }
    // No copy
    AUISignal(const AUISignal&) = delete;
    AUISignal& operator=(const AUISignal&) = delete;


    //////////////////////////////////////////////////////////////////////////
    // Lock-Free
public:
    inline constexpr bool IsLockFree() const noexcept {
        return m_bLockFree;
    }
    inline constexpr bool IsNotLockFree() const noexcept {
        return !m_bLockFree;
    }
protected:
    inline void Lock() const {
        if (IsNotLockFree())
            m_mutexSignalTargets.lock();
    }
    inline void Unlock() const {
        if (IsNotLockFree())
            m_mutexSignalTargets.unlock();
    }
private:
    const bool m_bLockFree = true;
    mutable std::mutex m_mutexSignalTargets;
    mutable bool m_bSending = false;


    //////////////////////////////////////////////////////////////////////////
    // Send signal
public:
    template<typename... _Arg>
    inline void Send(_Arg... args)
    {
        if (m_bSending)
            return;

        this->Lock();
        m_bSending = true;
        for (auto& target : m_SignalTargets)
            target.fSlot.Emit(target.fFunc, args...);
        m_bSending = false;
        this->Unlock();
    }

    //////////////////////////////////////////////////////////////////////////
    // Signal Data
private:
    struct TargetData
    {
        AUISlot fSlot;
        std::function<_FunctionType> fFunc;

        TargetData(AUISlot& s, std::function<_FunctionType> f) : fSlot(s), fFunc(std::move(f)) {}
    };
    std::vector<TargetData> m_SignalTargets;


    //////////////////////////////////////////////////////////////////////////
    // Bind with function
public:
    [[nodiscard]] inline AUISlot Bind(std::function<_FunctionType> func)
    {
        auto c = AUISlot::CreateSlot(IsLockFree());
        std::vector<TargetData> newTargets;

        this->Lock();
        // Remove invalid connections
        newTargets.reserve(m_SignalTargets.size() + 1);
        for (const auto& t : m_SignalTargets) {
            if (t.fSlot.IsValid())
                newTargets.emplace_back(t);
        }
        newTargets.emplace_back(c, std::move(func));
        std::swap(m_SignalTargets, newTargets);
        this->Unlock();

        return c;
    }

    template <class _Class, typename... _Arg>
    [[nodiscard]] inline AUISlot Bind(_Class* pClass, void(_Class::*pFunc)(_Arg... args))
    {
        return Bind([=](_Arg... args) {
            (pClass->*pFunc)(args...);
        });
    }
    void DisconnectAll(bool wait)
    {
        std::vector<TargetData> targets;

        this->Lock();
        std::swap(m_SignalTargets, targets);
        this->Unlock();

        for (auto& target : targets)
            target.fSlot.Disconnect(wait);
    }

};
