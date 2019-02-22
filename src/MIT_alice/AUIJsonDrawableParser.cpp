#include "pch.h"
#include "AUIJsonDrawableParser.h"
#include "AUIGalleria.h"
#include "AUILevelListDrawable.h"
#include "AUINinePatch.h"
#include "AUINinePatchDrawable.h"
#include "AUIStateDrawable.h"
#include "AUIAnimationListDrawable.h"
#include "AUIStateListDrawable.h"
#include "AUIApplication.h"
#include "AUIImageDrawable.h"
#include "AUIStringUtil.h"
#include "AUIResourceManager.h"

using JsonDocument = rapidjson::GenericDocument< rapidjson::UTF16<> >;
using JsonValue = JsonDocument::GenericValue;
using JsonParserFlag = unsigned int;
constexpr JsonParserFlag kParserDefaultFlag = rapidjson::kParseCommentsFlag | rapidjson::kParseTrailingCommasFlag;

namespace
{
	std::wstring _make_current_path( const std::wstring& base_path, const std::wstring& path)
	{
		if (path.find(L"/") == 0)
			return AUIStringUtil::ToLowerCase(path.substr(1));
		else if (path.find(L"./") == 0)
			return base_path + AUIStringUtil::ToLowerCase(path.substr(2));
		else
			return base_path + AUIStringUtil::ToLowerCase(path);
	}


