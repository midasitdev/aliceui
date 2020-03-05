#include "pch.h"
#include "AUIWorldPanelSensorManager.h"
#include "AUIWidgetManager.h"
#include "AUIWidget.h"
#include "AUIInstance.h"
#include "AUIWidgetRootInfo.h"

void AUIWorldPanelSensorManager::OnUpdateBuffers()
{
    auto& aSensors = SensorBuffer();
    auto sensorSize = aSensors.size();
    m_aBoundingCircle.resize(sensorSize);
    m_aInScreen.resize(sensorSize);

    auto& aWidgets = WidgetBuffer();
    auto widgetSize = aWidgets.size();
    m_aScreenPos.resize(widgetSize);

    for (auto i = 0; i < widgetSize; i++)
    {
        auto pWidget = aWidgets[i];
        auto root_coord = pWidget->GetRootCoordInfo();
        auto& matRoot = root_coord->GetMatrix();
        auto sPos = glm::project(glm::vec3(matRoot[3]), m_matView, m_matProj, m_viewport);
        auto& sc = m_aScreenPos[i];
        sc.x = sPos.x;
        sc.y = m_viewport[3] - sPos.y - 1.0f;
    }


    std::fill(m_aInScreen.begin(), m_aInScreen.end(), true);
    for (auto i = 0; i < sensorSize; i++)
    {
        auto& bc = m_aBoundingCircle[i];
        auto widgetIdx = Sensor2Widget(i);
        auto sc = m_aScreenPos[widgetIdx];

        auto p = bc.c + sc;
        if (
            m_viewport[0] > p.x + bc.r ||
            m_viewport[1] > p.y + bc.r ||
            m_viewport[0] + m_viewport[2] < p.x - bc.r ||
            m_viewport[1] + m_viewport[3] < p.y - bc.r)
            m_aInScreen[i] = false;
     }


}

void AUIWorldPanelSensorManager::OnCameraChanged()
{
    auto pWidgetManager = GetWidgetManager();
    m_matView = pWidgetManager->GetViewingMatrix();
    m_matProj = pWidgetManager->GetProjectionMatrix();
    m_viewport = pWidgetManager->GetViewport();

    auto& aWidgets = WidgetBuffer();
    auto widgetSize = aWidgets.size();

    for (auto i = 0; i < widgetSize; i++)
    {
        auto pWidget = aWidgets[i];
        auto root_coord = pWidget->GetRootCoordInfo();
        auto& matRoot = root_coord->GetMatrix();

        auto sPos = glm::project(glm::vec3(matRoot[3]), m_matView, m_matProj, m_viewport);
        auto& sc = m_aScreenPos[i];
        sc.x = sPos.x;
        sc.y = m_viewport[3] - sPos.y - 1.0f;
    }


    std::fill(m_aInScreen.begin(), m_aInScreen.end(), true);
    auto sensorSize = m_aBoundingCircle.size();
    for (auto i = 0; i < sensorSize; i++)
    {
        auto& bc = m_aBoundingCircle[i];
        auto widgetIdx = Sensor2Widget(i);
        auto sc = m_aScreenPos[widgetIdx];

        auto p = bc.c + sc;
        if (
            m_viewport[0] > p.x - bc.r ||
            m_viewport[1] > p.y - bc.r ||
            m_viewport[0] + m_viewport[2] < p.x + bc.r ||
            m_viewport[1] + m_viewport[3] < p.y + bc.r)
            m_aInScreen[i] = false;
    }

}

void AUIWorldPanelSensorManager::OnUpdateSensor(size_t sensor_idx, size_t widget_idx)
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

void AUIWorldPanelSensorManager::OnCheckSensors()
{
    auto pWidgetManager = GetWidgetManager();
    auto vMousePos = glm::vec2(pWidgetManager->GetMousePos());

    auto& aSensors = SensorBuffer();


    auto sensorSize = aSensors.size();
    std::vector<bool> aSensorHit;
    aSensorHit = m_aInScreen;

#pragma omp for simd
    for (auto i = 0; i < sensorSize; i++)
    {
        if(aSensorHit[i] == false)
            continue;

        auto& bc = m_aBoundingCircle[i];
        auto widgetIdx = Sensor2Widget(i);
        auto sc = m_aScreenPos[widgetIdx];

        auto l = glm::length(vMousePos - ( bc.c + sc ));

        if (l > bc.r)
            aSensorHit[i] = false;
    }



    auto& aInstances = InstanceBuffer();
    auto& aHitBuff = HitBuffer();


    std::fill(aHitBuff.begin(), aHitBuff.end(), false);
    //aHit.data()

    glm::vec3 vLocalDir;
    vLocalDir.x = 0.0f;
    vLocalDir.y = 0.0f;
    vLocalDir.z = -1.0f;

    for (auto i = 0; i < sensorSize; i++)
    {
        if (!aSensorHit[i])
            continue;
        auto buffidx = Sensor2Widget(i);
        auto pInstance = aInstances[buffidx].lock().get();
        if (!pInstance)
            continue;


        auto sc = m_aScreenPos[buffidx];
        glm::vec3 vLocalOrg;
        vLocalOrg.x = static_cast<float>(vMousePos.x) - sc.x;
        vLocalOrg.y = static_cast<float>(vMousePos.y) - sc.y;
        vLocalOrg.z = -10000.f;

        auto pSensor = aSensors[i];
        bool bHit = pSensor->UpdateHit(vLocalOrg, vLocalDir);
        if (bHit)
        {
            pInstance->SetHit(pSensor->GetHitDistance());
            aHitBuff[buffidx] = true;
        }
    }
}
