#pragma once

#include "AUIBasicEnumDef.h"
#include "AUIState.h"

#include <unordered_map>
#include <string>

ALICEUI_API extern const AUIState kAUINeutralWidgetState;

template<class T>
class AUIStateFeature
{
public:
    AUIStateFeature() {
        _default_feature();
    }
    virtual ~AUIStateFeature() = default;

public:
    struct TTransitionInfo
    {
        T fSSNotion;    // millisecond?
    };
    struct TStateInfo
    {
        size_t fIdHashKey = 0;
        T fSSNotion;
        std::unordered_map< AUIState, TTransitionInfo, AUIStateHasher> fTransitionFromMap;
    };


    const T& GetDefaultFeature() const {
        auto itr = m_mapState2Info.find(kAUINeutralWidgetState);
        AUIAssert(itr != m_mapState2Info.end());
        return itr->second.fSSNotion;
    }
    T& _default_feature() {
        return m_mapState2Info[kAUINeutralWidgetState].fSSNotion;
    }
    T& _state_feature(const AUIState& state)
    {
        auto& _sinfo = m_mapState2Info[state];
        return _sinfo.fSSNotion;
    }
    void _set_state_name(const AUIState& state, const std::wstring& name)
    {
        m_mapName2State[name] = state;
    }
    T* _transition_feature(const std::wstring& from_state_name, const std::wstring& to_state_name)
    {
        auto from_state = _find_state_by_name(from_state_name);
        auto to_state = _find_state_by_name(to_state_name);

        if (!from_state || !to_state)
            return nullptr;

        auto& _sinfo = m_mapState2Info[*to_state];
        return &(_sinfo.fTransitionFromMap[*from_state].fSSNotion);
    }




    void GetTransitionFeature(const TTransitionInfo*& pTransition, const T*& pToStateNotion, const AUIState& from_state, const AUIState& to_state) const
    {
        auto itr = m_mapState2Info.find(to_state);
        _find_state_from_map(itr, m_mapState2Info, to_state);
        if (itr == m_mapState2Info.end())
        {
            itr = m_mapState2Info.find(kAUINeutralWidgetState);
            AUIAssert(itr != m_mapState2Info.end());
        }


        auto& _info = itr->second;
        pToStateNotion = &_info.fSSNotion;
        auto& mapFrom = _info.fTransitionFromMap;
        auto itrFrom = mapFrom.end();

        _find_state_from_map(itrFrom, mapFrom, from_state);
        if (itrFrom == mapFrom.end())
            pTransition = nullptr;
        else
            pTransition = &itrFrom->second;
    }



private:
    AUIState * _find_state_by_name(const std::wstring& name)
    {
        auto itr = m_mapName2State.find(name);
        if (itr == m_mapName2State.end())
            return nullptr;
        return &itr->second;
    }

    template <class MAP, class Titer>
    void _find_state_from_map(Titer& itrRes, MAP& _map, const AUIState& _state) const
    {
        size_t _fc = 1;
        size_t _p = (std::numeric_limits<int>::max)();
        itrRes = _map.end();
        for (auto itr = _map.begin(); itr != _map.end(); itr++)
        {
            auto _check_state = itr->first;
            auto _cfc = _check_state.CheckState(_state);
            if (_cfc < _fc)
                continue;

            size_t _cp = _check_state.StatePriority();
            if (_p < _cp)
                continue;
            _p = _cp;
            _fc = _cfc;
            itrRes = itr;
        }
    }

    std::unordered_map<std::wstring, AUIState> m_mapName2State;
    std::unordered_map<AUIState, TStateInfo, AUIStateHasher> m_mapState2Info;
};

template <class T>
class AUIStateFeatureUpdator
{
public:
    AUIStateFeatureUpdator(std::shared_ptr<const AUIStateFeature<T>> pStyle) :m_pStateFeature(pStyle)
    {
        m_prevState.SetVisible(false);  // To enforce inital update
    }
    virtual ~AUIStateFeatureUpdator() = default;
    const T* GetUpdateFeature(const AUIState& state)
    {
        if (!m_pStateFeature)
            return nullptr;
        if (state == m_prevState)
            return nullptr;
        const typename AUIStateFeature<T>::TTransitionInfo* pTransition;
        const T* pNotion;
        m_pStateFeature->GetTransitionFeature(pTransition, pNotion, m_prevState, state);
        m_prevState = state;
        if (pTransition)
        {

        }
        if (pNotion)
            return pNotion;
        return nullptr;
    }
    std::shared_ptr<const AUIStateFeature<T>> GetStateFeature() const {
        return m_pStateFeature;
    }
private:
    std::shared_ptr<const AUIStateFeature<T>> m_pStateFeature;
    AUIState m_prevState;
};



