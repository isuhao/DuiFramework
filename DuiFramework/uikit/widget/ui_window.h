﻿#pragma once
#include "uikit/widget/ui_view.h"

namespace ui
{
	class UIWindowPrivate;
	class UIViewController;
	class UIWindow : public UIView
	{
	public:
		UIWindow();
		~UIWindow();

		UIViewController* rootViewController() const { return controller_; }
		//@privte
		void setRootViewController(UIViewController* controller) {
			controller_ = controller;
		}

		virtual void InitWithBounds(const Rect& rect) override;

		virtual UIResponder* NextResponder() const override;

		virtual void SchedulePaintInRect(const Rect& r) override;

		virtual void OnVisibleChanged() override;
		virtual void OnPositionChanged() override;

		virtual bool PointInsideWithEvent(const Point& pt, UIEvent* event) override;
		void Close();
		void AddToScreen();

		Point ConvertFromScreen(const Point& pt);
		Point ConvertToScreen(const Point& pt);

		void SetCursor(CursorId id);

		virtual void mouseMove(UIMouse* mouse, UIEvent* event) override;
		virtual void mousePress(UIMouse* mouse, UIEvent* event) override;
		virtual void mouseRelease(UIMouse* mouse, UIEvent* event) override;
	private:
		void PrivateInit();
		void willAppear();
		void didAppear();
		void willDisappear();
		void didDisappear();
		UIWindowPrivate* private_;
		UIViewController* controller_;

		bool may_start_drag_{ false };
		Point last_position_;
	};
}