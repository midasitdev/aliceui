#include "pch.h"
#include "AUIRecyclerLinearLayoutManager.h"
#include "AUIRecyclerWidget.h"
#include "AUIApplication.h"

AUIRecyclerLinearLayoutManager::AUIRecyclerLinearLayoutManager()
    : m_bHorizontal( false )
{

}

AUIRecyclerLinearLayoutManager::~AUIRecyclerLinearLayoutManager()
{

}

void AUIRecyclerLinearLayoutManager::OnMeasureSize( SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec)
{
    // NOTE : Base code is in AUILinearLayoutWidget
    auto pBase = GetRecyclerWidget();

    const auto isHorizontal = IsHorizontal();

    const auto spWidth = pBase->GetSizePolicyWidth();
    const auto spHeight = pBase->GetSizePolicyHeight();

    const auto defaultSize = pBase->GetDefaultSize();


    auto targetWidth = defaultSize.fX;
    auto targetHeight = defaultSize.fY;

    auto childWidthSpec = AUIMeasureSpec::kUnspecified;
    auto childHeightSpec = AUIMeasureSpec::kUnspecified;

    auto needWidthFitting = false;
    auto needHeightFitting = false;

    auto needWidthFitParent = false;
    auto needHeightFitParent = false;

    if ( isHorizontal )
    {
        if ( widthSpec == AUIMeasureSpec::kExactly )
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = width;
        }
        else if ( widthSpec == AUIMeasureSpec::kAtMost )
        {
            if ( spWidth == AUISizePolicy::kParent )
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
                targetWidth = width;
                needWidthFitParent = true;
            }
            else if ( spWidth == AUISizePolicy::kFixed )
            {
                childWidthSpec = AUIMeasureSpec::kAtMost;
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
        else if ( widthSpec == AUIMeasureSpec::kUnspecified )
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = defaultSize.fX;
        }
        else
        {
            AUIAssert( false );
        }


        if ( heightSpec == AUIMeasureSpec::kExactly )
        {
            childHeightSpec = AUIMeasureSpec::kExactly;
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
                childHeightSpec = AUIMeasureSpec::kExactly;
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
        }
        else
        {
            AUIAssert( false );
        }
    }
    else
    {
        if ( widthSpec == AUIMeasureSpec::kExactly )
        {
            childWidthSpec = AUIMeasureSpec::kExactly;
            targetWidth = width;
        }
        else if ( widthSpec == AUIMeasureSpec::kAtMost )
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
        else if ( widthSpec == AUIMeasureSpec::kUnspecified )
        {
            childWidthSpec = AUIMeasureSpec::kAtMost;
            targetWidth = defaultSize.fX;
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
        }
        else
        {
            AUIAssert( false );
        }
    }

    auto availableWidth = targetWidth - ( pBase->GetPaddingLeft() + pBase->GetPaddingRight() );
    auto availableHeight = targetHeight - ( pBase->GetPaddingTop() + pBase->GetPaddingBottom() );

    auto requiredWidth = 0.0f;
    auto requiredHeight = 0.0f;
    auto requiredDepth = 0.0f;

    const auto& children = pBase->GetChildren();
    for ( auto itr = children.begin(); itr != children.end(); itr++ )
    {
        auto pChildWidget = ( *itr ).get();
        if ( pChildWidget->IsIgnored() )
            continue;

        const auto targetChildWidth = availableWidth - ( pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight() );
        const auto targetChildHeight = availableHeight - ( pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom() );

        AUIWidget::OnCallMeasureAndUpdateSize(pChildWidget, targetChildWidth, childWidthSpec, targetChildHeight, childHeightSpec);

        const auto childSize = pChildWidget->GetSize();
        if ( isHorizontal )
        {
            availableWidth -= ( childSize.fX + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight() );
            requiredHeight = ( std::max )( requiredHeight, childSize.fY + pBase->GetPaddingTop() + pBase->GetPaddingBottom() + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom() );
        }
        else
        {
            availableHeight -= ( childSize.fY + pChildWidget->GetMarginTop() + pChildWidget->GetMarginBottom() );
            requiredWidth = ( std::max )( requiredWidth, childSize.fX + pBase->GetPaddingLeft() + pBase->GetPaddingRight() + pChildWidget->GetMarginLeft() + pChildWidget->GetMarginRight() );
        }
    }

    if ( isHorizontal )
    {
        requiredWidth = targetWidth - availableWidth;
    }
    else
    {
        requiredHeight = targetHeight - availableHeight;
    }

    // Only none or one option
    AUIAssert( !( needWidthFitting && needWidthFitParent ) );
    AUIAssert( !( needHeightFitting && needHeightFitParent ) );

    if ( needWidthFitting )
    {
        targetWidth = requiredWidth;
    }
    else if ( needWidthFitParent )
    {
        targetWidth = width;
    }
    if ( needHeightFitting )
    {
        targetHeight = requiredHeight;
    }
    else if ( needHeightFitParent )
    {
        targetHeight = height;
    }

    pBase->SetMeasureSize(targetWidth, targetHeight);

}

