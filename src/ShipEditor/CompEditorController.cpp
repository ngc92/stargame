#include "CompEditorController.h"
#include <irrlicht/IGUIEnvironment.h>

CompEditorController::CompEditorController(CompEditorData& data):
	mData(data)
{
}

void CompEditorController::initView(irr::gui::IGUIEnvironment* guiEnv)
{
	view = std::make_shared<CompEditorView>(mData,*this,guiEnv);
}

