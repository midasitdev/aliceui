#include "pch.h"
#include "AUILazyTaskManager.h"
#include "AUILazyTask.h"

void AUILazyTaskManager::RunTasks()
{
    OnPreRunTasks();

    std::vector<std::shared_ptr<AUILazyTask>> arrTasks;
    do
    {
        std::lock_guard< std::recursive_mutex > _guard(m_mtxTasks);
        arrTasks = std::move(m_Tasks);
    } while (false);

    for (const auto& task : arrTasks)
    {
        OnRunTasks(task);
    }
}

void AUILazyTaskManager::OnPreRunTasks()
{
    // Implement here
}

void AUILazyTaskManager::OnRunTasks(const std::shared_ptr<AUILazyTask>& pTask)
{
    AUIAssert(pTask->IsExecuted() == false);
    pTask->Execute();
}

size_t AUILazyTaskManager::GetTaskCount() const
{
    std::lock_guard<std::recursive_mutex> _guard(m_mtxTasks);
    return m_Tasks.size();
}

void AUILazyTaskManager::PushTask(const std::shared_ptr<AUILazyTask>& pTask)
{
    std::lock_guard<std::recursive_mutex> _guard(m_mtxTasks);
    m_Tasks.emplace_back(pTask);
}

