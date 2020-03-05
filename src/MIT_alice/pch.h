#pragma once

#define NOMINMAX

#if defined(_WIN32)

#   define VC_EXTRALEAN
#   define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

#   include "targetver.h"
#   include <afxwin.h>

#endif

//////////////////////////////////////////////////////////////////////////
// STL Header
#include <cwctype>
#include <cstdio>
#include <regex>
#include <atomic>
#include <mutex>
#include <thread>
#include <limits>
#include <cmath>
#include <cassert>
#include <codecvt>
#include <functional>
#include <cstdint>
#include <chrono>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <type_traits>
#include <typeindex>
#include <random>
#include <queue>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <exception>

//////////////////////////////////////////////////////////////////////////
// Rapid JSON
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

//////////////////////////////////////////////////////////////////////////
// GLM Header
//#define GLM_FORCE_CTOR_INIT
//#define GLM_FORCE_EXPLICIT_CTOR
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_query.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/optimum_pow.hpp>
#include <glm/gtx/projection.hpp>

//////////////////////////////////////////////////////////////////////////
// GL
#include "AUIOpenGL.h"


//////////////////////////////////////////////////////////////////////////
// Skia
#include "AUISkiaConfig.h"
#include "AUIColorDef.h"
#include "AUIDebug.h"
