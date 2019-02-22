#pragma once

#include "AUIAPIDef.h"

#include <memory>

class ALICEUI_API AUILazyTask : public std::enable_shared_from_this<AUILazyTask>
{
protected:
    AUILazyTask() = default;
public:
    virtual ~AUILazyTask() = default;

    //////////////////////////////////////////////////////////////////////////
    // Run
public:
    void Execute();
    bool IsExecuted() const noexcept {
        return m_bExecuted;
    }
protected:
    virtual void OnExecute() = 0;
private:
    bool m_bExecuted = false;
};
