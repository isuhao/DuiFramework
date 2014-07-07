#pragma once
#include "base/scoped_ptr.h"
#include "utils/image_store.h"
#include "event/event_listen_manager.h"

namespace ui
{
	class App
	{
	public:
		static App* Get();

		void Run();

		ImageStore* DefaultImageStore();

		EventListenManager* DefaultEventListenManager();
	private:
		App();
		~App();

		void Init();
		void UnInit();
		void InitMessageWndClass();

		static LRESULT CALLBACK WndProcThunk(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
		static LRESULT CALLBACK WndProcNormal(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
		void HandleWorkMessage();
		void HandleTimerMessage();

		bool ProcessNextWindowsMessage();
		void WaitForWork();

		static const int kMessageFilterCode = 0x5001;

		HWND message_hwnd_;
		HINSTANCE instance_;

		scoped_ptr<ImageStore> image_store_;

		scoped_ptr<EventListenManager> listen_manager_;

		ULONG_PTR gdiplusToken_;
	};
}