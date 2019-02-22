#pragma once

#include "AUIAPIDef.h"
#include "AUICommonDef.h"
#include "AUIBasicEnumDef.h"
#include "AUISkiaConfig.h"


#include "AUISensor.h"
#include "AUICompass.h"

#include "AUIApplication.h"
#include "AUIDrawable.h"
#include "AUIInstance.h"
#include "AUIWidget.h"
#include "AUIWidgetManager.h"


#ifdef MITALICE_EXPORTS
#   if defined(_MSC_VER)
#       define MITALICE_API  __declspec(dllexport)
#   else
#       define MITALICE_API  __attribute__((visibility("default")))
#   endif
#else
#   if defined(_MSC_VER)
#       define MITALICE_API  __declspec(dllimport)
#   else
#       define MITALICE_API
#   endif
#endif
