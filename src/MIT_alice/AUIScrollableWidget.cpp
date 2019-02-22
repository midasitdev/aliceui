#include "pch.h"
#include "AUIScrollableWidget.h"
#include "AUIWidgetManager.h"
#include "AUIScrollableContentWidget.h"
#include "AUIApplication.h"
#include "AUIWidgetTreeHelper.h"
#include "AUIScrollableBarWidget.h"

namespace {
    constexpr SkScalar DefaultScrollOffset = 30.0f;
    constexpr SkScalar DefaultWidth = 100.0f;
    constexpr SkScalar DefaultHeight = 100.0f;
}

AUIScrollableWidget::AUIScrollableWidget()
    : m_pContent( std::make_shared< AUIScrollableContentWidget >() )
    , m_pScrollBar( std::make_shared< AUIScrollableBarWidget >() )
    , m_eScrollBarPolicy( SBP_Show )
    , m_fScrollPos( 0.0f )
    , m_fScrollOffset( DefaultScrollOffset )
    , m_bHorizontal( false )
    , m_bPendingScrolllToBottom( false )
    , m_bPendingScrollToTop( false )
{
    Connect( m_pContent->ScrollSignal, this, &AUIScrollableWidget::OnContentScroll );
    Connect( m_pScrollBar->ThumbScrollSignal, this, &AUIScrollableWidget::OnThumbScroll );

    AddChild( m_pContent );
    AddChild( m_pScrollBar );

    SetSizePolicy(AUISizePolicy::kParent, AUISizePolicy::kParent);
    SetDefaultSize( DefaultWidth, DefaultHeight );
}

AUIScrollableWidget::~AUIScrollableWidget()
{

}

void AUIScrollableWidget::AddSubWidgetAt( const std::shared_ptr< AUIWidget >& widget, const size_t pos )
{
    m_pContent->AddSubWidgetAt( widget, pos );
}

void AUIScrollableWidget::DelSubWidget( const std::shared_ptr< AUIWidget >& widget )
{
    m_pContent->DelSubWidget( widget );
}

void AUIScrollableWidget::PopSubWidget()
{
    m_pContent->PopSubWidget();
}

void AUIScrollableWidget::ClearSubWidget()
{
    m_pContent->ClearSubWidget();
}

std::shared_ptr< AUIWidget > AUIScrollableWidget::FindSubWidget( size_t pos )
{
    return m_pContent->FindSubWidget( pos );
}

size_t AUIScrollableWidget::SubWidgetCount() const 
{
    return m_pContent->SubWidgetCount();
}

void AUIScrollableWidget::OnUpdateChildPosition()
{
    const auto startX = GetPaddingLeft();
    const auto startY = GetPaddingTop();

    const auto arrChildren = AUIApplication::Instance().GetWidgetTree().GetChildren( this );
    for ( auto& child : arrChildren )
    {
        // Except scollbar
        if ( child.get() == m_pScrollBar.get() )
            continue;
        child->SetPosition( startX + child->GetMarginLeft() + GetScrollX(), startY + child->GetMarginTop() + GetScrollY() );

        // Update Child's children
        AUIWidget::CallOnUpdateChildPosition( child );
    }

    //SuperClass::OnUpdateChildPosition();
    //const auto arrChildren = MAUIApplication::Instance().GetWidgetTree().GetChildren( this );

    //const auto startX = GetPaddingLeft();
    //const auto startY = GetPaddingTop();


    //for ( auto& child : arrChildren )
    //{
    //    child->SetPosition( startX + child->GetMarginLeft(), startY + child->GetMarginTop() );

    //    // Update Child's children
    //    AUIWidget::CallOnUpdateChildPosition( child );
    //}
}

void AUIScrollableWidget::OnSetDefaultSize(const AUIScalar2& size)
{
    m_pContent->SetDefaultSize(size);
}

