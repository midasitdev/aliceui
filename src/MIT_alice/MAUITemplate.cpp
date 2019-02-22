#include "pch.h"
#include "MAUITemplate.h"

using namespace mit::alice;

MAUITemplate::MAUITemplate()
{

}

MAUITemplate::~MAUITemplate()
{

}

std::shared_ptr< AUIWidget > mit::alice::MAUITemplate::CreateWidget()
{
    return OnCreateWidget();
}

void mit::alice::MAUITemplate::UpdateParam( AUIWidget* const pRoot, const MAUITemplParam& param )
{
    OnUpdateParam( pRoot, param );
}

//void mit::alice::MAUITemplate::UpdateInput( AUIWidget* const pRoot, const std::vector< MAUITemplInput >& arrInput )
//{
//    OnUpdateInput( pRoot, arrInput );
//}

void mit::alice::MAUITemplate::UpdateInsert( AUIWidget* const pRoot, const MAUITemplInput& input )
{
    OnUpdateInsert( pRoot, input );
}

void mit::alice::MAUITemplate::UpdateRemove( AUIWidget* const pRoot, const MAUITemplInput& input )
{
    OnUpdateRemove( pRoot, input );
}

void mit::alice::MAUITemplate::UpdateClear( AUIWidget* const pRoot, const MAUITemplInput& input )
{
    OnUpdateClear( pRoot, input );
}
