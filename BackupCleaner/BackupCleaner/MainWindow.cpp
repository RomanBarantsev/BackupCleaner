#include "MainWindow.h"
#include <Windows.h>

using namespace BackupCleaner;

int WINAPI WinMain(HINSTANCE ,HINSTANCE, LPSTR, int) {
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Application::Run(gcnew MainWindow());
    return 0;
}