void AUIScrollableWidget::OnContentScroll( AUIScrollableContentWidget* const pWidget, float delta )
{
    if ( 0.0f < delta )
    {
        if ((delta == std::numeric_limits<float>::max()))
        {
            // TopMost
            m_fScrollPos = 0.0f;
        }
        else
        {
            m_fScrollPos += m_fScrollOffset * delta;
            if (0.0f < m_fScrollPos)
                m_fScrollPos = 0.0f;
        }
        SetScrollY(m_fScrollPos);
    }
    else if ( 0.0f > delta )
    {
        if ((delta == std::numeric_limits<float>::lowest()))
        {
            m_fScrollPos = (std::min)(0.0f, -(m_pContent->GetHeight() - this->GetHeight()));
        }
        else
        {
            AUIAssert(0.0f <= (-delta));
            m_fScrollPos -= m_fScrollOffset * (-delta);
            if (-(m_pContent->GetHeight() - this->GetHeight()) > m_fScrollPos)
                m_fScrollPos = (std::min)(0.0f, -(m_pContent->GetHeight() - this->GetHeight()));
        }
        SetScrollY(m_fScrollPos);
    }

    m_pScrollBar->SetScrollPos( m_fScrollPos );
    m_pScrollBar->Invalidate();

    UpdateChildPosition();
    Invalidate();
}

void AUIScrollableWidget::ScrollToTop()
{
    m_bPendingScrollToTop = true;
    UpdateSize();
}

void AUIScrollableWidget::ScrollToBottom()
{
    m_bPendingScrolllToBottom = true;
    UpdateSize();
}

void AUIScrollableWidget::OnDraw( SkCanvas * const canvas )
{
    SuperClass::OnDraw( canvas );

}

void AUIScrollableWidget::OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{

    const auto spWidth = GetSizePolicyWidth();
    const auto spHeight = GetSizePolicyHeight();

    const auto defaultSize = GetDefaultSize();


    auto targetWidth = defaultSize.fX;
    auto targetHeight = defaultSize.fY;

    auto childWidthSpec = AUIMeasureSpec::kUnspecified;
    auto childHeightSpec = AUIMeasureSpec::kUnspecified;

    auto needWidthFitting = false;
    auto needHeightFitting = false;

    auto needWidthFitParent = false;
    auto needHeightFitParent = false;

    if ( widthSpec == AUIMeasureSpec::kExactly )
    {
        childWidthSpec = AUIMeasureSpec::kAtMost;
        targetWidth = width;
    }
    else if ( widthSpec == AUIMeasureSpec::kAtMost )
    {
        childWidthSpec = AUIMeasureSpec::kAtMost;
        targetWidth = width;
        if ( spWidth == AUISizePolicy::kContent )
            needWidthFitting = true;
    }
    else if ( widthSpec == AUIMeasureSpec::kUnspecified )
    {
        if ( spWidth == AUISizePolicy::kParent )
        {
            childWidthSpec = AUIMeasureSpec::kExactly;
            targetWidth = width;
            needWidthFitParent = true;
        }
        else if ( spWidth == AUISizePolicy::kFixed )
        {
            childWidthSpec = AUIMeasureSpec::kExactly;
            targetWidth = ( std::min )( defaultSize.fX, width );
        }
        else if ( spWidth == AUISizePolicy::kContent )
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
            needWidthFitting = true;
        }
        else
        {
            AUIAssert( false );
        }
    }
    else
    {
        AUIAssert( false );
    }


    if ( heightSpec == AUIMeasureSpec::kExactly )
    {
        childHeightSpec = AUIMeasureSpec::kAtMost;
        targetHeight = height;
    }
    else if ( heightSpec == AUIMeasureSpec::kAtMost )
    {
        if ( spHeight == AUISizePolicy::kParent )
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = height;
            needHeightFitParent = true;
        }
        else if ( spHeight == AUISizePolicy::kFixed )
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = ( std::min )( defaultSize.fY, height );
        }
        else if ( spHeight == AUISizePolicy::kContent )
        {
            childHeightSpec = AUIMeasureSpec::kAtMost;
            targetHeight = height;
            needHeightFitting = true;
        }
        else
        {
            AUIAssert( false );
        }
    }
    else if ( heightSpec == AUIMeasureSpec::kUnspecified )
    {
        childHeightSpec = AUIMeasureSpec::kAtMost;
        targetHeight = defaultSize.fY;
        if ( spHeight == AUISizePolicy::kContent )
            needHeightFitting = true;
    }
    else
    {
        AUIAssert( false );
    }

    auto availableWidth = targetWidth - ( GetPaddingLeft() + GetPaddingRight() );
    auto availableHeight = targetHeight - ( GetPaddingTop() + GetPaddingBottom() );

    auto requiredWidth = 0.0f;
    auto requiredHeight = 0.0f;

    const auto& children = GetChildren();
    for ( auto itr = children.begin(); itr != children.end(); itr++ )
    {
        auto pChildWidget = ( *itr ).get();

        // Except scrollbar widget
        if ( pChildWidget == m_pScrollBar.get() )
            continue;

        const auto targetChildWidth = availableWidth - ( pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight() );
        const auto targetChildHeight = availableHeight - ( pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom() );

        OnCallMeasureAndUpdateSize(pChildWidget, targetChildWidth, childWidthSpec, targetChildHeight, childHeightSpec);

        const auto childPos = pChildWidget->GetPosition();
        const auto childSize = pChildWidget->GetMeasureSize();

        requiredWidth = ( std::max )( requiredWidth, childPos.fX + childSize.fX + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight() );
        requiredHeight = ( std::max )( requiredHeight, childPos.fY + childSize.fY + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom() );
    }

    if ( widthSpec == AUIMeasureSpec::kAtMost )
        requiredWidth = ( std::min )( requiredWidth, width );
    if ( heightSpec == AUIMeasureSpec::kAtMost )
        requiredHeight = ( std::min )( requiredHeight, height );

    if ( needWidthFitting )
        targetWidth = requiredWidth;
    if ( needHeightFitting )
        targetHeight = requiredHeight;

    SetMeasureSize(targetWidth, targetHeight);

    OnCallMeasureAndUpdateSize( m_pScrollBar.get(), targetWidth, AUIMeasureSpec::kExactly, targetHeight, AUIMeasureSpec::kExactly);
}

