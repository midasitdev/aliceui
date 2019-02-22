#pragma once

#include "AUIAPIDef.h"

#include <memory>
#include <mutex>
#include <vector>

class AUILazyTask;

class ALICEUI_API AUILazyTaskManager
{
public:
    AUILazyTaskManager() = default;
    virtual ~AUILazyTaskManager() = default;


    //////////////////////////////////////////////////////////////////////////
    // Run Task
public:
    void RunTasks();
protected:
    virtual void OnPreRunTasks();
    virtual void OnRunTasks(const std::shared_ptr<AUILazyTask>& pTask);


    //////////////////////////////////////////////////////////////////////////
    // Task queue
public:
    size_t GetTaskCount() const;
    void PushTask(const std::shared_ptr<AUILazyTask>& pTask);
protected:
    std::vector<std::shared_ptr<AUILazyTask>> m_Tasks;
    mutable std::recursive_mutex m_mtxTasks;
};