void AUIRecyclerLinearLayoutManager::OnUpdateChildPosition()
{
    if ( IsHorizontal() )
        UpdateChild_Horizontal();
    else
        UpdateChild_Vertical();
}

void AUIRecyclerLinearLayoutManager::UpdateChild_Horizontal()
{
    // NOTE : Base code is in AUILinearLayoutWidget
    auto pBase = GetRecyclerWidget();

    const auto height = pBase->GetHeight();
    const auto startX = pBase->GetPaddingLeft();
    const auto startY = pBase->GetPaddingTop();
    const auto endY = height - pBase->GetPaddingBottom();


    const auto toParentLeft = pBase->GetPropGravityLeft();
    const auto toParentTop = pBase->GetPropGravityTop();
    const auto toParentRight = pBase->GetPropGravityRight();
    const auto toParentBottom = pBase->GetPropGravityBottom();
    const auto toParentCenterHorizontal = pBase->GetPropGravityCenterHorizontal();
    const auto toParentCenterVertical = pBase->GetPropGravityCenterVertical();
    const auto toParentCenter = pBase->GetPropGravityCenter();

    auto childPosX = startX;

    const auto arrChildren = pBase->GetChildren();

    if ( toParentRight )
    {
        SkScalar totalChildrenWidth = 0.0f;
        for ( auto idx = 0; idx < arrChildren.size(); idx++ )
        {
            totalChildrenWidth += arrChildren[idx]->GetMarginLeft() + arrChildren[idx]->GetWidth() + arrChildren[idx]->GetMarginRight();
        }
        childPosX = pBase->GetWidth() - pBase->GetPaddingLeft() - pBase->GetPaddingRight() - totalChildrenWidth;
    }

    for ( auto& child : arrChildren )
    {
        if ( child->IsIgnored() )
            continue;

        const auto toLeft = child->GetPropLayoutGravityLeft();
        const auto toTop = child->GetPropLayoutGravityTop();
        const auto toRight = child->GetPropLayoutGravityRight();
        const auto toBottom = child->GetPropLayoutGravityBottom();
        const auto toCenterHorizontal = child->GetPropLayoutGravityCenterHorizontal();
        const auto toCenterVertical = child->GetPropLayoutGravityCenterVertical();
        const auto toCenter = child->GetPropLayoutGravityCenter();

        childPosX += child->GetMarginLeft();

        auto childPosY = startY + child->GetMarginTop();

        if ( toLeft || toTop || toRight || toBottom || toCenterHorizontal || toCenterVertical || toCenter )
        {
            // Use child's option
            if ( toBottom )
            {
                childPosY = endY - child->GetHeight() - child->GetMarginBottom();
            }
            if ( toCenterVertical || toCenter )
            {
                childPosY = pBase->GetHeight() * 0.5f - child->GetHeight() * 0.5f;
            }
        }
        else
        {
            // Use parent's option
            if ( toParentBottom )
            {
                childPosY = endY - child->GetHeight() - child->GetMarginBottom();
            }
            if ( toParentCenterVertical || toParentCenter )
            {
                childPosY = pBase->GetHeight() * 0.5f - child->GetHeight() * 0.5f;
            }
        }

        // Set Child Position
        child->SetPosition( childPosX + pBase->GetScrollX(), childPosY + pBase->GetScrollY() );

        // Update Child's children
        AUIWidget::CallOnUpdateChildPosition( child );

        childPosX += child->GetWidth() + child->GetMarginRight();
    }

}

