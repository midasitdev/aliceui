#include "pch.h"
#include "AUISensorManager.h"
#include "AUIWidgetManager.h"
#include "AUIInstance.h"
#include "AUIWidget.h"
#include "AUIWidgetRootInfo.h"
#include "AUIApplication.h"
#include "AUIWidgetTreeHelper.h"


void AUISensorManager::_update_buffer()
{
    std::vector<std::shared_ptr<AUIInstance>> aInstances;
    m_pWidgetManager->GetInstances(aInstances);


    m_aInstances.clear();
    m_aWidgets.clear();
    m_aInstances.reserve(aInstances.size());
    m_aWidgets.reserve(aInstances.size());

    auto target_coord = TargetCoordSpace();
    m_mapWidgetIdx.clear();

    for (auto pInstance : aInstances)
    {
        auto pWidget = pInstance->GetWidget();
        
        auto root_info = pWidget->GetRootCoordInfo();
        auto root_target_coord = root_info->GetTargetCoord();
        if( root_target_coord != target_coord)
            continue;

        m_aInstances.push_back(pInstance);
        m_aWidgets.push_back(pWidget);

    }

    auto widget_size = m_aWidgets.size();
    m_aHitTest.resize(widget_size);
    std::fill(m_aHitTest.begin(), m_aHitTest.end(), true);
    m_aHit.resize(widget_size);

    const auto& widgettree = AUIApplication::Instance().GetWidgetTree();
    for (auto i = 0; i< widget_size;i++)
    {
        auto pWidget = m_aWidgets[i];
        m_mapWidgetIdx[pWidget] = i;
        if( 
            pWidget->HasHitTest() == false ||
            pWidget->GetSensors().size() == 0 ||  //여기 있어도 되나..? 실시간으로 바뀌나?
            widgettree.IsVisibleByParent(pWidget) == false)  //여기 있어도 되나..? 실시간으로 바뀌나?
            m_aHitTest[i] = false;
    }
    
    m_aSensor.clear();
    m_aWidget2SensorIdx.resize(widget_size);

    //////////////////////////////////////////////////////////////////////////
    // Sensor Buffer에 대한 Index 계산
    //////////////////////////////////////////////////////////////////////////

    for (auto i = 0; i < widget_size ; i++)
    {
        auto pWidget = m_aWidgets[i];
        auto bHitTest = m_aHitTest[i];

        if (!bHitTest)
            continue;

        const auto& aSensors = pWidget->GetSensors();

        auto o = m_aSensor.size();
        auto sensorSize = aSensors.size();
        auto newSize = o + sensorSize;
        m_aSensor.resize(newSize);
        m_aSensor2WidgetIdx.resize(newSize);
        m_aWidget2SensorIdx[i] = o;

        for (auto j = 0; j < sensorSize; j++)
        {
            m_aSensor[j + o] = aSensors[j].get();
            m_aSensor2WidgetIdx[j + o] = i;
        }
    }



    OnUpdateBuffers();
    auto sensorSize = m_aSensor.size();
    for (auto i = 0; i < sensorSize; i++)
    {
        OnUpdateSensor(i,m_aSensor2WidgetIdx[i]);
    }


}

void AUISensorManager::_update_sensor()
{

    std::set<AUIWidget*> setUpdated;

   decltype(m_ChangedSensorWidget) sSensorWidget;
   {
       std::lock_guard< std::recursive_mutex > guard(m_mtxBuffer);
       sSensorWidget = m_ChangedSensorWidget;
       m_ChangedSensorWidget.clear();
   }

    for (auto wpWidget : sSensorWidget)
    {
        auto pWidget = wpWidget.lock().get();
        if (!pWidget)
            continue;
        if(setUpdated.find(pWidget) != setUpdated.end())
            continue;

        setUpdated.insert(pWidget);

        auto itr = m_mapWidgetIdx.find(pWidget);
        if (itr == m_mapWidgetIdx.end())
            continue;

        auto widget_idx = itr->second;
        auto bHitTest = m_aHitTest[widget_idx];
        if (!bHitTest)
            continue;

        auto sensor_idx_start = Widget2Sensor(widget_idx);
        auto sensor_idx_end = sensor_idx_start + pWidget->GetSensors().size();

        for (auto i = sensor_idx_start; i < sensor_idx_end; i++)
            OnUpdateSensor(i, widget_idx);
    }
}

void AUISensorManager::_invalidate_sensor(std::weak_ptr<AUIWidget> pWidget)
{
    m_ChangedSensorWidget.emplace_back(std::move( pWidget ));
    m_bInvalidateSensor = true;
}

bool AUISensorManager::CheckSensors()
{
    if (m_bInvalidateSensor && !m_bInvalidateBuffer)    //widget buffer 갱신시, 어차피 모두 갱신됨.
    {
        _update_sensor();
        m_bInvalidateSensor = false;
    }
    if (m_bInvalidateBuffer)
    {
        _update_buffer();
        m_bInvalidateBuffer = false;
    }
    if (m_bInvalidateCamera)
    {
        OnCameraChanged();
        m_bInvalidateCamera = false;
    }

    OnCheckSensors();


    auto buff_size = m_aInstances.size();
    m_aHitInstance.clear();
    m_aHitInstance.reserve(buff_size);
    for (auto i = 0; i < buff_size; i++)
        if (m_aHit[i])
            m_aHitInstance.push_back(m_aInstances[i]);

    return m_aHitInstance.size() > 0;
}
