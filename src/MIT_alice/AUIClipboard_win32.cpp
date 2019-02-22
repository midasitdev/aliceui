#include "pch.h"
#include "AUIClipboard_win32.h"

class AutoClipboard final
{
public:
    AutoClipboard()
        : m_bValid( false )
    {
        if (!::OpenClipboard(NULL))
            throw std::runtime_error("Failed to open clipboard");
        else
            m_bValid = true;
    }
    ~AutoClipboard()
    {
        if (IsValid())
            ::CloseClipboard();
    }
    AutoClipboard(const AutoClipboard&) = delete;

    //////////////////////////////////////////////////////////////////////////
    // Plain Text
public:
    std::wstring GetText() const
    {
        AUIAssert( IsValid() );

        const auto hData = GetClipboardData( CF_UNICODETEXT );
        if ( hData == nullptr )
            return std::wstring();

        AUIAssert( hData );

        std::wstring text;
        do 
        {
            const auto pText = static_cast< wchar_t* >( GlobalLock( hData ) );
            if ( pText == nullptr )
                break;

            text = std::wstring( pText );

            GlobalUnlock( hData );
        } while ( false );


        return text;
    }
    void SetText( const std::wstring& text )
    {
        AUIAssert( IsValid() );

        EmptyClipboard();
        if ( text.empty() )
            return;


        const auto hData = GlobalAlloc( GMEM_MOVEABLE, ( text.size() + 1 ) * sizeof( wchar_t ) );
        if ( hData == nullptr )
            return;

        auto pData = static_cast< wchar_t* >( GlobalLock( hData ) );

#       pragma warning(push)
#       pragma warning(disable: 4996)
        std::wcsncpy(pData, text.data(), text.size());
#       pragma warning(pop)

        pData[text.size()] = L'\0';

        GlobalUnlock( hData );

        SetClipboardData( CF_UNICODETEXT, hData );
    }


    //////////////////////////////////////////////////////////////////////////
    // Valid
public:
    bool IsValid() const { return m_bValid; }
private:
    bool m_bValid;
};

std::wstring AUIClipboard::Impl::GetText() const
{
    AutoClipboard clipboard;
    return clipboard.GetText();
}

void AUIClipboard::Impl::SetText( const std::wstring& text )
{
    AutoClipboard clipboard;
    clipboard.SetText( text );
}
