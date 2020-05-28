#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//不显示控制台

#include "MainWindow.h"

int main() {
    MainWindow app;
    app.Run();

    return 0;
}
