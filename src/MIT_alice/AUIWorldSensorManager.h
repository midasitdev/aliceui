#pragma once
#include "AUISensorManager.h"
class AUIWorldSensorManager : public AUISensorManager
{
public:
    AUIWorldSensorManager() {}
    virtual ~AUIWorldSensorManager() {}
    virtual AUICoordSpace TargetCoordSpace() { return AUICoordSpace::kWorld; }

    virtual void OnUpdateBuffers();


    virtual void OnCameraChanged();
    virtual void OnCheckSensors();
    virtual void OnUpdateSensor(size_t sensor_idx, size_t widget_idx);


private:
    void UpdateBoundingCircle();

    void UpdateBoundingCircle(size_t i);

    struct TBoundingSphere {
        glm::vec3 c;
        float r;
    };
    std::vector<TBoundingSphere> m_aBoundingSphere;


    struct TBoundingCircle {
        glm::vec2 c;
        float r;
    };
    std::vector<float> m_aScale;
    std::vector<TBoundingCircle> m_aBoundingCircle;
    std::vector<bool> m_aInScreen;


    std::vector<AUIWidget*> m_aHitWidget;


    glm::mat4 m_matProj = glm::mat4(1.f);
    glm::mat4 m_matView = glm::mat4(1.f);
    glm::vec4 m_viewport;
};