#pragma once


#include "AUIComboAdapter.h"
#include "AUITextWidget.h"

template< typename T >
class AUIArrayAdapter : public AUIComboAdapter
{
public:
    AUIArrayAdapter() : m_bSendDataChangeSignal(true) { }
    virtual ~AUIArrayAdapter() { }


    //////////////////////////////////////////////////////////////////////////
    // Implements
public:
    virtual size_t GetCount() const override
    {
        return m_arrData.size();
    }
    virtual std::any GetItem(const size_t pos) const override
    {
        if (IsValidPos(pos) == false)
        {
            AUIAssert(!"Invalid position");
            return std::any();
        }
        return std::make_any< T >(m_arrData[pos]);
    }
    virtual std::shared_ptr< AUIWidget > GetWidget(const size_t pos, const std::shared_ptr< AUIWidget >& pOldWidget, const std::shared_ptr< AUIWidget >& pParentWidget) override
    {
        // We use LabelWidget for default
        auto pWidget = std::shared_ptr< AUITextWidget >();
        if (pOldWidget == nullptr)
        {
            pWidget = std::make_shared< AUITextWidget >();
        }
        else
        {
            if (pOldWidget->IsKindOf< AUITextWidget >())
                pWidget = std::static_pointer_cast<AUITextWidget>(pOldWidget);
        }
        AUIAssert(pWidget);
        AUIAssert(IsValidPos(pos));

        // If error, override GetWidget() or implement std::to_wstring( T val )
        AUIAssert(!"Implement this class");

        return pWidget;
    }


    //////////////////////////////////////////////////////////////////////////
    // Operation
public:
    void Add(const T& data)
    {
        m_arrData.emplace_back(data);

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }
    void Clear()
    {
        m_arrData.clear();

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }
    void Insert(const size_t pos, const T& data)
    {
        auto itr = m_arrData.begin();
        std::advance(itr, pos);
        m_arrData.insert(itr, data);

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }
    void Remove(const size_t pos)
    {
        auto itr = m_arrData.begin();
        std::advance(itr, pos);
        m_arrData.erase(itr);

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }


    //////////////////////////////////////////////////////////////////////////
    // Data change signal
public:
    void SetSendDataChangeSignal(bool send) { m_bSendDataChangeSignal = send; }
    bool IsSendDataChangeSignal() const { return m_bSendDataChangeSignal; }
private:
    bool m_bSendDataChangeSignal;


    //////////////////////////////////////////////////////////////////////////
    // Data
protected:
    std::vector< T > m_arrData;
};


template<>
class AUIArrayAdapter< std::wstring > : public AUIComboAdapter
{
public:
    AUIArrayAdapter() {}
    virtual ~AUIArrayAdapter() { }


    //////////////////////////////////////////////////////////////////////////
    // Implements
public:
    virtual size_t GetCount() const override
    {
        return m_arrData.size();
    }
    virtual std::any GetItem(const size_t pos) const override
    {
        if (IsValidPos(pos) == false)
        {
            AUIAssert(!"Invalid position");
            return std::any();
        }
        return std::make_any< std::wstring >(m_arrData[pos]);
    }
    virtual std::shared_ptr< AUIWidget > GetWidget(const size_t pos, const std::shared_ptr< AUIWidget >& pOldWidget, const std::shared_ptr< AUIWidget >& pParentWidget) override
    {
        // We use LabelWidget for default
        auto pWidget = std::shared_ptr< AUITextWidget >();
        if (pOldWidget == nullptr)
        {
            pWidget = std::make_shared< AUITextWidget >();
            pWidget->SetCaptionVertAlign(AUITextVertAlign::kCenter);
            pWidget->SetPaddingLTRB(7.0f, 2.0f, 7.0f, 2.0f);
        }
        else
        {
            if (pOldWidget->IsKindOf< AUITextWidget >())
                pWidget = std::static_pointer_cast<AUITextWidget>(pOldWidget);
            else {
                pWidget = std::make_shared< AUITextWidget >();
                pWidget->SetCaptionVertAlign(AUITextVertAlign::kCenter);
                pWidget->SetPaddingLTRB(7.0f, 2.0f, 7.0f, 2.0f);
            }
        }
        AUIAssert(pWidget);
        AUIAssert(IsValidPos(pos));

        const auto str = std::wstring(m_arrData[pos]);

        pWidget->SetCaption(str);

        return pWidget;
    }


    //////////////////////////////////////////////////////////////////////////
    // Operation
public:
    void Add(std::wstring data)
    {
        m_arrData.emplace_back(data);

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }
    void Clear()
    {
        m_arrData.clear();

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }
    void Insert(std::wstring data, size_t pos)
    {
        auto itr = m_arrData.begin();
        std::advance(itr, pos);
        m_arrData.insert(itr, data);

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }
    void Remove(size_t pos)
    {
        auto itr = m_arrData.begin();
        std::advance(itr, pos);
        m_arrData.erase(itr);

        if (IsSendDataChangeSignal())
            DataChangedSignal.Send(this);
    }


    //////////////////////////////////////////////////////////////////////////
    // Data change signal
public:
    void SetSendDataChangeSignal(bool send) { m_bSendDataChangeSignal = send; }
    bool IsSendDataChangeSignal() const { return m_bSendDataChangeSignal; }
private:
    bool m_bSendDataChangeSignal;


    //////////////////////////////////////////////////////////////////////////
    // Data
protected:
    std::vector< std::wstring > m_arrData;
};
