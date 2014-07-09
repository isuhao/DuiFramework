#pragma once

namespace ui
{
	class View;
	class LayoutManager
	{
	public:
		virtual ~LayoutManager() {}

		virtual void Layout(View* owner) = 0;
	};
}