#include "CompEditorController.h"
CompEditorController::CompEditorController(CompEditorData& data):
	mData(data)
{
}

void CompEditorController::addEventListener(IGUIElement* elm,std::function<bool(Event)> func)
{
	eventListener.registerListenerForElement(elm,func);
}

void CompEditorController::performEvent(Event& event)
{
	eventListener.onEvent(event);
}

void CompEditorController::initView(IGUIEnvironment* guiEnv)
{
	view = std::make_shared<CompEditorView>(mData, *this,guiEnv);
}

///---controller-functions--------------------
bool test_f(Event& event)
{

}
