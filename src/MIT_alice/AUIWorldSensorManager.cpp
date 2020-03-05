#include "pch.h"
#include "AUIWorldSensorManager.h"
#include "AUIWidgetManager.h"
#include "AUIWidget.h"
#include "AUIInstance.h"
#include "AUIWidgetRootInfo.h"

void AUIWorldSensorManager::OnUpdateBuffers()
{
    auto& aSensors = SensorBuffer();
    auto sensorSize = aSensors.size();
    m_aBoundingCircle.resize(sensorSize);
    m_aBoundingSphere.resize(sensorSize);
    m_aInScreen.resize(sensorSize);
    m_aScale.resize(sensorSize);

    auto& aWidgets = WidgetBuffer();
    auto widgetSize = aWidgets.size();
    UpdateBoundingCircle();


}

void AUIWorldSensorManager::UpdateBoundingCircle()
{
    auto& aSensors = SensorBuffer();
    auto sensorSize = aSensors.size();


    std::fill(m_aInScreen.begin(), m_aInScreen.end(), true);
    for (auto i = 0; i < sensorSize; i++)
    {
        UpdateBoundingCircle(i);
    }

}

void AUIWorldSensorManager::UpdateBoundingCircle(size_t i)
{
    auto& aWidgets = WidgetBuffer();
    auto& bs = m_aBoundingSphere[i];
    auto& bc = m_aBoundingCircle[i];
    auto widgetIdx = Sensor2Widget(i);


    auto pWidget = aWidgets[widgetIdx];
    auto root_coord = pWidget->GetRootCoordInfo();
    auto& matRoot = root_coord->GetMatrix();


    auto pos = glm::vec3(matRoot[3]) + bs.c;
    auto sPos = glm::project(pos, m_matView, m_matProj, m_viewport);

    bc.c.x = sPos.x;
    bc.c.y = m_viewport[3] - sPos.y - 1.0f;
    float fScale = 2.0f / m_matProj[1][1];
    float fViewLen = glm::min(m_viewport[2], m_viewport[3]);
    fScale /= fViewLen;
    m_aScale[i] = fScale;

    if (m_matProj[3][2] != 0.f)
    {
        float fEyeZ = m_matProj[0][2] * pos[0] + m_matView[1][2] * pos[1] + m_matView[2][2] * pos[2] + m_matView[3][2];
        fScale *= -fEyeZ;
    }

    bc.r = bs.r / fScale;

    if (
        m_viewport[0] > bc.c.x + bc.r ||
        m_viewport[1] > bc.c.y + bc.r ||
        m_viewport[0] + m_viewport[2] < bc.c.x - bc.r ||
        m_viewport[1] + m_viewport[3] < bc.c.y - bc.r)
        m_aInScreen[i] = false;
}

void AUIWorldSensorManager::OnCameraChanged()
{
    auto pWidgetManager = GetWidgetManager();
    m_matView = pWidgetManager->GetViewingMatrix();
    m_matProj = pWidgetManager->GetProjectionMatrix();
    m_viewport = pWidgetManager->GetViewport();


    UpdateBoundingCircle();

}

void AUIWorldSensorManager::OnUpdateSensor(size_t sensor_idx, size_t widget_idx)
{
    auto& aSensors = SensorBuffer();
    auto pSensor = aSensors[sensor_idx];
    auto& bs = m_aBoundingSphere[sensor_idx];
    pSensor->GetBoundingSphere(bs.c, bs.r);
    UpdateBoundingCircle(sensor_idx);
}

void AUIWorldSensorManager::OnCheckSensors()
{
    auto pWidgetManager = GetWidgetManager();
    auto vMousePos = glm::vec2(pWidgetManager->GetMousePos());

    auto& aSensors = SensorBuffer();


    auto sensorSize = aSensors.size();
    std::vector<bool> aSensorHit;
    aSensorHit = m_aInScreen;


    for (auto i = 0; i < sensorSize; i++)
    {
        if (aSensorHit[i] == false)
            continue;

        auto& bc = m_aBoundingCircle[i];
        auto widgetIdx = Sensor2Widget(i);

        auto l = glm::length(vMousePos - (bc.c));

        if (l > bc.r)
            aSensorHit[i] = false;
    }



    auto& aInstances = InstanceBuffer();
    auto& aWidgets = WidgetBuffer();
    auto& aHitBuff = HitBuffer();


    std::fill(aHitBuff.begin(), aHitBuff.end(), false);
    //aHit.data()

    glm::vec3 vLocalDir(0.0f, 0.0f, -1.0f);

    for (auto i = 0; i < sensorSize; i++)
    {
        if (!aSensorHit[i])
            continue;
        auto buffidx = Sensor2Widget(i);
        auto pInstance = aInstances[buffidx].lock().get();
        if (!pInstance)
            continue;

        auto root_coord = aWidgets[buffidx]->GetRootCoordInfo();
        auto coord = root_coord->GetTargetCoord();
        auto& matRoot = root_coord->GetMatrix();

        auto matInv = glm::inverse(matRoot);
        const glm::vec3 vLocalOrg(matInv * glm::vec4(GetWidgetManager()->GetMouseOrg(), 1));
        vLocalDir = glm::normalize(glm::vec3(matInv * glm::vec4(GetWidgetManager()->GetMouseDir(), 0)));

        auto pSensor = aSensors[i];
        bool bHit = pSensor->UpdateHit(vLocalOrg, vLocalDir, m_aScale[i]);
        if (bHit)
        {
            pInstance->SetHit(pSensor->GetHitDistance());
            aHitBuff[buffidx] = true;
        }
    }
}
