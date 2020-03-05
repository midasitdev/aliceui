#include "pch.h"
#include "AUIScreenSensorManager.h"
#include "AUIWidgetManager.h"
#include "AUIWidget.h"
#include "AUIInstance.h"
void AUIScreenSensorManager::OnUpdateBuffers()
{
    auto& aSensors = SensorBuffer();
    auto sensorSize = aSensors.size();
    m_aBoundingCircle.resize(sensorSize);

}

void AUIScreenSensorManager::OnCameraChanged()
{

}

void AUIScreenSensorManager::OnUpdateSensor(size_t sensor_idx, size_t widget_idx)
{
    auto& aSensors = SensorBuffer();
    auto pSensor = aSensors[sensor_idx];
    auto& bc = m_aBoundingCircle[sensor_idx];
    glm::vec3 c(0.f);
    float r = 0.f;
    pSensor->GetBoundingSphere(c, r);
    bc.c = glm::vec2(c);
    bc.r = r;
}

void AUIScreenSensorManager::OnCheckSensors()
{
    auto pWidgetManager = GetWidgetManager();
    auto vMousePos = glm::vec2(pWidgetManager->GetMousePos());

    auto& aSensors = SensorBuffer();


    auto sensorSize = aSensors.size();
    std::vector<bool> aSensorHit;
    aSensorHit.resize(sensorSize, true);

    for (auto i = 0; i < sensorSize; i++)
    {
        auto& bc = m_aBoundingCircle[i];

        auto l = glm::length(vMousePos - bc.c);

        if (l > bc.r)
            aSensorHit[i] = false;
    }

    const glm::vec3 vLocalOrg(vMousePos.x, vMousePos.y, -10000.f);
    const glm::vec3 vLocalDir(0.0f, 0.0f, -1.0f);

    auto& aInstances = InstanceBuffer();
    auto& aHitBuff = HitBuffer();

    std::fill(aHitBuff.begin(), aHitBuff.end(), false);
    //aHit.data()

    for (auto i = 0; i < sensorSize; i++)
    {
        if (!aSensorHit[i])
            continue;
        auto buffidx = Sensor2Widget(i);
        auto pInstance = aInstances[buffidx].lock().get();
        if(!pInstance)
            continue;

        auto pSensor = aSensors[i];
        bool bHit = pSensor->UpdateHit(vLocalOrg, vLocalDir);
        if (bHit)
        {
            pInstance->SetHit(pSensor->GetHitDistance());
            aHitBuff[buffidx] = true;
        }
    }
}
