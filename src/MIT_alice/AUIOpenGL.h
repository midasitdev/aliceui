#pragma once

#include "AUIAPIDef.h"

class ALICEUI_API AUIOpenGL final
{
public:
    static void AssertGLContext();
    static bool IsInGLContext();
};
