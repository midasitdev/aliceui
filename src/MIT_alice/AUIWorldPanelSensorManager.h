#pragma once
#include "AUISensorManager.h"
class AUIWorldPanelSensorManager : public AUISensorManager
{
public:
    AUIWorldPanelSensorManager() {}
    virtual ~AUIWorldPanelSensorManager() {}
    virtual AUICoordSpace TargetCoordSpace() { return AUICoordSpace::kWorldPanel; }

    virtual void OnUpdateBuffers();
    virtual void OnCameraChanged();
    virtual void OnCheckSensors();
    virtual void OnUpdateSensor(size_t sensor_idx, size_t widget_idx);


private:
    struct TBoundingCircle {
        glm::vec2 c;
        float r;
    };
    std::vector<TBoundingCircle> m_aBoundingCircle;

    std::vector<glm::vec2> m_aScreenPos;
    std::vector<bool> m_aInScreen;


    std::vector<AUIWidget*> m_aHitWidget;

    glm::mat4 m_matProj = glm::mat4(1.f);
    glm::mat4 m_matView = glm::mat4(1.f);
    glm::vec4 m_viewport;
};