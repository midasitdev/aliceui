#include "pch.h"
#include "AUIStateDrawable.h"

AUIStateDrawable::AUIStateDrawable()
    : m_bRefreshDraw(true)
{

}

AUIStateDrawable::~AUIStateDrawable()
{

}

void AUIStateDrawable::OnDraw( SkCanvas* const canvas )
{
    m_bRefreshDraw = false;
    const auto padding = GetDrawPadding();
    //canvas->translate( padding.left(), padding.top() );
    const auto bound = GetDrawBound();
    canvas->clipRect( SkRect::MakeLTRB( bound.left() + padding.left(), bound.top() + padding.top(), bound.right() - padding.right(), bound.bottom() - padding.bottom() ) );
    if ( auto pDrawable = GetCurDrawable() )
    {
        pDrawable->Draw( canvas );
    }
}

void AUIStateDrawable::OnChangeDrawUIState()
{
    m_pCurDrawable = nullptr;

    const auto& state = GetDrawUIState();

    if ( auto pDrawable = FindFromTrueState( AUIState::kDefault ) )
    {
        m_pCurDrawable = pDrawable;
    }
    else if ( auto pDrawable = FindFromFalseState( AUIState::kDefault ) )
    {
        m_pCurDrawable = pDrawable;
    }

    // Enabled
    if ( state.IsDisabled() == false )
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kDisabled ) )
            m_pCurDrawable = pDrawable;
    }

    // Focusable
    if ( state.IsFocusable() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kFocusable ) )
            m_pCurDrawable = pDrawable;

        // Focused
        if ( state.IsFocused() )
        {
            if ( auto pDrawable = FindFromTrueState( AUIState::kFocused ) )
                m_pCurDrawable = pDrawable;
        }
        else
        {
            if ( auto pDrawable = FindFromFalseState( AUIState::kFocused ) )
                m_pCurDrawable = pDrawable;
        }
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kFocusable ) )
            m_pCurDrawable = pDrawable;
    }

    // Checkable
    if ( state.IsCheckable() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kCheckable ) )
            m_pCurDrawable = pDrawable;

        // Checked
        if ( state.IsChecked() )
        {
            // Indeterminate
            if (state.IsCheckedIndeterminate())
            {
                if (auto pDrawable = FindFromTrueState(AUIState::kCheckIndeterminate))
                {
                    m_pCurDrawable = pDrawable;
                }
                else
                {
                    if (auto pDrawable = FindFromTrueState(AUIState::kChecked))
                        m_pCurDrawable = pDrawable;
                }
            }
            else
            {
                if (auto pDrawable = FindFromTrueState(AUIState::kChecked))
                    m_pCurDrawable = pDrawable;
            }
        }
        else
        {
            if ( auto pDrawable = FindFromFalseState( AUIState::kChecked ) )
                m_pCurDrawable = pDrawable;
        }
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kCheckable ) )
            m_pCurDrawable = pDrawable;
    }

    // Selectable
    if ( state.IsSelectable() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kSelectable ) )
            m_pCurDrawable = pDrawable;

        // Selected
        if ( state.IsSelected() )
        {
            if ( auto pDrawable = FindFromTrueState( AUIState::kSelected ) )
                m_pCurDrawable = pDrawable;
        }
        else
        {
            if ( auto pDrawable = FindFromFalseState( AUIState::kSelected ) )
                m_pCurDrawable = pDrawable;
        }
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kSelectable ) )
            m_pCurDrawable = pDrawable;
    }


    // Draggable
    if ( state.IsDraggable() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kDraggable ) )
            m_pCurDrawable = pDrawable;

        // Dragging
        if ( state.IsDragging() )
        {
            if ( auto pDrawable = FindFromTrueState( AUIState::kDragging ) )
                m_pCurDrawable = pDrawable;
        }
        else
        {
            if ( auto pDrawable = FindFromFalseState( AUIState::kDragging ) )
                m_pCurDrawable = pDrawable;
        }
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kDraggable ) )
            m_pCurDrawable = pDrawable;
    }

    // Hovered
    if ( state.IsMouseHovered() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kMouseHovered ) )
            m_pCurDrawable = pDrawable;
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kMouseHovered ) )
            m_pCurDrawable = pDrawable;
    }

    // Pressed
    if ( state.IsPressed() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kPressed ) )
            m_pCurDrawable = pDrawable;
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kPressed ) )
            m_pCurDrawable = pDrawable;
    }

    // Left Down
    if ( state.IsMouseLDown() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kMouseLDown ) )
            m_pCurDrawable = pDrawable;
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kMouseLDown ) )
            m_pCurDrawable = pDrawable;
    }

    // Middle Down
    if ( state.IsMouseMDown() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kMouseMDown ) )
            m_pCurDrawable = pDrawable;
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kMouseMDown ) )
            m_pCurDrawable = pDrawable;
    }

    // Right Down
    if ( state.IsMouseRDown() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kMouseRDown ) )
            m_pCurDrawable = pDrawable;
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kMouseRDown ) )
            m_pCurDrawable = pDrawable;
    }

    // Freezed
    if ( state.IsFreezed() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kFreezed ) )
            m_pCurDrawable = pDrawable;
    }
    else
    {
        if ( auto pDrawable = FindFromFalseState( AUIState::kFreezed ) )
            m_pCurDrawable = pDrawable;
    }

    // Disabled is topmost!
    if ( state.IsDisabled() )
    {
        if ( auto pDrawable = FindFromTrueState( AUIState::kDisabled ) )
            m_pCurDrawable = pDrawable;
    }

    if (m_pCurDrawable)
        m_pCurDrawable->SetDrawUIState(state);

    m_bRefreshDraw = true;
}

