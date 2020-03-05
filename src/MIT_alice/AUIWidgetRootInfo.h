#pragma once

#include "AUICommonDef.h"

class ALICEUI_API AUIWidgetRootInfo final
{
public:
    AUIWidgetRootInfo() = default;
    ~AUIWidgetRootInfo() = default;

    //////////////////////////////////////////////////////////////////////////
    // Info Data
public:
    void SetTargetCoord(AUICoordSpace eCoord) {
        m_eTargetCoord = eCoord;
    }
    void SetMatrix(const glm::mat4& mat) {
        m_matRoot = mat;
    }
    AUICoordSpace GetTargetCoord() const {
        return m_eTargetCoord;
    }
    const glm::mat4& GetMatrix() const {
        return m_matRoot;
    }
private:
    AUICoordSpace m_eTargetCoord = AUICoordSpace::kScreenSpace;
    glm::mat4 m_matRoot = glm::mat4(1.f);
};
