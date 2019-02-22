#pragma once


#include "MAUITemplateDef.h"

class AUIDrawable;
class AUILinearLayoutWidget;
class AUIWidget;

namespace mit
{
    namespace alice
    {
        class MAUITemplate;
        class MAUITemplatePool;

        class ALICEUI_API MAUITemplateProcessor
        {
        public:
            MAUITemplateProcessor();


            //////////////////////////////////////////////////////////////////////////
            // Pool
        public:
            void Clear();
			bool Insert( const std::wstring& tag, const std::shared_ptr< MAUITemplate >& pTemplate );
            bool Remove( const std::wstring& tag );
            bool Has( const std::wstring& tag ) const;
        protected:
            void SetPool( const std::shared_ptr< MAUITemplatePool >& pPool );
        private:
            std::shared_ptr< MAUITemplatePool > m_pPool;


            //////////////////////////////////////////////////////////////////////////
            // Load
        public:
            bool IsLoaded() const { return m_bLoaded; }
            bool Load();
            bool Unload();
        private:
            bool m_bLoaded;


            //////////////////////////////////////////////////////////////////////////
            // Root
        public:
            void SetRootWidget( const std::shared_ptr< AUILinearLayoutWidget >& pRootWidget );
            void SetRootWidget( AUILinearLayoutWidget* const pRootWidget );
            std::shared_ptr< AUILinearLayoutWidget > GetRootWidget() const { return m_pRootWidget; }
            void SetRootTags( const std::vector< std::wstring >& arrRootTags );
            void SetRootTags( const std::wstring& rootTag0 ) {
                std::vector< std::wstring > _RootTags; _RootTags.reserve( 1 );
                _RootTags.emplace_back( rootTag0 );
                this->SetRootTags( _RootTags );
            }
            void SetRootTags( const std::wstring& rootTag0, const std::wstring& rootTag1 ) {
                std::vector< std::wstring > _RootTags; _RootTags.reserve( 2 );
                _RootTags.emplace_back( rootTag0 ); _RootTags.emplace_back( rootTag1 );
                this->SetRootTags( _RootTags );
            }
            void SetRootTags( const std::wstring& rootTag0, const std::wstring& rootTag1, const std::wstring& rootTag2 ) {
                std::vector< std::wstring > _RootTags; _RootTags.reserve( 3 );
                _RootTags.emplace_back( rootTag0 ); _RootTags.emplace_back( rootTag1 ); _RootTags.emplace_back( rootTag2 );
                this->SetRootTags( _RootTags );
            }
            void SetRootTags( const std::wstring& rootTag0, const std::wstring& rootTag1, const std::wstring& rootTag2, const std::wstring& rootTag3 ) {
                std::vector< std::wstring > _RootTags; _RootTags.reserve( 4 );
                _RootTags.emplace_back( rootTag0 ); _RootTags.emplace_back( rootTag1 ); _RootTags.emplace_back( rootTag2 ); _RootTags.emplace_back( rootTag3 );
                this->SetRootTags( _RootTags );
            }
            void SetRootTags( const std::wstring& rootTag0, const std::wstring& rootTag1, const std::wstring& rootTag2, const std::wstring& rootTag3, const std::wstring& rootTag4 ) {
                std::vector< std::wstring > _RootTags; _RootTags.reserve( 5 );
                _RootTags.emplace_back( rootTag0 ); _RootTags.emplace_back( rootTag1 ); _RootTags.emplace_back( rootTag2 ); _RootTags.emplace_back( rootTag3 ); _RootTags.emplace_back( rootTag4 );
                this->SetRootTags( _RootTags );
            }
        private:
            std::shared_ptr< AUILinearLayoutWidget > m_pRootWidget;
            std::vector< std::wstring > m_RootTags;


            //////////////////////////////////////////////////////////////////////////
            // Update Transaction
        public:
            bool IsTrPrepared() const { return IsLoaded() && m_bTrPrepared; }
            bool TrPrepare();
            bool TrCommit();
            bool TrRollback();

            void TrInsert( const std::wstring& toTag, const std::wstring& targetTag, const std::wstring& text, const std::shared_ptr< AUIDrawable>& pImage );
            void TrInsert( const std::wstring& toTag, const std::wstring& targetTag ) { this->TrInsert( toTag, targetTag, L"", nullptr ); }
            void TrInsert( const std::wstring& toTag, const std::wstring& targetTag, const std::wstring& text ) { this->TrInsert( toTag, targetTag, text, nullptr ); }
            void TrInsert( const std::wstring& toTag, const std::wstring& targetTag, const std::shared_ptr< AUIDrawable >& pImage ) { this->TrInsert( toTag, targetTag, L"", pImage ); }
            void TrInsert( const std::wstring& toTag, const std::shared_ptr< AUIWidget >& pWidget, const std::wstring& text, const std::shared_ptr< AUIDrawable >& pImage );
            void TrInsert( const std::wstring& toTag, const std::shared_ptr< AUIWidget >& pWidget ) { this->TrInsert( toTag, pWidget, L"", nullptr ); }
            void TrRemove( const std::wstring& toTag, const std::wstring& targetTag );
            void TrRemove( const std::wstring& toTag, const std::shared_ptr< AUIWidget >& pWidget );
            void TrClear( const std::wstring& toTag );
        private:
            bool TrOptimize();
            bool m_bTrPrepared;
        private:
            struct Tr
            {
                enum Cmd
                {
                    Clear_Cmd,
                    Insert_Cmd,
                    Remove_Cmd,
                    Param_Cmd,
                };
                Cmd fCmd;

                std::wstring fToTag;

                std::wstring fTargetTag;
                std::shared_ptr< AUIWidget > fWidget;

                std::wstring fText;
                std::shared_ptr< AUIDrawable > fImage;


                Tr( const Cmd& _cmd, const std::wstring& _toTag, const std::wstring& _fromTag ) : fCmd( _cmd ), fToTag( _toTag ), fTargetTag( _fromTag ) { }
                Tr( const Cmd& _cmd, const std::wstring& _toTag, const std::wstring& _fromTag, const std::wstring& _text, const std::shared_ptr< AUIDrawable >& _image ) : fCmd( _cmd ), fToTag( _toTag ), fTargetTag( _fromTag ), fText( _text ), fImage( _image ) { }
                Tr( const Cmd& _cmd, const std::wstring& _toTag, const std::shared_ptr< AUIWidget >& _widget ) : fCmd( _cmd ), fToTag( _toTag ), fWidget( _widget ) { }
                Tr( const Cmd& _cmd, const std::wstring& _toTag, const std::shared_ptr< AUIWidget >& _widget, const std::wstring& _text, const std::shared_ptr< AUIDrawable >& _image ) : fCmd( _cmd ), fToTag( _toTag ), fWidget( _widget ), fText( _text ), fImage( _image ) { }
            };
            std::vector< Tr > m_Transactions;
            std::unordered_map< AUIWidget*, std::wstring > m_Widget2Tag;
            std::unordered_map< std::wstring, std::wstring > m_Tag2Tag;



            //////////////////////////////////////////////////////////////////////////
            // Update
        public:
            void UpdateParam( const std::wstring& tag, const MAUITemplParam& param );
            std::shared_ptr< AUIWidget > GetTagWidget( const std::wstring& tag ) const;
            std::vector< std::wstring > GetAllTag() const;
        private:
            std::unordered_map< std::wstring, std::shared_ptr< AUIWidget > > m_mapTag2Widget;
        };
    }
}
