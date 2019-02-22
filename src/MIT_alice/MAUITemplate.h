#pragma once


#include "MAUITemplateDef.h"

namespace mit
{
    namespace alice
    {
		class MAUIFastStyleSheetSetter;
        class ALICEUI_API MAUITemplate : public std::enable_shared_from_this< MAUITemplate >
        {
        public:
            MAUITemplate();
            virtual ~MAUITemplate();

            //////////////////////////////////////////////////////////////////////////
            // Create
        public:
            template< class _Template >
            static std::shared_ptr< _Template > CreateTemplate() {
                static_assert( std::is_base_of< MAUITemplate, _Template >::value, "Must be base of MAUITemplate" );
                auto _pT = std::make_shared< _Template >();
                return _pT;
            }
            template< class _Template >
            static std::shared_ptr< _Template > CreateTemplate( const std::wstring& mssClass ) {
                static_assert( std::is_base_of< MAUITemplate, _Template >::value, "Must be base of MAUITemplate" );
                auto _pT = std::make_shared< _Template >();
                _pT->SetMSSClass( mssClass );
                return _pT;
            }
            template< class _Template, class _Arg0 >
            static std::shared_ptr< _Template > CreateTemplate( const std::wstring& mssClass, const _Arg0& _arg0 ) {
                static_assert( std::is_base_of< MAUITemplate, _Template >::value, "Must be base of MAUITemplate" );
                auto _pT = std::make_shared< _Template >( _arg0 );
                _pT->SetMSSClass( mssClass );
                return _pT;
            }

            //////////////////////////////////////////////////////////////////////////
            // Create
        public:
            std::shared_ptr< AUIWidget > CreateWidget();
            void UpdateParam( AUIWidget* const pRoot, const MAUITemplParam& param );
            void UpdateInsert( AUIWidget* const pRoot, const MAUITemplInput& input );
            void UpdateRemove( AUIWidget* const pRoot, const MAUITemplInput& input );
            void UpdateClear( AUIWidget* const pRoot, const MAUITemplInput& input );
        protected:
            virtual std::shared_ptr< AUIWidget > OnCreateWidget() { return nullptr; }
            virtual void OnUpdateParam( AUIWidget* const pRoot, const MAUITemplParam& param ) { }

            virtual void OnUpdateInsert( AUIWidget* const pRoot, const MAUITemplInput& input ) { }
            virtual void OnUpdateRemove( AUIWidget* const pRoot, const MAUITemplInput& input ) { }
            virtual void OnUpdateClear( AUIWidget* const pRoot, const MAUITemplInput& input ) { }


			//////////////////////////////////////////////////////////////////////////
			// TagClass
		//public:
		//	void SetFastStyleSheetSetter( std::shared_ptr<MAUIFastStyleSheetSetter> pFSSSetter){ m_pFSSSetter = pFSSSetter;}
		//	std::shared_ptr<MAUIFastStyleSheetSetter> GetFastStyleSheetSetter(){ return m_pFSSSetter; }
		//private:
		//	std::shared_ptr<MAUIFastStyleSheetSetter> m_pFSSSetter;
		public:
			void SetStyleSheet(std::shared_ptr<const AUIWidgetStyle> pStyle) { m_pStyle = pStyle; }
			std::shared_ptr<const AUIWidgetStyle> GetStyleSheet() const { return m_pStyle; }

			void SetComponentStyle(const std::wstring& component_name, std::shared_ptr<const AUIWidgetStyle> style) {}
		private:
			std::shared_ptr<const AUIWidgetStyle> m_pStyle;


            //////////////////////////////////////////////////////////////////////////
            // TagClass
        public:
            void SetMSSClass( const std::wstring& mssClass ) { m_MSSClass = mssClass; }
            std::wstring GetMSSClass() const { return m_MSSClass; }
        private:
            std::wstring m_MSSClass;




        };
    }
}