void AUIScrollableWidget::SetShowThumbOnHit( bool show )
{
    AUIAssert( m_pScrollBar );
    m_pScrollBar->SetShowThumbOnHit( show );
}

bool AUIScrollableWidget::IsShowThumbOnHit() const
{
    AUIAssert( m_pScrollBar );
    return m_pScrollBar->IsShowThumbOnHit();
}

void AUIScrollableWidget::OnAfterMeasureSize(SkScalar width, SkScalar height)
{
    if ( m_bPendingScrollToTop )
        this->OnContentScroll( m_pContent.get(), std::numeric_limits<float>::max());
    else if ( m_bPendingScrolllToBottom )
        this->OnContentScroll( m_pContent.get(), std::numeric_limits<float>::lowest());
    m_bPendingScrolllToBottom = false;
    m_bPendingScrollToTop = false;

    m_pScrollBar->SetContentHeight( m_pContent->GetHeight() );
    m_pScrollBar->Invalidate();
}

void AUIScrollableWidget::OnThumbScroll( const SkScalar& val )
{
    //AUIDebugPrint( "Thumb Scroll Value : %f | Scroll Pos : %f\n", val, GetScrollY() );
    m_fScrollPos -= m_pContent->GetHeight() * val;
    if ( 0.0f < m_fScrollPos )
        m_fScrollPos = 0.0f;
    if ( -( m_pContent->GetHeight() - this->GetHeight() ) > m_fScrollPos )
        m_fScrollPos = ( std::min )( 0.0f, -( m_pContent->GetHeight() - this->GetHeight() ) );

    SetScrollY( m_fScrollPos );
    m_pScrollBar->SetScrollPos( m_fScrollPos );
    m_pScrollBar->Invalidate();

    UpdateChildPosition();
    Invalidate();
}

