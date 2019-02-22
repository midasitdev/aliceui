#include "pch.h"
#include "AUIOpenGL.h"
#ifdef _WIN32
#   include <wingdi.h>
#endif

void AUIOpenGL::AssertGLContext()
{
#ifdef _WIN32
    AUIAssert( wglGetCurrentContext() );
#else
    AUIAssertFailReason("Implement context check function");
#endif
}

bool AUIOpenGL::IsInGLContext()
{

#ifdef _WIN32
    return wglGetCurrentContext() != NULL;
#else
    AUIAssertFailReason("Implement context check function");
    return false;
#endif
}
