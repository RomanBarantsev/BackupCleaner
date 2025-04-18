#include "MainWindow.h"
#include <Windows.h>
#include "Cleaner.h"
#include "TaskManager.h"

#include "resource.h"

using namespace BackupCleaner;

[STAThread]
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {    
    CreateScheduledTask();
    std::wstring arg = pCmdLine;
    if (arg == L"1") {         
        StoreData storeDt = StoreData();
        auto data = storeDt.GetData();
        for (const auto& [first, second] : data) {
            Cleaner cl(first, second->daysToStore, second->countFiles, second->folderSize);
        }
        return 0;
    }
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Application::Run(gcnew MainWindow());    
    return 0;
}