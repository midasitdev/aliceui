#include "pch.h"
#include "AUINinePatchDrawable.h"
#include "AUIGalleria.h"

AUINinePatchDrawable::AUINinePatchDrawable()
{

}

AUINinePatchDrawable::AUINinePatchDrawable( const AUINinePatch& ninepatch )
    : m_NinePatch( ninepatch )
{

}

AUINinePatchDrawable::~AUINinePatchDrawable()
{

}

void AUINinePatchDrawable::OnDraw( SkCanvas* const canvas )
{
    m_NinePatch.Draw( canvas, GetDrawBound() );
}

std::shared_ptr<AUINinePatchDrawable > AUINinePatchDrawable::CreateFromResourcePath( const std::wstring& path )
{
    auto pImage = AUIGalleria::Make().GetFromResource( path );
    if ( nullptr == pImage)
        return std::make_shared< AUINinePatchDrawable >();
    return std::make_shared< AUINinePatchDrawable >(AUINinePatch::MakeFromNinePatchImage(pImage));
}
