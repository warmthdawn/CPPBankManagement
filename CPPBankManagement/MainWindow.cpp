#include "MainWindow.h"
#include <AppCore/JSHelpers.h>
#include <iostream>
#include <Windows.h>
#include <WinNls.h>

using namespace ultralight;

//窗口默认宽度
#define WINDOW_WIDTH  750

//窗口默认高度
#define WINDOW_HEIGHT 450


//初始化窗口
MainWindow::MainWindow() {
	//App实例
	app_ = App::Create();
	//窗口
	window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
		//含标题，可以最大化，可以调整大小
		false, kWindowFlags_Titled | kWindowFlags_Maximizable | kWindowFlags_Resizable);

	
	//窗口标题
	window_->SetTitle("银行管理系统");
	//设置主窗口
	app_->set_window(*window_.get());
	//设置窗口渲染
	overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);
	//调整窗口大小事件的监听
	OnResize(window_->width(), window_->height());
	//加载窗体
	overlay_->view()->LoadURL("file:///main.html");
	//设置事件监听器
	app_->set_listener(this);
	window_->set_listener(this);
	overlay_->view()->set_load_listener(this);
	overlay_->view()->set_view_listener(this);
}

//程序关闭
MainWindow::~MainWindow() {
	delete logicAdapt;
}

//程序启动
void MainWindow::Run() {
	app_->Run();
}

//窗口更新
void MainWindow::OnUpdate() {
}

//窗口关闭
void MainWindow::OnClose() {
}

//调整大小
void MainWindow::OnResize(uint32_t width, uint32_t height) {
	overlay_->Resize(width, height);
}

void MainWindow::OnFinishLoading(View* caller) {

	//初始化
	logicAdapt = new Adapt();
}

inline std::string ToUTF8(const String& str) {
	String8 utf8 = str.utf8();
	return std::string(utf8.data(), utf8.length());
}

