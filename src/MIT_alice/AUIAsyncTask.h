#pragma once

#include "AUIAPIDef.h"

#include <memory>
#include <atomic>
#include <thread>
#include <future>

class AUIApplication;

class ALICEUI_API AUIAsyncTask : public std::enable_shared_from_this<AUIAsyncTask>
{
    friend class AUIApplication;
public:
    AUIAsyncTask();
    virtual ~AUIAsyncTask() = default;


    //////////////////////////////////////////////////////////////////////////
    // Thread function
public:
    bool IsRunning() const;
    bool Execute();
protected:
    void PublishProgress(int val);
private:
    int RunThread();
    bool m_bRunning = false;


    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    virtual void OnBackgroundThread() {}    // May not in 'main thread'
    virtual void OnPreExecute() {}          // In 'main thread'
    virtual void OnPostExecute() {}         // In 'main thread'
    virtual void OnProgressUpdate() {}      // In 'main thread'
    virtual void OnCancelled() {}           // In 'main thread'

    //////////////////////////////////////////////////////////////////////////
    // Callback for MAUIApplication
private:
    void ProgressUpdate();
    void PostExecute();
    void Cancelled();


    //////////////////////////////////////////////////////////////////////////
    // Progress
public:
    bool IsPublishedProgress() const;
    int GetProgressValue() const;
private:
    std::atomic_bool m_isPublishedProgress;
    std::atomic_int m_iProgressValue;


    //////////////////////////////////////////////////////////////////////////
    // Cancel
public:
    bool IsCancelled() const;
    void Cancel();
private:
    std::atomic_bool m_isCancelled;
    std::future<int> m_thisFuture;
};
