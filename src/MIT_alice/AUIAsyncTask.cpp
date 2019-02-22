#include "pch.h"
#include "AUIAsyncTask.h"
#include "AUIApplication.h"

AUIAsyncTask::AUIAsyncTask()
{
    m_iProgressValue = 0;
    m_isPublishedProgress = false;
    m_isCancelled = false;

}

bool AUIAsyncTask::IsRunning() const
{
    return m_bRunning;
}

bool AUIAsyncTask::Execute()
{
    if ( IsRunning() )
        return false;

    m_isCancelled.store(false, std::memory_order_release);

    std::packaged_task< int() > task( std::bind( &AUIAsyncTask::RunThread, this ) );
    m_thisFuture = task.get_future();

    this->OnPreExecute();

    AUIApplication::Instance().AsyncExecute(shared_from_this());

    m_bRunning = true;

    std::thread _thread(std::move(task));
    _thread.detach();

    return true;
}

int AUIAsyncTask::RunThread()
{
    this->OnBackgroundThread();

    m_bRunning = false;

    AUIApplication::Instance().PostLazyUpdate();

    return 0;
}

void AUIAsyncTask::PublishProgress( int val )
{
    m_iProgressValue = val;
    m_isPublishedProgress.store(true, std::memory_order_release);

    AUIApplication::Instance().PostLazyUpdate();
}

void AUIAsyncTask::ProgressUpdate()
{
    m_isPublishedProgress.store(false, std::memory_order_release);

    this->OnProgressUpdate();
}

int AUIAsyncTask::GetProgressValue() const
{
    return m_iProgressValue.load(std::memory_order_acquire);
}

bool AUIAsyncTask::IsPublishedProgress() const
{
    return m_isPublishedProgress.load(std::memory_order_acquire);
}

void AUIAsyncTask::PostExecute()
{
    this->OnPostExecute();
}

bool AUIAsyncTask::IsCancelled() const
{
    return m_isCancelled.load(std::memory_order_acquire);
}

void AUIAsyncTask::Cancel()
{
    m_isCancelled.store(true, std::memory_order_release);
}

void AUIAsyncTask::Cancelled()
{
    this->OnCancelled();
}
