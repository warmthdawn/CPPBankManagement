#include "MainWindow.h"
#include <AppCore/JSHelpers.h>
#include <iostream>
#include <Windows.h>
#include <WinNls.h>

using namespace ultralight;

//����Ĭ�Ͽ��
#define WINDOW_WIDTH  750

//����Ĭ�ϸ߶�
#define WINDOW_HEIGHT 450


//��ʼ������
MainWindow::MainWindow() {
	//Appʵ��
	app_ = App::Create();
	//����
	window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
		//�����⣬������󻯣����Ե�����С
		false, kWindowFlags_Titled | kWindowFlags_Maximizable | kWindowFlags_Resizable);

	
	//���ڱ���
	window_->SetTitle("���й���ϵͳ");
	//����������
	app_->set_window(*window_.get());
	//���ô�����Ⱦ
	overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);
	//�������ڴ�С�¼��ļ���
	OnResize(window_->width(), window_->height());
	//���ش���
	overlay_->view()->LoadURL("file:///main.html");
	//�����¼�������
	app_->set_listener(this);
	window_->set_listener(this);
	overlay_->view()->set_load_listener(this);
	overlay_->view()->set_view_listener(this);
}

//����ر�
MainWindow::~MainWindow() {
	delete logicAdapt;
}

//��������
void MainWindow::Run() {
	app_->Run();
}

//���ڸ���
void MainWindow::OnUpdate() {
}

//���ڹر�
void MainWindow::OnClose() {
}

//������С
void MainWindow::OnResize(uint32_t width, uint32_t height) {
	overlay_->Resize(width, height);
}

void MainWindow::OnFinishLoading(View* caller) {

	//��ʼ��
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
// ����ת������
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

//���ݺϷ��Լ��
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

//������־
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



//���ڼ������
void MainWindow::OnDOMReady(View* caller) {
	//��JS����
	SetJSContext(caller->js_context());
	//ȫ��js����
	const JSObject global = JSGlobalObject();

	//��C++����������JavaScript���󣬴��ݵĲ���Ϊ������ָ��
	global["GetAccount"] = BindJSCallbackWithRetval(&MainWindow::GetAccount);
	global["GetLists"] = BindJSCallbackWithRetval(&MainWindow::GetLists);
	global["RemoveAccount"] = BindJSCallbackWithRetval(&MainWindow::RemoveAccount);
	global["AddAccount"] = BindJSCallbackWithRetval(&MainWindow::AddAccount);
	global["EditAccount"] = BindJSCallbackWithRetval(&MainWindow::EditAccount);

	displayView = caller;
	cout << "�����ʼ�����" << endl;
}

//��JS����ת��Ϊ�ַ���
char* getArgs(const JSArgs& args, int index) {
	size_t buffer = JSStringGetMaximumUTF8CStringSize(args[index].ToString());
	char* str = new char[buffer];
	JSStringGetUTF8CString(args[index].ToString(), str, buffer);
	return str;
}


JSValue MainWindow::GetAccount(const JSObject& thisObject, const JSArgs& args)
{
	char* id_acc = getArgs(args, 0);

	//��ȡ����
	string data = logicAdapt->getAll(id_acc);
	delete id_acc;
	string scriptR = GBKToUTF8(("setDisplay(" + data + ");").c_str());
	String8 script = scriptR.c_str();

	this->overlay_->view()->EvaluateScript(script);
	return NULL;
}


//
JSValue MainWindow::GetLists(const JSObject& thisObject, const JSArgs& args) {

	//�˷��������ݲ������װ���˴�ע��

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
	cout << "׼����ʼ��ȡ�˻��б�" << endl;
	string all = logicAdapt->All();
	return JSValue(all.c_str());


}
JSValue MainWindow::RemoveAccount(const JSObject& thisObject, const JSArgs& args) {
	char* id_acc = getArgs(args, 0);

	bool removed = logicAdapt->Delete(id_acc);

	cout << "ɾ���˺�" << id_acc << endl;
	//�ж��Ƿ�ɾ���ɹ�
	if (removed) {

		//���¶�ȡ����
		this->overlay_->view()->EvaluateScript("read_data()");
		//�����ʾ����
		this->overlay_->view()->EvaluateScript("clearDisplay()");
		//�������������
		this->overlay_->view()->EvaluateScript("$('#id_account').val('')");
		//ˢ����ʾ�б�
		this->overlay_->view()->EvaluateScript("initial_selections('')");
	}
	else {
		//��ʾɾ��ʧ��
		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('ɾ��ʧ��', '�˺Ų�����')").c_str()));

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
		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('���ʧ��', '�Ƿ��Ĵ������')").c_str()));
		return NULL;
	}


	cout << "����˺�" << id_acc << endl;

	//�������
	string name_encoded = UTF8ToGBK(name);
	string address_encoded = UTF8ToGBK(address);


	//�������
	if (!(check_data(id_acc) && check_data(id_card) && check_data(name_encoded) && check_data(address_encoded))) {

		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('���ʧ��', '�벻Ҫ���������ַ��������ո�')").c_str()));
		return NULL;
	}

	//���
	bool success = logicAdapt->Add(id_acc, id_card, name_encoded, address_encoded, balance);

	//�ж��Ƿ���ӳɹ�
	if (success) {
		//���¶�ȡ����
		this->overlay_->view()->EvaluateScript("read_data()");
		//ˢ����ʾ�б�
		this->overlay_->view()->EvaluateScript("initial_selections($('#id_account').val())");
		//ˢ������
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
		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('�༭ʧ��', '�Ƿ��Ĵ������')").c_str()));
		return NULL;
	}
	//�������
	string name_encoded = UTF8ToGBK(name);
	string address_encoded = UTF8ToGBK(address);


	cout << "�༭�˺�" << id_acc << endl;

	//�������
	if (!(check_data(id_acc) && check_data(id_card) && check_data(name_encoded) && check_data(address_encoded))) {

		this->overlay_->view()->EvaluateScript(static_cast<String8>(GBKToUTF8("showMessage('���ʧ��', '�벻Ҫ���������ַ��������ո�')").c_str()));
		this->overlay_->view()->EvaluateScript("flushDisplay()");
		return NULL;
	}

	//�༭��������ӷ�������
	logicAdapt->Add(id_acc, id_card, name_encoded, address_encoded, balance);
	this->overlay_->view()->EvaluateScript("flushDisplay()");

	delete id_acc;
	delete id_card;
	delete name;
	delete address;
	delete balance_raw;
	return NULL;
}

