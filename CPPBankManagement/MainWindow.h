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
	// ��������
	virtual void Run();
	// ��׼�����¼�ѭ��
	virtual void OnUpdate() override;
	// ����ر��¼�
	virtual void OnClose() override;
	// �����С����
	virtual void OnResize(uint32_t width, uint32_t height) override;
	// �����ܼ���
	virtual void OnFinishLoading(View* caller) override;
	// ������Ⱦ���
	virtual void OnDOMReady(View* caller) override;
	// ����JavaScript��־����
	virtual void OnAddConsoleMessage(View* caller, MessageSource source, MessageLevel level, const String& message, uint32_t line_number, uint32_t column_number, const String& source_id) override;
	// ��ȡ�˺���Ϣ�߼�
	JSValue GetAccount(const JSObject& thisObject, const JSArgs& args);
	// ��ȡ�˺��б�
	JSValue GetLists(const JSObject& thisObject, const JSArgs& args);
	// ɾ���˺�
	JSValue RemoveAccount(const JSObject& thisObject, const JSArgs& args);
	// ����˺�
	JSValue AddAccount(const JSObject& thisObject, const JSArgs& args);
	// �༭�˺���Ϣ
	JSValue EditAccount(const JSObject& thisObject, const JSArgs& args);

protected:
	// ���������
	RefPtr<App> app_;
	// ���������
	RefPtr<Window> window_;
	// ��UI�����
	RefPtr<Overlay> overlay_;
private:
	// �߼����������
	Adapt* logicAdapt{};
	// ��ԾUI����
	View* displayView{};
};