	std::optional<std::shared_ptr<AUIDrawable>> ParseLevelList(const JsonValue& levelList, const std::wstring& basePath, bool isFromFile, const AUIJsonDrawableParser::OptParam& optParam)
	{
		bool isValid = false;
		auto pBase = std::make_shared<AUILevelListDrawable>();
		AUIGalleria galleria;
		if (levelList.IsArray())
		{
			const auto& items = levelList.GetArray();
			for (const auto& itrItem : items)
			{
				if (false == itrItem.HasMember(L"item"))
					continue;
				const auto& item = itrItem.FindMember(L"item")->value;
				if (item.IsObject())
				{
					int low = 0;
					int high = 0;
					std::shared_ptr< AUIDrawable > pDrawable;
					if (item.HasMember(L"minLevel"))
					{
						const auto& minLevelValue = item.FindMember(L"minLevel")->value;
						if (minLevelValue.IsInt())
							low = minLevelValue.GetInt();
					}
					if (item.HasMember(L"maxLevel"))
					{
						const auto& maxLevelValue = item.FindMember(L"maxLevel")->value;
						if (maxLevelValue.IsInt())
							high = maxLevelValue.GetInt();
					}
					if (item.HasMember(L"drawable"))
					{
						std::wstring strDrawable;
						const auto& drawableValue = item.FindMember(L"drawable")->value;
						if (drawableValue.IsString())
							strDrawable = drawableValue.GetString();
						if (false == strDrawable.empty())
						{
							AUIJsonDrawableParser parser;
                            parser.SetOptParam(optParam);
							auto drawableRef = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, strDrawable)) : parser.LoadFromPathByResource(_make_current_path(basePath, strDrawable));
							if (drawableRef)
								pDrawable = *drawableRef;
						}
					}
					if (nullptr != pDrawable)
					{
						pBase->AddLevel(low, high, pDrawable);
						isValid = true;
					}
				}
			}
		}
		else
		{
			if (levelList.HasMember(L"item"))
			{
				const auto& item = levelList.FindMember(L"item")->value;
				if (item.IsObject())
				{
					int low = 0;
					int high = 0;
					std::shared_ptr< AUIDrawable > pDrawable;
					if (item.HasMember(L"minLevel"))
					{
						const auto& minLevelValue = item.FindMember(L"minLevel")->value;
						if (minLevelValue.IsInt())
							low = minLevelValue.GetInt();
					}
					if (item.HasMember(L"maxLevel"))
					{
						const auto& maxLevelValue = item.FindMember(L"maxLevel")->value;
						if (maxLevelValue.IsInt())
							high = maxLevelValue.GetInt();
					}
					if (item.HasMember(L"drawable"))
					{
						std::wstring strDrawable;
						const auto& drawableValue = item.FindMember(L"drawable")->value;
						if (drawableValue.IsString())
							strDrawable = drawableValue.GetString();
						if (false == strDrawable.empty())
						{
							AUIJsonDrawableParser parser;
                            parser.SetOptParam(optParam);
							auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, strDrawable)) : parser.LoadFromPathByResource(_make_current_path(basePath, strDrawable));
							if (refDrawable)
							{
								pDrawable = *refDrawable;
							}
						}
					}
					if (nullptr != pDrawable)
					{
						pBase->AddLevel(low, high, pDrawable);
						isValid = true;
					}
				}
			}

		}
		if (isValid)
			return { pBase };
		return {};
	}
	std::optional<std::shared_ptr<AUIDrawable>> ParseStated(const JsonValue& stated, const std::wstring& basePath, bool isFromFile, const AUIJsonDrawableParser::OptParam& optParam)
	{
		bool isValid = false;
		auto pStateDrawable = std::make_shared< AUIStateDrawable >();
		AUIGalleria galleria;
		if (stated.HasMember(L"default"))
		{
			const auto path = std::wstring(stated.FindMember(L"default")->value.GetString());
			AUIJsonDrawableParser parser;
            parser.SetOptParam(optParam);
			const auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, path)) : parser.LoadFromPathByResource(_make_current_path(basePath, path));
			if (refDrawable)
			{
				pStateDrawable->SetTrueStateDrawable(AUIState::kDefault, *refDrawable);
				isValid = true;
			}
		}
		if (stated.HasMember(L"hovered"))
		{
			const auto path = std::wstring(stated.FindMember(L"hovered")->value.GetString());
			AUIJsonDrawableParser parser;
            parser.SetOptParam(optParam);
			const auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, path)) : parser.LoadFromPathByResource(_make_current_path(basePath, path));
			if (refDrawable)
			{
				pStateDrawable->SetTrueStateDrawable(AUIState::kMouseHovered, *refDrawable);
				isValid = true;
			}
		}
		if (stated.HasMember(L"pressed"))
		{
			const auto path = std::wstring(stated.FindMember(L"pressed")->value.GetString());
			AUIJsonDrawableParser parser;
            parser.SetOptParam(optParam);
			const auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, path)) : parser.LoadFromPathByResource(_make_current_path(basePath, path));
			if (refDrawable)
			{
				pStateDrawable->SetTrueStateDrawable(AUIState::kPressed, *refDrawable);
				isValid = true;
			}
		}
		if (stated.HasMember(L"disabled"))
		{
			const auto path = std::wstring(stated.FindMember(L"disabled")->value.GetString());
			AUIJsonDrawableParser parser;
            parser.SetOptParam(optParam);
			const auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, path)) : parser.LoadFromPathByResource(_make_current_path(basePath, path));
			if (refDrawable)
			{
				pStateDrawable->SetTrueStateDrawable(AUIState::kDisabled, *refDrawable);
				isValid = true;
			}
		}
		if (stated.HasMember(L"checked"))
		{
			const auto path = std::wstring(stated.FindMember(L"checked")->value.GetString());
			AUIJsonDrawableParser parser;
            parser.SetOptParam(optParam);
			const auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, path)) : parser.LoadFromPathByResource(_make_current_path(basePath, path));
			if (refDrawable)
			{
				pStateDrawable->SetTrueStateDrawable(AUIState::kChecked, *refDrawable);
				isValid = true;
			}
		}
		if (stated.HasMember(L"checkindeterminate"))
		{
			const auto path = std::wstring(stated.FindMember(L"checkindeterminate")->value.GetString());
			AUIJsonDrawableParser parser;
            parser.SetOptParam(optParam);
			const auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, path)) : parser.LoadFromPathByResource(_make_current_path(basePath, path));
			if (refDrawable)
			{
				pStateDrawable->SetTrueStateDrawable(AUIState::kCheckIndeterminate, *refDrawable);
				isValid = true;
			}
		}
		if (stated.HasMember(L"focused"))
		{
			const auto path = std::wstring(stated.FindMember(L"focused")->value.GetString());
			AUIJsonDrawableParser parser;
            parser.SetOptParam(optParam);
			const auto refDrawable = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, path)) : parser.LoadFromPathByResource(_make_current_path(basePath, path));
			if (refDrawable)
			{
				pStateDrawable->SetTrueStateDrawable(AUIState::kFocused, *refDrawable);
				isValid = true;
			}
		}
		if (isValid)
			return { pStateDrawable };
		return {};
	}
	std::optional<std::shared_ptr<AUIDrawable>> ParseAnimationList(const JsonValue& animationList, const std::wstring& basePath, bool isFromFile, const AUIJsonDrawableParser::OptParam& optParam)
	{
		bool isValid = false;
		auto pAnimationListDrawable = std::make_shared<AUIAnimationListDrawable>();
		AUIGalleria galleria;
		if (animationList.HasMember(L"repeat"))
		{
			const auto& r = animationList.FindMember(L"repeat")->value;
			if (r.IsBool())
				pAnimationListDrawable->SetRepeat(r.GetBool());
		}
		if (animationList.HasMember(L"items"))
		{
			const auto& items = animationList.FindMember(L"items")->value;
			if (items.IsArray())
			{
				for (const auto& i : items.GetArray())
				{
					if (false == i.HasMember(L"duration"))
						continue;
					if (false == i.HasMember(L"src"))
						continue;
					const auto& durRef = i.FindMember(L"duration")->value;
					const auto& srcRef = i.FindMember(L"src")->value;

					if (false == durRef.IsInt())
						continue;
					if (false == srcRef.IsString())
						continue;
					const auto src = std::wstring(srcRef.GetString());
					AUIJsonDrawableParser parser;
                    parser.SetOptParam(optParam);
					const auto drawableRef = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, src)) : parser.LoadFromPathByResource(_make_current_path(basePath, src));
					if (drawableRef)
					{
						pAnimationListDrawable->EmplaceFrameData(*drawableRef, durRef.GetInt());
						isValid = true;
					}
				}
			}
		}
		if (isValid)
		{
			// TODO : setup start timing
			pAnimationListDrawable->Start();
			return { pAnimationListDrawable };
		}
		return {};
	}



	template <typename T>
	bool FindMember(bool& ret, const T& src, const wchar_t * memb)
	{
		if (src.HasMember(memb))
		{
			auto found = src.FindMember(memb);
			AUIAssert(src.MemberEnd() != found);
			AUIAssert(found->value.IsBool());
			ret = found->value.GetBool();
			return true;
		}
		return false;
	}


	std::optional<std::shared_ptr<AUIDrawable>> ParseStateList(const JsonValue& stateList, const std::wstring& basePath, bool isFromFile, const AUIJsonDrawableParser::OptParam& optParam)
	{

		bool isValid = false;
		auto pStateImgs = std::make_shared<AUIStateImgSrc>();
		AUIGalleria galleria;
		if (stateList.HasMember(L"default-src"))
		{
			const auto& srcRef = stateList.FindMember(L"default-src")->value;
			if (false == srcRef.IsString())
				;
			else
			{
				const auto src = std::wstring(srcRef.GetString());
				AUIJsonDrawableParser parser;
                parser.SetOptParam(optParam);
				auto drawableRef = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, src)) : parser.LoadFromPathByResource(_make_current_path(basePath, src));
				if (drawableRef)
				{
					pStateImgs->_default_feature()._drawable = *drawableRef;
					isValid = true;
				}
			}
		}
		if (stateList.HasMember(L"states"))
		{
			auto foundStates = stateList.FindMember(L"states");

			if (foundStates == stateList.MemberEnd())
				;
			else if (foundStates->value.IsArray())
			{
				const auto& arrStates = foundStates->value.GetArray();
				for (const auto& state : arrStates)
				{
					AUIState auiState;
					bool bFlag;

					if (FindMember(bFlag, state, L"freeze"))
						auiState.SetFreeze(bFlag);
					if (FindMember(bFlag, state, L"pressed"))
						auiState.SetPressed(bFlag);
					if (FindMember(bFlag, state, L"draggable"))
						auiState.SetDraggable(bFlag);
					if (FindMember(bFlag, state, L"dragging"))
						auiState.SetDragging(bFlag);
					if (FindMember(bFlag, state, L"focusable"))
						auiState.SetFocusable(bFlag);
					if (FindMember(bFlag, state, L"focused"))
						auiState.SetFocused(bFlag);
					if (FindMember(bFlag, state, L"checkable"))
						auiState.SetCheckable(bFlag);
					if (FindMember(bFlag, state, L"checked"))
						auiState.SetChecked(bFlag);
					if (FindMember(bFlag, state, L"check-indeterminate"))
						auiState.SetCheckedIndeterminate(bFlag);
					if (FindMember(bFlag, state, L"selectable"))
						auiState.SetSelectable(bFlag);
					if (FindMember(bFlag, state, L"selected"))
						auiState.SetSelected(bFlag);
					if (FindMember(bFlag, state, L"disabled"))
						auiState.SetDisabled(bFlag);
					if (FindMember(bFlag, state, L"hovered"))
						auiState.SetMouseHovered(bFlag);
					if (FindMember(bFlag, state, L"lbutton-down"))
						auiState.SetMouseLDown(bFlag);
					if (FindMember(bFlag, state, L"mbutton-down"))
						auiState.SetMouseMDown(bFlag);
					if (FindMember(bFlag, state, L"rbutton-donw"))
						auiState.SetMouseRDown(bFlag);
					if (FindMember(bFlag, state, L"clickable"))
						auiState.SetClickable(bFlag);



					const auto foundName = state.FindMember(L"name");
					if (foundName != state.MemberEnd() && foundName->value.IsString())
					{
						const auto& state_name = foundName->value.GetString();
						pStateImgs->_set_state_name(auiState, state_name);

					}
					const auto foundSrc = state.FindMember(L"src");
					if (foundSrc != state.MemberEnd())
					{
						const auto& srcRef = foundSrc->value;
						if (false == srcRef.IsString())
							continue;
						const auto src = std::wstring(srcRef.GetString());
						AUIJsonDrawableParser parser;
                        parser.SetOptParam(optParam);
						auto drawableRef = isFromFile ? parser.LoadFromPathByFile(_make_current_path(basePath, src)) : parser.LoadFromPathByResource(_make_current_path(basePath, src));
						if (!drawableRef)
							continue;

						auto& feature = pStateImgs->_state_feature(auiState);
						feature._drawable = *drawableRef;
					}
				}
			}
		}
		if (stateList.HasMember(L"transitions"))
		{
			const auto& transitions = stateList.FindMember(L"transitions")->value;


		}
		if (isValid)
		{
			// TODO : setup start timing
			auto pStateListDrawable = std::make_shared<AUIStateListDrawable>();
			pStateListDrawable->SetStateImgsrc(pStateImgs);
			return { pStateListDrawable };
		}
		return {};
	}
}

