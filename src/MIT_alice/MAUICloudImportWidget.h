#pragma once

#include "AUILinearLayoutWidget.h"

class AUIImageWidget;
class AUITextWidget;
namespace mit::alice
{
    class ALICEUI_API MAUICloudImportWidget : public AUILinearLayoutWidget
    {
    public:
        MAUICloudImportWidget();
        virtual ~MAUICloudImportWidget();

    private:
        std::shared_ptr< AUIImageWidget > m_pCloudTemplate;
        std::shared_ptr< AUITextWidget > m_pText;
    };
}
