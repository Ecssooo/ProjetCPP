#include "Font.h"
#include "Windows.h"

std::string GetFont() {
    char cExeFilePath[256];
    GetModuleFileNameA(NULL, cExeFilePath, 256);
    std::string exeFilePath = cExeFilePath;
    int exeNamePos = exeFilePath.find_last_of("\\/");
    std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
    std::cout << appPath + "\Assets\\ARIAL.TTF" << std::endl;
    return appPath + "\\Assets";
}