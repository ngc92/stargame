#include "CompEditorView.h"
#include "CompEditorController.h"

#include <irrlicht/coreutil.h>
#include <irrlicht/IGUIButton.h>

CompEditorView::CompEditorView(CompEditorData& data,CompEditorController& controller,irr::gui::IGUIEnvironment* guiEnv):
	env(guiEnv)
{
	const irr::core::recti 	rectangle(50,50,200,200);
	const wchar_t* 			text = L"test";
	const wchar_t* 			tooltiptext = 0;

	irr::gui::IGUIButton* newCompButton;
	newCompButton = guiEnv->addButton(rectangle,0,1,text,tooltiptext);

	initMenuBar();
}


void CompEditorView::initMenuBar(){
	const irr::core::recti 	compMenuRect(0,0,100,100);
	compMenu = env->addContextMenu(compMenuRect, 0, 2);
	//compMenu->addItem(L"Comp",3,true,false,false,false);
	//compMenu->setText(L"Component");
}