void AUIRecyclerLinearLayoutManager::UpdateChild_Vertical()
{
    // NOTE : Base code is in AUILinearLayoutWidget
    auto pBase = GetRecyclerWidget();

    const auto width = pBase->GetWidth();
    const auto startX = pBase->GetPaddingLeft();
    const auto endX = width - pBase->GetPaddingRight();
    const auto startY = pBase->GetPaddingTop();

    const auto toParentLeft = pBase->GetPropGravityLeft();
    const auto toParentTop = pBase->GetPropGravityTop();
    const auto toParentRight = pBase->GetPropGravityRight();
    const auto toParentBottom = pBase->GetPropGravityBottom();
    const auto toParentCenterHorizontal = pBase->GetPropGravityCenterHorizontal();
    const auto toParentCenterVertical = pBase->GetPropGravityCenterVertical();
    const auto toParentCenter = pBase->GetPropGravityCenter();

    auto childPosY = startY;

    const auto arrChildren = pBase->GetChildren();



    if ( toParentBottom )
    {
        SkScalar totalChildrenHeight = 0.0f;
        for ( auto idx = 0; idx < arrChildren.size(); idx++ )
        {
            totalChildrenHeight += arrChildren[idx]->GetMarginTop() + arrChildren[idx]->GetHeight() + arrChildren[idx]->GetMarginBottom();
        }
        childPosY = pBase->GetHeight() - pBase->GetPaddingTop() - pBase->GetPaddingBottom() - totalChildrenHeight;
    }


    for ( auto& child : arrChildren )
    {
        if ( child->IsIgnored() )
            continue;

        const auto toLeft = child->GetPropLayoutGravityLeft();
        const auto toTop = child->GetPropLayoutGravityTop();
        const auto toRight = child->GetPropLayoutGravityRight();
        const auto toBottom = child->GetPropLayoutGravityBottom();
        const auto toCenterHorizontal = child->GetPropLayoutGravityCenterHorizontal();
        const auto toCenterVertical = child->GetPropLayoutGravityCenterVertical();
        const auto toCenter = child->GetPropLayoutGravityCenter();


        childPosY += child->GetMarginTop();

        auto childPosX = startX + child->GetMarginLeft();

        if ( toLeft || toTop || toRight || toBottom || toCenterHorizontal || toCenterVertical || toCenter )
        {
            // Use child's option
            if ( toRight )
            {
                childPosX = endX - child->GetWidth() - child->GetMarginRight();
            }
            if ( toCenterHorizontal || toCenter )
            {
                childPosX = pBase->GetWidth() * 0.5f - child->GetWidth() * 0.5f;
            }
        }
        else
        {
            // Use parent's option
            if ( toParentRight )
            {
                childPosX = endX - child->GetWidth() - child->GetMarginRight();
            }
            if ( toParentCenterHorizontal || toParentCenter )
            {
                childPosX = pBase->GetWidth() * 0.5f - child->GetWidth() * 0.5f;
            }
        }

        // Set Child Position
        child->SetPosition( childPosX + pBase->GetScrollX(), childPosY + pBase->GetScrollY() );

        // Update Child's children
        AUIWidget::CallOnUpdateChildPosition( child );

        childPosY += child->GetHeight() + child->GetMarginBottom();
    }

}
