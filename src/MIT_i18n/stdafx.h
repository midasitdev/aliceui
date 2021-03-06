#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


#include <memory>
#include <cassert>
#include <string>
#include <mutex>
#include <codecvt>

// ICU
#include <unicode/uclean.h>
#include <unicode/calendar.h>
#include <unicode/unistr.h>
#include <unicode/ucnv.h>
#include <unicode/locid.h>
#include <unicode/timezone.h>
#include <unicode/datefmt.h>
#include <unicode/numfmt.h>
#include <unicode/dtfmtsym.h>
#include <unicode/alphaindex.h>
#include <unicode/msgfmt.h>
#include <unicode/fieldpos.h>
#include <unicode/fmtable.h>
