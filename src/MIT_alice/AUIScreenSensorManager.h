#pragma once
#include "AUISensorManager.h"
class AUIScreenSensorManager : public AUISensorManager
{
public:
    AUIScreenSensorManager() {}
    virtual ~AUIScreenSensorManager() {}
    virtual AUICoordSpace TargetCoordSpace() { return AUICoordSpace::kScreenSpace; }

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
    std::vector<AUIWidget*> m_aHitWidget;

};