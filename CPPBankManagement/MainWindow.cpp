#include "MainWindow.h"
#include <AppCore/JSHelpers.h>
using namespace ultralight;

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400

MainWindow::MainWindow() {
    app_ = App::Create();
    window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
        false, kWindowFlags_Titled | kWindowFlags_Resizable);
    window_->SetTitle("银行管理系统");
    app_->set_window(*window_.get());
    overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);
    OnResize(window_->width(), window_->height());
    overlay_->view()->LoadURL("file:///main_window.html");
    app_->set_listener(this);
    window_->set_listener(this);
    overlay_->view()->set_load_listener(this);
}

MainWindow::~MainWindow() {
}

void MainWindow::Run() {
    app_->Run();
}

void MainWindow::OnUpdate() {
}

void MainWindow::OnClose() {
}

void MainWindow::OnResize(uint32_t width, uint32_t height) {
    overlay_->Resize(width, height);
}

void MainWindow::OnFinishLoading(View* caller) {
}

void MainWindow::OnDOMReady(View* caller) {
    SetJSContext(caller->js_context());
    JSObject global = JSGlobalObject();

    //绑定C++方法到前端
    global["GetMessage"] = BindJSCallbackWithRetval(&MainWindow::GetMessage);
}

JSValue MainWindow::GetMessage(const JSObject& thisObject, const JSArgs& args) {
    
    
    return JSValue("Hello 1");
}
