#pragma once

#include "AUISignal.h"

#include <string>
#include <initializer_list>
#include <tuple>
#include <unordered_map>

template<typename _State, typename _Trigger>
class AUIAutomata
{
public:
    AUIAutomata() = delete;
    AUIAutomata(const _State& initState) : m_StateData(initState) {}
    AUIAutomata(const _State& initState, std::initializer_list<std::tuple<_State, _Trigger, _State>> initAutomata) : AUIAutomata(initState) {
        for (const auto& a : initAutomata) {
            this->Define(std::get<0>(a)).Allow(std::get<1>(a), std::get<2>(a));
        }
    }
    ~AUIAutomata() = default;

    AUIAutomata(const AUIAutomata&) = delete;
    AUIAutomata& operator=(const AUIAutomata&) = delete;

    AUIAutomata(AUIAutomata&&) = default;
    AUIAutomata& operator=(AUIAutomata&&) = default;


    //////////////////////////////////////////////////////////////////////////
    // Signals
public:
    // Transition failed signal
    // void signalFunc( const _State& _curState, const _Trigger& _failedTrigger );
    AUISignal< void(const _State&, const _Trigger&) > SignalTransitionFailed;

    // Transition succeed signal
    // void signalFunc( const _State& _fromState, const _State& _toState, const _Trigger& _succeedTrigger );
    AUISignal< void(AUIAutomata<_State, _Trigger>*, const _State&, const _State&, const _Trigger&) > SignalTransitionSucceed;


    //////////////////////////////////////////////////////////////////////////
    // Transition
public:
    void Transition(const _Trigger& _trigger) {
        const auto oldState = this->GetState();
        if (m_RuleSet.HasRule(this->GetState())) {
            _State newState;
            if (m_RuleSet.GetNextState(oldState, _trigger, newState)) {
                this->SetState(newState);
                this->SignalTransitionSucceed.Send(this, oldState, newState, _trigger);
                return;
            }
        }
        this->SignalTransitionFailed.Send(oldState, _trigger);
    }


    //////////////////////////////////////////////////////////////////////////
    // Rule
public:
    class Rule
    {
    public:
        Rule() = default;
        Rule(const Rule&) = default;
        Rule& operator=(const Rule&) = default;
        Rule(Rule&&) = default;
        Rule& operator=(Rule&&) = default;
    public:
        Rule& Allow(const _Trigger& _trigger, const _State& _toState) {
            m_mapTriggerToState[_trigger] = _toState;
            return *this;
        }
        bool Next(const _Trigger& _trigger, _State& _nextState) const {
            const auto found = m_mapTriggerToState.find(_trigger);
            if (std::end(m_mapTriggerToState) == found)
                return false;
            _nextState = found->second;
            return true;
        }
    private:
        std::unordered_map<_Trigger, _State> m_mapTriggerToState;
    };
    Rule& Define(const _State& _state) {
        return m_RuleSet.GetOrCreateRule(_state);
    }
private:
    class RuleSet final
    {
    public:
        RuleSet() = default;
        bool GetNextState(const _State& _curState, const _Trigger _trigger, _State& _nextState) const {
            return this->GetRule(_curState).Next(_trigger, _nextState);
        }
        const Rule& GetRule(const _State& _state) const {
            const auto _found = m_StateRule.find(_state);
            if (std::end(m_StateRule) == _found)
                return m_EmptyRule;
            return _found->second;
        }
        Rule& GetOrCreateRule(const _State& _state) {
            return m_StateRule[_state];
        }
        bool HasRule(const _State& _state) const {
            return (std::end(m_StateRule) != m_StateRule.find(_state));
        }
    private:
        std::unordered_map<_State, Rule> m_StateRule;
        Rule m_EmptyRule;
    };
    RuleSet m_RuleSet;

    //////////////////////////////////////////////////////////////////////////
    // State
public:
    _State GetState() const {
        return m_StateData.Get();
    }
private:
    void SetState(const _State& _state) {
        m_StateData.Set(_state);
    }
    class StateData final
    {
    public:
        StateData() = delete;
        StateData(const _State& state) : m_State(state) {}
        _State Get() const {
            return m_State;
        }
        void Set(const _State& _nextState) {
            m_State = _nextState;
        }
    private:
        _State m_State;
    };
    StateData m_StateData;
};
