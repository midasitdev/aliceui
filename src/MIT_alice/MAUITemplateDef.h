#pragma once


#include "AUICommonDef.h"
#include <variant>

class AUIDrawable;
class AUIWidget;
class AUIWidgetStyle;

namespace mit
{
    namespace alice
    {
		class MAUIFastStyleSheetSetter;
        struct MAUITemplParam
        {
			enum TEMPL_PARAM
			{
				TEMPL_PARAM_CHILD_SHOW,
				TEMPL_PARAM_MSS,
				TEMPL_PARAM_COMPONENT_MSS,
				TEMPL_PARAM_TEXT,
				TEMPL_PARAM_IMAGE,
			};
			struct _temp_show{
				std::shared_ptr<AUIWidget > fWidget;
				bool fShow;
				_temp_show(std::shared_ptr<AUIWidget > _widget, bool _show) :fWidget(_widget), fShow(_show) {}
			};
			struct _temp_comp_mss
			{
				std::wstring fComponent;
				std::shared_ptr<const AUIWidgetStyle> fMss;
				_temp_comp_mss(std::wstring _comp, std::shared_ptr<const AUIWidgetStyle> _mss) : fComponent(_comp), fMss(_mss) {}
			};


			TEMPL_PARAM fType;
			std::variant
				<
				std::wstring,
				std::shared_ptr< const AUIDrawable >,
				std::shared_ptr<const AUIWidgetStyle>,
				_temp_show,
				_temp_comp_mss
				> fParam;

			MAUITemplParam(std::shared_ptr<AUIWidget > _widget, bool _show) :fType(TEMPL_PARAM_CHILD_SHOW), fParam(_temp_show(_widget, _show)) {  }
			MAUITemplParam(std::shared_ptr< const AUIDrawable > _image) :fType(TEMPL_PARAM_IMAGE), fParam(_image) {  }
			MAUITemplParam(std::wstring _text) :fType(TEMPL_PARAM_TEXT), fParam(_text) {  }
			MAUITemplParam(std::shared_ptr<const AUIWidgetStyle> _mss) :fType(TEMPL_PARAM_MSS), fParam(_mss) {  }
			MAUITemplParam(std::wstring _comp, std::shared_ptr<const AUIWidgetStyle> _mss) :fType(TEMPL_PARAM_COMPONENT_MSS), fParam(_temp_comp_mss(_comp,_mss)) {  }



   //         std::wstring fVar;
   //         std::wstring fText;
   //         std::shared_ptr< const SkBitmap > fImage;
			//std::shared_ptr< AUIWidget > fWidget;
			//std::shared_ptr< mit::alice::MSSStyleSheet const> fMss;
   //         bool fHasShow;
   //         bool fSubShow;
   //         bool fShow;
   //         MAUITemplParam() : fHasShow( false ), fSubShow( false ), fShow( true ) { }
   //         MAUITemplParam( bool _show ) : fHasShow( true ), fSubShow( false ), fShow( _show ) { }
   //         MAUITemplParam( bool _show, const std::shared_ptr< AUIWidget >& _widget ) : fHasShow( false ), fSubShow( true ), fShow( _show ), fWidget( _widget ) { }
   //         MAUITemplParam( const std::wstring& _var, const std::wstring& _text ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fText( _text ) { }
   //         MAUITemplParam( const std::wstring& _var, const std::shared_ptr< const SkBitmap >& _image ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fImage( _image ) { }
   //         MAUITemplParam( const std::wstring& _var, const std::shared_ptr< AUIWidget >& _widget ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fWidget( _widget ) { }
   //         MAUITemplParam( const std::wstring& _var, const std::wstring& _text, const std::shared_ptr< const SkBitmap >& _image ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fText( _text ), fImage( _image ) { }

        };

        struct MAUITemplInput
        {
            std::wstring fVar;
            std::wstring fText;
            std::shared_ptr< AUIDrawable > fImage;
            std::shared_ptr< AUIWidget > fWidget;

            MAUITemplInput() { }
            MAUITemplInput( const std::wstring& _var, const std::shared_ptr< AUIWidget >& _widget ) : fVar( _var ), fWidget( _widget ) { }
            MAUITemplInput( const std::wstring& _var, const std::wstring& _text, const std::shared_ptr< AUIWidget >& _widget ) : fVar( _var ), fText( _text ), fWidget( _widget ) { }
            MAUITemplInput( const std::wstring& _var, const std::wstring& _text ) : fVar( _var ), fText( _text ) { }
            MAUITemplInput( const std::wstring& _var, const std::shared_ptr< AUIDrawable >& _image ) : fVar( _var ), fImage( _image ) { }
            MAUITemplInput( const std::wstring& _var, const std::wstring& _text, const std::shared_ptr< AUIDrawable >& _image, const std::shared_ptr< AUIWidget >& _widget ) : fVar( _var ), fText( _text ), fImage( _image ), fWidget( _widget ) { }
        };
    }
}
