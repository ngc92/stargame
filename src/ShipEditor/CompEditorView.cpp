#include "CompEditorView.h"

#include <irrlicht/coreutil.h>
#include <irrlicht/IGUIButton.h>


CompEditorView::CompEditorView(CompEditorData& data,CompEditorController& controller,irr::gui::IGUIEnvironment* guiEnv)
{
	const irr::core::recti 	rectangle(50,50,100,100);
	const wchar_t* 			text = L"test";
	const wchar_t* 			tooltiptext = 0;

	irr::gui::IGUIButton* newCompButton;
	newCompButton = guiEnv->addButton(rectangle,0,1,text,tooltiptext);
}

