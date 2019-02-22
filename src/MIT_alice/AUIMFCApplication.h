#pragma once

#include "AUIApplication.h"

class AUIHandle;

class AUIApplication::Impl final
{
public:
    Impl();
    ~Impl() = default;


    //////////////////////////////////////////////////////////////////////////
    // Application Information
public:
    AUIHandle* GetApplicationHandle() const;
    void GetApplicationSize(int& width, int& height) const;
    void GetApplicationPosition(int& x, int& y) const;
    void GetApplicationPositionAndSize(int& x, int& y, int& width, int& height) const;
    std::wstring GetApplicationDirectory() const;
private:
    std::wstring m_strExeDir;


    //////////////////////////////////////////////////////////////////////////
    // Desktop Information
public:
    AUIHandle* const GetDesktopHandle() const;
    void GetDesktopSize(int& width, int& height) const;
    void GetVirtualScreenSize(int& width, int& height) const;
    void GetMonitorCount(int& count) const;
    void ConvertToDesktopPos(int& desktopX, int& desktopY, const int x, const int y, AUIHandle* const pHandle);
    void GetMonitorRectFromPoint(SkRect& monitorRect, const int& desktopX, const int& desktopY);


    //////////////////////////////////////////////////////////////////////////
    // Mouse Information
public:
    void GetMousePosition(int& x, int& y) const;
    void GetMouseDragOffset(int& x, int& y) const;
    bool IsMouseRightHanded() const;
};
