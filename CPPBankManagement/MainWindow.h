#pragma once
#include "BankAccount.h"
#include "AccountFile.h"
#include "Adapt.h"
#include <AppCore/AppCore.h>
#include <cstdint>

using namespace ultralight;

class MainWindow : public AppListener,
	public WindowListener,
	public LoadListener,
	public ViewListener {
public:
	MainWindow();

	virtual ~MainWindow();
	// 启动窗口
	virtual void Run();
	// 标准窗体事件循环
	virtual void OnUpdate() override;
	// 窗体关闭事件
	virtual void OnClose() override;
	// 窗体大小调整
	virtual void OnResize(uint32_t width, uint32_t height) override;
	// 窗体框架加载
	virtual void OnFinishLoading(View* caller) override;
	// 窗体渲染完成
	virtual void OnDOMReady(View* caller) override;
	// 窗体JavaScript日志处理
	virtual void OnAddConsoleMessage(View* caller, MessageSource source, MessageLevel level, const String& message, uint32_t line_number, uint32_t column_number, const String& source_id) override;
	// 获取账号信息逻辑
	JSValue GetAccount(const JSObject& thisObject, const JSArgs& args);
	// 获取账号列表
	JSValue GetLists(const JSObject& thisObject, const JSArgs& args);
	// 删除账号
	JSValue RemoveAccount(const JSObject& thisObject, const JSArgs& args);
	// 添加账号
	JSValue AddAccount(const JSObject& thisObject, const JSArgs& args);
	// 编辑账号信息
	JSValue EditAccount(const JSObject& thisObject, const JSArgs& args);

protected:
	// 主程序对象
	RefPtr<App> app_;
	// 主窗体对象
	RefPtr<Window> window_;
	// 主UI层对象
	RefPtr<Overlay> overlay_;
private:
	// 逻辑处理类对象
	Adapt* logicAdapt{};
	// 活跃UI对象
	View* displayView{};
};
