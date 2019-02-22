#include "pch.h"
#include "AUILazyTask.h"

void AUILazyTask::Execute()
{
    OnExecute();
    m_bExecuted = true;
}
