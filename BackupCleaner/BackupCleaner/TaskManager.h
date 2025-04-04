#pragma once

#include <windows.h>
#include <taskschd.h>
#include <iostream>
#include <comutil.h>  
#include <thread>
#include <comdef.h>
#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "comsuppw.lib")

const std::string taskName="BackupCleaner";

std::string CreateScheduledTask() {
    std::thread([]() {
        HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
        if (hr == RPC_E_CHANGED_MODE) {
            return "COM already initialized in a different mode!";
        }
        if (FAILED(hr)) {
            return "Failed to initialize COM library.\n";
        }

        // task manager instance
        ITaskService* pService = nullptr;
        hr = CoCreateInstance(CLSID_TaskScheduler, NULL, CLSCTX_INPROC_SERVER, IID_ITaskService, (void**)&pService);
        if (FAILED(hr)) {
            CoUninitialize();
            return "Failed to create Task Service instance.\n";

        }

        // connecting to task manager
        hr = pService->Connect(_variant_t(), _variant_t(), _variant_t(), _variant_t());
        if (FAILED(hr)) {
            pService->Release();
            CoUninitialize();
            return "Failed to connect to Task Scheduler.\n";
        }

        // getting root folder
        ITaskFolder* pRootFolder = nullptr;
        hr = pService->GetFolder(_bstr_t(L"\\"), &pRootFolder);
        if (FAILED(hr)) {
            pService->Release();
            CoUninitialize();
            return "Failed to get Task Scheduler root folder.\n";
        }

        // checking for existing task
        IRegisteredTask* existTask = nullptr;
        hr = pRootFolder->GetTask(_bstr_t(taskName.c_str()), &existTask);
        if (SUCCEEDED(hr)) {
            pRootFolder->DeleteTask(_bstr_t(taskName.c_str()),0);
        }        

        // creating new task 
        ITaskDefinition* pTask = nullptr;
        hr = pService->NewTask(0, &pTask);
        if (FAILED(hr)) {
            pRootFolder->Release();
            pService->Release();
            CoUninitialize();
            return  "Failed to create a new task.\n";
        }

        // common settings
        IRegistrationInfo* pRegInfo = nullptr;
        pTask->get_RegistrationInfo(&pRegInfo);
        pRegInfo->put_Author(_bstr_t(L"User"));
        pRegInfo->Release();

        // trigger setting
        ITriggerCollection* pTriggerCollection = nullptr;
        pTask->get_Triggers(&pTriggerCollection);
        ITrigger* pTrigger = nullptr;
        hr = pTriggerCollection->Create(TASK_TRIGGER_DAILY, &pTrigger);
        if (FAILED(hr)) {
            pTriggerCollection->Release();
            pTask->Release();
            pRootFolder->Release();
            pService->Release();
            CoUninitialize();
            return "Failed to create trigger.\n";
        }

        //set time of executing
        IDailyTrigger* pDailyTrigger = nullptr;
        pTrigger->QueryInterface(IID_IDailyTrigger, (void**)&pDailyTrigger);
        pDailyTrigger->put_DaysInterval(1);
        pDailyTrigger->put_StartBoundary(_bstr_t(L"2025-03-26T00:00:00"));
        pDailyTrigger->Release();
        pTrigger->Release();
        pTriggerCollection->Release();

        // action creating - executing .exe file
        IActionCollection* pActionCollection = nullptr;
        pTask->get_Actions(&pActionCollection);
        IAction* pAction = nullptr;
        hr = pActionCollection->Create(TASK_ACTION_EXEC, &pAction);
        if (FAILED(hr)) {
            pActionCollection->Release();
            pTask->Release();
            pRootFolder->Release();
            pService->Release();
            CoUninitialize();
            return "Failed to create action.\n";
        }

        // set argument and work folder
        IExecAction* pExecAction = nullptr;
        pAction->QueryInterface(IID_IExecAction, (void**)&pExecAction);        
        wchar_t exePath[MAX_PATH];
        GetModuleFileNameW(NULL, exePath, MAX_PATH);
        pExecAction->put_Path(_bstr_t(exePath));
        BSTR bs = SysAllocString(L"1");
        pExecAction->put_Arguments(bs);
        std::wstring workingDir = std::filesystem::path(exePath).parent_path().wstring();
        pExecAction->put_WorkingDirectory(_bstr_t(workingDir.c_str()));
        pExecAction->Release();
        pAction->Release();
        pActionCollection->Release();

        //set start when available
        ITaskSettings* pSettings = nullptr;
        hr = pTask->get_Settings(&pSettings);
        if (SUCCEEDED(hr)) {
            hr = pSettings->put_StartWhenAvailable(VARIANT_TRUE);
            pSettings->Release();
        }

        // saving task to task manager
        IRegisteredTask* pRegisteredTask = nullptr;
        hr = pRootFolder->RegisterTaskDefinition(_bstr_t(taskName.c_str()), pTask, TASK_CREATE_OR_UPDATE, _variant_t(L""), _variant_t(L""), TASK_LOGON_INTERACTIVE_TOKEN, _variant_t(L""), &pRegisteredTask);
        if (SUCCEEDED(hr)) {
            return "Task created successfully.\n";
        }
        else {
            return "Failed to register task.\n";
        }

        pRegisteredTask->Release();
        pTask->Release();
        pRootFolder->Release();
        pService->Release();
        CoUninitialize();
		}).detach();
		return "Success";
}