AUIJsonDrawableParser::AUIJsonDrawableParser()
{

}

AUIJsonDrawableParser::~AUIJsonDrawableParser()
{

}

std::optional<std::shared_ptr<AUIDrawable>> AUIJsonDrawableParser::LoadFromPath_Private(const std::wstring& input_path, bool isFromFile)
{
	const auto isJson = std::wstring::npos != input_path.rfind(L".json");
	auto filepath = input_path;
	if (isFromFile)
	{
		const auto tempDir = L"/temp/resource/";
		const auto appDir = AUIStringUtil::ToLowerCase(AUIApplication::Instance().GetApplicationDirectory());
		filepath = appDir + tempDir + input_path;
	}

	if (isJson)
	{
		return LoadFromPathJson(filepath, isFromFile);
	}
	else
	{
		AUIGalleria galleria;
		const auto isNinePatch = std::wstring::npos != input_path.rfind(L".9.png");
        sk_sp<SkImage> pImage;
		pImage = isFromFile ? galleria.GetFromFile(filepath) : galleria.GetFromResource(filepath);
		if (pImage)
		{
			if (isNinePatch)
			{
				return { std::make_shared< AUINinePatchDrawable >(AUINinePatch::MakeFromNinePatchImage(pImage)) };
			}
			else
			{
				return { std::make_shared< AUIImageDrawable >(pImage, m_OptParam.fDefaultImageStretch) };
			}
		}
	}
	return {};
}

