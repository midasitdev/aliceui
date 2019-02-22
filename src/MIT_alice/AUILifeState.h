#pragma once


#include "AUIAPIDef.h"
#include <array>
#include <memory>


class AUIWidgetManager;
class AUIInstance;


class ALICEUI_API AUILifeState final
{
public:
    AUILifeState() noexcept;
    AUILifeState(const AUILifeState& state) noexcept;
    ~AUILifeState() = default;

public:
    enum State : unsigned int
    {
        kCreated_State = 0,

        kPendingCreate_State,
        kPendingDestroy_State,

        // Total
        kStateTotal_State
    };
    void Reset();
    void ResetState()
    {
        std::fill(m_States.begin(), m_States.end(), false);
    }
    void SetCreated(bool val) noexcept
    {
        SetState(kCreated_State, val);
    }
    void SetPendingCreate(bool val) noexcept
    {
        SetState(kPendingCreate_State, val);
    }
    void SetPendingDestroy(bool val) noexcept
    {
        SetState(kPendingDestroy_State, val);
    }
    bool IsCreated() const noexcept
    {
        return GetState(kCreated_State);
    }
    bool IsPendingCreate() const noexcept
    {
        return GetState(kPendingCreate_State);
    }
    bool IsPendingDestory() const noexcept
    {
        return GetState(kPendingDestroy_State);
    }
private:
    void SetState(State state, bool val) noexcept
    {
        m_States[state] = val;
    }
    bool GetState(State state) const noexcept
    {
        return m_States[state];
    }
    std::array< bool, kStateTotal_State > m_States = { false, };

    //////////////////////////////////////////////////////////////////////////
    // Widget Manager
public:
    void ResetWidgetManagers() noexcept;
    AUIWidgetManager* GetCurWidgetManager() const noexcept {
        return m_pCurWidgetManager;
    }
    AUIWidgetManager* GetPendingCreateWidgetManager() const noexcept {
        return m_pPendingCreateWidgetManager;
    }
    AUIWidgetManager* GetPendingDestroyWidgetManager() const noexcept {
        return m_pPendingDestroyWidgetManager;
    }
    void SetCurWidgetManager(AUIWidgetManager* pWidgetManager) noexcept {
        m_pCurWidgetManager = pWidgetManager;
    }
    void SetPendingCreateWidgetManager(AUIWidgetManager* pWidgetManager) noexcept {
        m_pPendingCreateWidgetManager = pWidgetManager;
    }
    void SetPendingDestroyWidgetManager(AUIWidgetManager* pWidgetManager) noexcept {
        m_pPendingDestroyWidgetManager = pWidgetManager;
    }
private:
    AUIWidgetManager* m_pCurWidgetManager = nullptr;
    AUIWidgetManager* m_pPendingCreateWidgetManager = nullptr;
    AUIWidgetManager* m_pPendingDestroyWidgetManager = nullptr;

    //////////////////////////////////////////////////////////////////////////
    // Instance
public:
    void ResetCurInstance() noexcept;
    void SetCurInstance(const std::weak_ptr< AUIInstance >& wpInstance) noexcept {
        m_wpCurInstance = wpInstance;
    }
    std::weak_ptr< AUIInstance > GetCurInstance() const noexcept {
        return m_wpCurInstance;
    }
private:
    std::weak_ptr< AUIInstance > m_wpCurInstance;
};
