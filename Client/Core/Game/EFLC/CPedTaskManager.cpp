/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CPedTaskManager.h"
#include <CCore.h>
#include "CPed.h"
extern CCore * g_pCore;

_GAME_BEGIN

CPedTaskManager::CPedTaskManager(IPedTaskManager * pPedTaskManager, CPed * pPed) :
	m_pPedTaskManager(pPedTaskManager), 
	m_pPed(pPed)
{
}

void CPedTaskManager::SetTask(CTask * pTask, int iType, bool bForceNewTask)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
		{
			((void(__thiscall *) (IPedTaskManager *, ITask *, int, byte))(COffsets::FUNC_CPedTaskManager__SetTaskPriority))(m_pPedTaskManager, pTask ? pTask->GetTask() : nullptr, iType, bForceNewTask);
		}
	}
}

void CPedTaskManager::RemoveTask(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
		{
			// Make sure its not the default task
			if(iType != TASK_PRIORITY_DEFAULT)
				SetTask(nullptr, iType);
		}
	}
}

CTask * CPedTaskManager::GetTask(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
			return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pPedTaskManager->m_pPrimaryTasks[iType]);
	}

	return nullptr;
}

void CPedTaskManager::SetTaskSecondary(CTask * pTask, int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
		{
			((void(__thiscall *) (IPedTaskManager *, ITask *, int))(COffsets::FUNC_CPedTaskManager__SetTaskSecondary))(m_pPedTaskManager, pTask ? pTask->GetTask() : nullptr, iType);
		}
	}
}

void CPedTaskManager::RemoveTaskSecondary(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
			SetTaskSecondary(nullptr, iType);
	}
}

CTask * CPedTaskManager::GetTaskSecondary(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
			return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pPedTaskManager->m_pSecondaryTasks[iType]);
	}

	return nullptr;
}

void CPedTaskManager::SetTaskMovement(CTask * pTask, int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
		{
			((void(__thiscall *) (IPedTaskManager *, ITask *, int))(COffsets::FUNC_CPedTaskManager__SetTaskMovement))(m_pPedTaskManager, pTask ? pTask->GetTask() : nullptr, iType);
		}
	}
}

void CPedTaskManager::RemoveTaskMovment(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
			SetTaskMovement(nullptr, iType);
	}
}

CTask * CPedTaskManager::GetTaskMovement(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
		{
			if(g_pCore->GetGame()->GetTaskManager())
				return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pPedTaskManager->m_pMovementTasks[iType]);
		}
	}

	return nullptr;
}

void CPedTaskManager::ClearTasks(int iAbortPriority)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Clear priority tasks
		for(int i = 0; i < TASK_PRIORITY_MAX; i++)
		{
			CTask * pTask = GetTask(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, nullptr);
		}

		// Clear secondary tasks
		for(int i = 0; i < TASK_SECONDARY_MAX; i++)
		{
			CTask * pTask = GetTaskSecondary(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, nullptr);
		}

		// Clear movement tasks
		for(int i = 0; i < TASK_MOVEMENT_MAX; i++)
		{
			CTask * pTask = GetTaskMovement(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, nullptr);
		}
	}
}

_GAME_END