#pragma once
#include "base/basictypes.h"
#include "dom/ui_document.h"

namespace ui
{
	class UIParser
	{
	public:
		UIParser();
		
		void SetDomDocument(UIDocumentPtr document);

		bool ParseXmlDocument(const std::string& buffer);
	private:
		UIElementPtr ParseXmlElement(void* elem);
		UIElementPtr ParseUIElement(void* elem, const char* tag);
		void ParseStyleSheet(void* elem);

		UIElement* CreateUIElement(const char* tag);

		bool ParseElementClasses(UIElementPtr elem, const char* val);
		UIDocumentPtr document_;
		DISALLOW_COPY_AND_ASSIGN(UIParser);
	};
}