inline const char* Stringify(MessageLevel level) {
	switch (level) {
	case kMessageLevel_Log: return "Log";
	case kMessageLevel_Warning: return "Warning";
	case kMessageLevel_Error: return "Error";
	case kMessageLevel_Debug: return "Debug";
	case kMessageLevel_Info: return "Info";
	default: return "";
	}
}
// 编码转换函数
string GBKToUTF8(const char* strGBK)
{
	int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

string UTF8ToGBK(const char* strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

//数据合法性检查
bool check_data(const char* data) {
	int i = 0;
	while (data[i]) {
		if (data[i] == '#') {
			return false;
		}
		i++;
	}
	return true;
}

bool check_data(string data) {
	int i = 0;
	while (i < data.length()) {
		if (data[i] == '#') {
			return false;
		}
		i++;
	}
	return true;
}

//调试日志
void MainWindow::OnAddConsoleMessage(View* caller,
	MessageSource source,
	MessageLevel level,
	const String& message,
	uint32_t line_number,
	uint32_t column_number,
	const String& source_id) {

	cout << "[Console]:[" <<
		Stringify(level) << "] " << UTF8ToGBK(ToUTF8(message).c_str());

	if (source == kMessageSource_JS) {
		std::cout << " (" << ToUTF8(source_id) << " @ line " << line_number <<
			", col " << column_number << ")";
	}

	cout << endl;

}



//窗口加载完毕
void MainWindow::OnDOMReady(View* caller) {
	//主JS处理
	SetJSContext(caller->js_context());
	//全局js对象
	const JSObject global = JSGlobalObject();

	//绑定C++方法到窗口JavaScript对象，传递的参数为方法的指针
	global["GetAccount"] = BindJSCallbackWithRetval(&MainWindow::GetAccount);
	global["GetLists"] = BindJSCallbackWithRetval(&MainWindow::GetLists);
	global["RemoveAccount"] = BindJSCallbackWithRetval(&MainWindow::RemoveAccount);
	global["AddAccount"] = BindJSCallbackWithRetval(&MainWindow::AddAccount);
	global["EditAccount"] = BindJSCallbackWithRetval(&MainWindow::EditAccount);

	displayView = caller;
	cout << "窗体初始化完成" << endl;
}

//将JS参数转换为字符串
char* getArgs(const JSArgs& args, int index) {
	size_t buffer = JSStringGetMaximumUTF8CStringSize(args[index].ToString());
	char* str = new char[buffer];
	JSStringGetUTF8CString(args[index].ToString(), str, buffer);
	return str;
}


JSValue MainWindow::GetAccount(const JSObject& thisObject, const JSArgs& args)
{
	char* id_acc = getArgs(args, 0);

	//获取数据
	string data = logicAdapt->getAll(id_acc);
	delete id_acc;
	string scriptR = GBKToUTF8(("setDisplay(" + data + ");").c_str());
	String8 script = scriptR.c_str();

	this->overlay_->view()->EvaluateScript(script);
	return NULL;
}


//
JSValue MainWindow::GetLists(const JSObject& thisObject, const JSArgs& args) {

	//此方法有数据操作类封装，此处注释

	/*
	string* all;
	int n = file->allObject(&all);

	string s = "[\"";

	for (int i = 0; i < n; i++)
	{
		s.append(all[i]);
		if (i < n - 1) {
			s.append("\",\"");
		}
	}
	s.append("\"]");
	cout << s;
	return JSValue(s.c_str());
	*/
	cout << "准备开始读取账户列表" << endl;
	string all = logicAdapt->All();
	return JSValue(all.c_str());


}
JSValue MainWindow::RemoveAccount(const JSObject& thisObject, const JSArgs& args) {
	char* id_acc = getArgs(args, 0);

	bool removed = logicAdapt->Delete(id_acc);

	cout << "删除账号" << id_acc << endl;
	//判断是否删除成功
	if (removed) {

		//重新读取数据
		this->overlay_->view()->EvaluateScript("read_data()");
		//清空显示数据
		this->overlay_->view()->EvaluateScript("clearDisplay()");
		//重新输入框数据
		this->overlay_->view()->EvaluateScript("$('#id_account').val('')");
		//刷新提示列表
		this->overlay_->view()->EvaluateScript("initial_selections('')");
	}
	else {
		//提示删除失败
		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('删除失败', '账号不存在')").c_str()));

	}

	delete id_acc;
	return NULL;
}


JSValue MainWindow::AddAccount(const JSObject& thisObject, const JSArgs& args) {
	char* id_acc = getArgs(args, 0);
	char* id_card = getArgs(args, 1);
	char* name = getArgs(args, 2);
	char* address = getArgs(args, 3);
	char* balance_raw = getArgs(args, 4);
	double balance;
	try {
		balance = atof(balance_raw);
	}
	catch (...) {
		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('添加失败', '非法的存款数据')").c_str()));
		return NULL;
	}


	cout << "添加账号" << id_acc << endl;

	//处理编码
	string name_encoded = UTF8ToGBK(name);
	string address_encoded = UTF8ToGBK(address);


	//检查数据
	if (!(check_data(id_acc) && check_data(id_card) && check_data(name_encoded) && check_data(address_encoded))) {

		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('添加失败', '请不要输入特殊字符（包括空格）')").c_str()));
		return NULL;
	}

	//添加
	bool success = logicAdapt->Add(id_acc, id_card, name_encoded, address_encoded, balance);

	//判断是否添加成功
	if (success) {
		//重新读取数据
		this->overlay_->view()->EvaluateScript("read_data()");
		//刷新提示列表
		this->overlay_->view()->EvaluateScript("initial_selections($('#id_account').val())");
		//刷新数据
		this->overlay_->view()->EvaluateScript("flushDisplay()");
	}

	delete id_acc;
	delete id_card;
	delete name;
	delete address;
	delete balance_raw;
	return NULL;
}


JSValue MainWindow::EditAccount(const JSObject& thisObject, const JSArgs& args) {
	char* id_acc = getArgs(args, 0);
	char* id_card = getArgs(args, 1);
	char* name = getArgs(args, 2);
	char* address = getArgs(args, 3);
	char* balance_raw = getArgs(args, 4);

	double balance;
	try {
		balance = atof(balance_raw);
	}
	catch (...) {
		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('编辑失败', '非法的存款数据')").c_str()));
		return NULL;
	}
	//处理编码
	string name_encoded = UTF8ToGBK(name);
	string address_encoded = UTF8ToGBK(address);


	cout << "编辑账号" << id_acc << endl;

	//检查数据
	if (!(check_data(id_acc) && check_data(id_card) && check_data(name_encoded) && check_data(address_encoded))) {

		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('添加失败', '请不要输入特殊字符（包括空格）')").c_str()));
		this->overlay_->view()->EvaluateScript("flushDisplay()");
		return NULL;
	}

	//编辑方法与添加方法类似
	logicAdapt->Add(id_acc, id_card, name_encoded, address_encoded, balance);
	this->overlay_->view()->EvaluateScript("flushDisplay()");

	delete id_acc;
	delete id_card;
	delete name;
	delete address;
	delete balance_raw;
	return NULL;
}

