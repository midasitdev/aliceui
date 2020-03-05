#include "pch.h"
#include "AUITooltipWidget.h"
#include "AUITextWidget.h"
#include "AUITooltip.h"

AUITooltipWidget::AUITooltipWidget()
{

}

AUITooltipWidget::~AUITooltipWidget()
{

}

void AUITooltipWidget::SetData( const std::shared_ptr< AUITooltip >& pTooltip )
{
    m_pTooltip = pTooltip;

    ClearSubWidget();
    if ( nullptr == m_pTooltip )
    {
        return;
    }
    auto pText = std::make_shared< AUITextWidget >( m_pTooltip->GetMessage() );
    pText->SetSizePolicyWidth( AUISizePolicy::kContent );
    pText->SetSizePolicyHeight( AUISizePolicy::kContent );
    pText->SetCaptionColor(SkColorSetRGB(17, 17, 17));
    //pText->SetUseMultiline( true );
    pText->SetPaddingLTRB( 3, 3, 3, 3 );
    AddSubWidget( pText );
}
