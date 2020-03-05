#pragma once
#include "AUIBasicEnumDef.h"
#include "AUISensor.h"


#include <set>

//struct THitBuffer
//{
//
//    bool fHit;
//    std::weak_ptr<AUISensor>   fHitSensor;
//    std::weak_ptr<AUIInstance> fInstance;
//};
class AUIWidgetManager;
class AUIInstance;
class AUIWidget;
enum class AUICoordSpace;

struct THitBuffer
{
    bool fHit;
    std::weak_ptr<AUIWidget> fWidget;
};


struct HitBufferData
{
    float fDistance = 0.0f;
    std::weak_ptr<AUIInstance> fInstance;

    HitBufferData(const float dist, std::weak_ptr<AUIInstance>  inst) noexcept : fDistance(dist), fInstance(inst) {}

    HitBufferData() noexcept = default;
    HitBufferData(const HitBufferData&) noexcept = default;
    HitBufferData(HitBufferData&&) noexcept = default;
    HitBufferData& operator=(const HitBufferData&) noexcept = default;
    HitBufferData& operator=(HitBufferData&&) noexcept = default;

};

class ALICEUI_API AUISensorManager
{
public:
    AUISensorManager() {}
    virtual ~AUISensorManager() {}


    virtual AUICoordSpace TargetCoordSpace() = 0;
    virtual void OnCameraChanged() = 0;
    virtual void OnCheckSensors() = 0;
    virtual void OnUpdateBuffers() = 0;
    virtual void OnUpdateSensor(size_t sensor_idx, size_t widget_idx) = 0;


    void _invalidate_buffer()
    {
        m_bInvalidateBuffer = true;
    }
    void _update_buffer();
    void _update_sensor();
    void _invalidate_sensor(std::weak_ptr<AUIWidget> wpSensor);
    void _invliadate_camera()
    {
        m_bInvalidateCamera = true;

    }

    bool CheckSensors();

private:
    bool m_bInvalidateBuffer = true;
    bool m_bInvalidateSensor = true;
    bool m_bInvalidateCamera = true;


    //const HitBufferData& GetHitData() const
    //{
    //    return m_hit;
    //}
public:
    void SetWidgetManager(AUIWidgetManager* pWidgetManager) { m_pWidgetManager = pWidgetManager; }
protected:
    AUIWidgetManager* GetWidgetManager() const { return m_pWidgetManager; }
private:
    AUIWidgetManager* m_pWidgetManager;
public:



     std::vector< std::weak_ptr<AUIInstance> >& InstanceBuffer()  { return m_aInstances; }
     std::vector< AUIWidget* >& WidgetBuffer()  { return m_aWidgets; }
     std::vector< bool >& HitTestBuffer()  { return m_aHitTest; }
     std::vector< bool >& HitBuffer()  { return m_aHit; }
    //const std::vector< size_t>& Widget2SensorIdxBuffer() const { return m_aWidget2SensorIdx; }
    //const std::vector< size_t>& Sensor2WidgetIdxBuffer() const { return m_aSensor2WidgetIdx; }

    const std::vector< AUISensor* >& SensorBuffer() const { return m_aSensor; }
    //size_t SensorBufferSize()const { return m_SensorSize;}

    const inline size_t Widget2Sensor(size_t idx) {
        return m_aWidget2SensorIdx[idx];
    }
    const inline size_t Sensor2Widget(size_t idx) {
        return m_aSensor2WidgetIdx[idx];
    }
    //const inline size_t WidgetIdx(AUIWidget* pWidget)
    //{
    //    auto itr = m_mapWidgetIdx.find(pWidget);
    //    if (itr == m_mapWidgetIdx.end())
    //        return -1;
    //    return itr->second;
    //}

private:
    mutable std::recursive_mutex m_mtxBuffer;
    std::vector<std::weak_ptr<AUIWidget>> m_ChangedSensorWidget;
    std::vector< std::weak_ptr<AUIInstance> > m_aInstances;
    std::vector< AUIWidget* > m_aWidgets;
    std::vector< bool > m_aHitTest;
    std::vector< bool > m_aHit;

    std::vector< AUISensor* > m_aSensor;
    std::vector< size_t > m_aWidget2SensorIdx;
    std::vector< size_t > m_aSensor2WidgetIdx;
    std::map<AUIWidget*, size_t > m_mapWidgetIdx;
    //size_t m_SensorSize;

public:
    const std::vector< std::weak_ptr<AUIInstance> >& HitInstances() const { return m_aHitInstance; }
private:
    std::vector< std::weak_ptr<AUIInstance> > m_aHitInstance;


    //std::unordered_set<AUIWidget*> setVisualHitTrue;
    //std::unordered_set<AUIWidget*> setVisualHitFalse;
};