void AUIJsonDrawableParser::SetDefaultImageStretch(AUIImageStretch stretch)
{
    m_OptParam.fDefaultImageStretch = stretch;
}

void AUIJsonDrawableParser::SetOptParam(const OptParam& optParam)
{
    m_OptParam = optParam;
}

std::optional<std::shared_ptr<AUIDrawable>> AUIJsonDrawableParser::LoadFromPathJson(const std::wstring& json_path, bool isFromFile)
{
	std::wstring json;

    json = AUIResourceManager::Instance().LoadText(json_path);
    if (json.empty())
        return {};


	std::wstring basePath;
	const auto basePathPos = json_path.find_last_of(L"/\\");
	if (std::wstring::npos != basePathPos)
		basePath = json_path.substr(0, basePathPos + 1);
	else
		basePath = L"/";    // Root directory(?)


	JsonDocument doc;
	if (doc.Parse<kParserDefaultFlag>(json.c_str()).HasParseError())
		return {};

	if (doc.HasMember(L"level-list"))
		return ::ParseLevelList(doc.FindMember(L"level-list")->value, basePath, isFromFile, m_OptParam);
	else if (doc.HasMember(L"stated"))
		return ::ParseStated(doc.FindMember(L"stated")->value, basePath, isFromFile, m_OptParam);
	else if (doc.HasMember(L"animation-list"))
		return ::ParseAnimationList(doc.FindMember(L"animation-list")->value, basePath, isFromFile, m_OptParam);
	else if (doc.HasMember(L"state-list"))
		return ::ParseStateList(doc.FindMember(L"state-list")->value, basePath, isFromFile, m_OptParam);
	return {};
}