void AUIStateDrawable::SetTrueStateDrawable( AUIState::Index idx, const std::shared_ptr< AUIDrawable >& pDrawable )
{
    AUIAssert( idx != AUIState::kCreated );
	AUIAssert(pDrawable);
    m_mapTrueState2Drawable[idx] = pDrawable;
}

void AUIStateDrawable::SetFalseStateDrawable( AUIState::Index idx, const std::shared_ptr< AUIDrawable >& pDrawable )
{
    AUIAssert( idx != AUIState::kCreated );
	AUIAssert(pDrawable);
    m_mapFalseState2Drawable[idx] = pDrawable;
}

std::shared_ptr< AUIDrawable > AUIStateDrawable::FindFromTrueState( AUIState::Index idx ) const
{
    const auto found = m_mapTrueState2Drawable.find( idx );
    if ( found == m_mapTrueState2Drawable.end() )
        return nullptr;
    return found->second;
}

std::shared_ptr< AUIDrawable > AUIStateDrawable::FindFromFalseState( AUIState::Index idx ) const
{
    const auto found = m_mapFalseState2Drawable.find( idx );
    if ( found == m_mapFalseState2Drawable.end() )
        return nullptr;
    return found->second;
}

void AUIStateDrawable::OnSetDrawBound()
{
    const auto bound = GetDrawBound();
    const auto padding = GetDrawPadding();
    const auto subbound = SkRect::MakeLTRB( bound.left() + padding.left(), bound.top() + padding.top(), bound.right() - padding.right(), bound.bottom() - padding.bottom() );


    for ( auto& drawable : m_mapTrueState2Drawable )
    {
        drawable.second->SetDrawBound( subbound );
    }
    for ( auto& drawable : m_mapFalseState2Drawable )
    {
        drawable.second->SetDrawBound( subbound );
    }
}

void AUIStateDrawable::OnSetDrawPadding()
{
    //for ( auto& drawable : m_mapTrueState2Drawable )
    //{
    //    drawable.second->SetDrawPadding( GetDrawPadding() );
    //}
    //for ( auto& drawable : m_mapFalseState2Drawable )
    //{
    //    drawable.second->SetDrawPadding( GetDrawPadding() );
    //}
}

void AUIStateDrawable::OnChangeLevelIndex()
{
    for ( auto& drawable : m_mapTrueState2Drawable )
    {
        drawable.second->SetLevelIndex( GetLevelIndex() );
    }
    for ( auto& drawable : m_mapFalseState2Drawable )
    {
        drawable.second->SetLevelIndex( GetLevelIndex() );
    }

}
