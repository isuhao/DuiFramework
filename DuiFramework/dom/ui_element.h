#pragma once
#include "base/basictypes.h"
#include "dom/ui_forward.h"
#include "render/render_forward.h"
#include "core/hittest_result.h"
#include "event/event_target.h"

#include <set>

namespace ui
{

	class RenderObject;
	class UIElement 
		: public EventTarget
	{
		friend class UIDocument;
		friend class UIElement;
	public:
		UIElement(UIDocumentPtr);
		UIDocumentPtr GetDocument();

		UIElementPtr parent();
		bool HasChildren() const;
		bool HasParent() const;

		UIElementPtr previousSibling() const;
		UIElementPtr nextSibling() const;
		UIElementPtr firstChild() const;
		UIElementPtr lastChild() const;

		void AppendTo(UIElementPtr parent);
		void Detach();

		void Append(UIElementPtr child);
		void Prepend(UIElementPtr child);
		void Remove(UIElementPtr child);
		void InsertAfterChild(UIElementPtr ref, UIElementPtr child);
		void InsertBeforeChild(UIElementPtr ref, UIElementPtr child);

		void RemoveChildren();
		void RemoveChild(UIElementPtr n);

		//=================================================
		//position
		void SetBounds(int x, int y, int width, int height);
		void SetBoundsRect(const Rect& bounds);
		void SetSize(const Size& size);
		void SetPosition(const Point& position);
		void SetPosition(int x, int y);
		void SetX(int x);
		void SetY(int y);

		// No transformation is applied on the size or the locations.
		const Rect& bounds() const { return bounds_; }
		int x() const { return bounds_.x(); }
		int y() const { return bounds_.y(); }
		int width() const { return bounds_.width(); }
		int height() const { return bounds_.height(); }
		const Size& size() const { return bounds_.size(); }
		Rect GetLocalBounds() const;
		Rect GetContentBounds() const;

		static Point ConvertPointToElement(UIElement* elem, const Point& pt);

		//=================================================
		//attribute
		void setTag(const std::string& tag);
		const std::string& getTag() const;
		void setId(const std::string& id);
		const std::string& getId() const;

		void addClass(const std::string& v);
		void removeClass(const std::string& v);
		bool haveClass(const std::string& v) const;
		void clearClass();

		//=================================================
		//styles
		void UpdateStyles();
		RenderStyles* styles() const;
		int marginLeft() const;
		int marginTop() const;
		int marginRight() const;
		int marginBottom() const;
		int marginWidth() const { return marginLeft() + marginRight(); }
		int marginHeight() const { return marginTop() + marginBottom(); }

		//=================================================
		//paint
		virtual void SchedulePaint();
		virtual void SchedulePaintInRect(const Rect& r);
		virtual void OnChildSchedulePaintInRect(UIElement* child, const Rect& r);
		virtual void DoPaint(RenderContext* painter, const Rect& r);

		//=================================================
		//layout
		virtual void Layout();
		virtual void LayoutIfNeeded();
		virtual void OnBoundsChanged();
		virtual void OnChildBoundsChanged(UIElement* child);

		//=================================================
		//event
		virtual bool Hittest(HitTestResult* result, const Point& pt);

		void HandleLocalEvents(Event* event);
		bool DispatchMouseEvent(MouseEvent* evt, EventType eventType, int clickCount = 0, UIElement* relatedTarget = NULL);
	protected:
		virtual ~UIElement();
		void Unlink(UIElementPtr child);

		Rect ConvertRectFromChild(UIElement* child, const Rect& r);
		void PaintBackground(RenderContext* painter);
		void PaintBorder(RenderContext* painter);
		void PaintContents(RenderContext* painter);

		UIDocumentPtr document_;
		
		UIElementPtr parent_{ NULL };
		UIElementPtr prev_sibling_{ NULL };
		UIElementPtr next_sibling_{ NULL };
		UIElementPtr first_child_{ NULL };
		UIElementPtr last_child_{ NULL };

		std::string tag_;
		std::string id_;
		std::set<std::string> classes_;

		scoped_ptr<RenderStyles> styles_;

		Rect bounds_; // ʵ��λ��
		bool needs_layout_{true};//self needs layout
		bool child_needs_layout_{true};

		DISALLOW_COPY_AND_ASSIGN(UIElement);
	};
}