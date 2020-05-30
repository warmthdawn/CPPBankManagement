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

	// Start the run loop.
	virtual void Run();

	// This is called continuously from the app's main loop. Update logic here.
	virtual void OnUpdate() override;

	// This is called when the window is closing.
	virtual void OnClose() override;

	// This is called whenever the window resizes.
	virtual void OnResize(uint32_t width, uint32_t height) override;

	// This is called when the page finishes a load in the main frame.
	virtual void OnFinishLoading(View* caller) override;

	// This is called when the DOM has loaded in the main frame. Update JS here.
	virtual void OnDOMReady(View* caller) override;

	//
	virtual void OnAddConsoleMessage(View* caller,
		MessageSource source,
		MessageLevel level,
		const String& message,
		uint32_t line_number,
		uint32_t column_number,
		const String& source_id) override;

	JSValue GetAccount(const JSObject& thisObject, const JSArgs& args);
	JSValue GetLists(const JSObject& thisObject, const JSArgs& args);
	JSValue RemoveAccount(const JSObject& thisObject, const JSArgs& args);
	JSValue AddAccount(const JSObject& thisObject, const JSArgs& args);
	JSValue EditAccount(const JSObject& thisObject, const JSArgs& args);

protected:
	RefPtr<App> app_;
	RefPtr<Window> window_;
	RefPtr<Overlay> overlay_;
private:
	Adapt* logicAdapt{};
	View* displayView{};
};
