#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//����ʾ����̨

#include "MainWindow.h"

int main() {
    MainWindow app;
    app.Run();

    return 0;
}
