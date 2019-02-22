#pragma once
#define MIDAS_SDK
#include "MAUIRelativeLayoutWidget.h"

#include "HeaderPre.h"
namespace mit
{
	namespace alice
	{
		class MAUITitleBarWidget;
		class MAUIImageButtonWidget;
		class __MY_EXT_CLASS__ MMainAUITitleBarWIdget : public MAUIRelativeLayoutWidget
		{
			typedef MAUIRelativeLayoutWidget __SuperWidget;
			MRUNTIME_DECL_KINDOF(MMainAUITitleBarWIdget);
		public:
			MMainAUITitleBarWIdget();
			MMainAUITitleBarWIdget(const std::wstring& caption);
			virtual ~MMainAUITitleBarWIdget();

		private:
			std::shared_ptr< mit::alice::MAUITitleBarWidget > m_pTitle;
			std::shared_ptr< mit::alice::MAUIImageButtonWidget > m_pCloseButton;
			std::shared_ptr< mit::alice::MAUIImageButtonWidget > m_pMaximizeButton;
			std::shared_ptr< mit::alice::MAUIImageButtonWidget > m_pMinimizeButton;
		};
	}
}
#include "HeaderPost.h"