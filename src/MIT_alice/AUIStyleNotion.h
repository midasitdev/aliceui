#pragma once

#include "AUIAPIDef.h"
#include "AUIBasicEnumDef.h"

#include <any>
#include <variant>
#include <map>



enum MNOTION_VALUE_TYPE {
    MNV_NONE = 0,
    MNV_VISIBLE,
    MNV_DRAGGABLE,
    MNV_IGNORED,
    MNV_FLOAT,
    MNV_DEFAULT_WIDTH,
    MNV_DEFAULT_HEIGHT,
    MNV_BACKGROUND_COLOR,
    MNV_COLOR,
    MNV_OPACITY,
    MNV_MARGIN_LEFT,
    MNV_MARGIN_RIGHT,
    MNV_MARGIN_TOP,
    MNV_MARGIN_BOTTOM,
    MNV_PADDING_LEFT,
    MNV_PADDING_RIGHT,
    MNV_PADDING_TOP,
    MNV_PADDING_BOTTOM,
    MNV_WIDTH_POLICY,
    MNV_HEIGHT_POLICY,
    MNV_GRAVITY_OPTION,
    MNV_LAYOUT_GRAVITY_OPTION,
    MNV_LAYOUT_ALIGN_PARENT,
    MNV_TEXT_HORZONTAL_ALIGN,
    MNV_TEXT_VERTICAL_ALIGN,
    MNV_FONT_SIZE,
	MNV_FONT_COLOR,
	MNV_FONT_DISABLED_COLOR,
    MNV_FONT_FAMILY,
    MNV_FONT_STYLE,
    MNV_BACKGROUND_IMAGE,
    MNV_BACKGROUND_IMAGE_TOP,
	MNV_BACKGROUND_IMAGE_MID,
	MNV_BACKGROUND_IMAGE_BOTTOM,
	MNV_FOREGROUND_IMAGE,
	MNV_UNDERLINE,
    MNV_NUM
};

struct AUIStyleNotionValue
{
    template < class T >
    void SetValue(const T& ret)
    {
        fValue = std::make_any<T>(ret);
    }
    template < class T >
    bool GetValue(T& ret)const
    {
        if (fValue.type() != typeid(T))
            return false;

        ret = std::any_cast<T>(fValue);
        return true;
    }
    std::any fValue;

    //template < class T >
    //bool GetValue(T& ret)const
    //{
    //	auto pVal = std::get_if<T>(fVal);
    //	if (!pVal)
    //		return false;
    //	ret = *pVal;
    //	return true;
    //}


    //std::variant<
    //	bool,
    //	SkScalar,
    //	SkColor,
    //	SizePolicy,
    //	TextHorzAlign,
    //	TextVertAlign,
    //	std::vector< std::wstring >
    //> fValue;
};

class ALICEUI_API AUIStyleNotion
{
public:
    template < class T >
    bool GetValue(unsigned int eType, T& val) const
    {
        auto itr = m_mapValues.find(eType);
        if (itr == m_mapValues.end())
            return false;
        return itr->second.GetValue<T>(val);
    }

    template< class T >
    void SetValue(unsigned int eType, const T& val)
    {
        m_mapValues[eType].fValue = val;
    }
    bool HasVerticalAlign() const;
    bool HasHorizontalAlign() const;
    const std::map<unsigned int, AUIStyleNotionValue>& GetValueMap() const { return m_mapValues; }

private:
    std::map<unsigned int, AUIStyleNotionValue> m_mapValues;	//차피..unordered map이면 array 쓰나 매한가지 아닌가..
};

