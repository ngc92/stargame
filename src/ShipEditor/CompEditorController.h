#ifndef COMPEDITORCONTROLLER_H_INCLUDED
#define COMPEDITORCONTROLLER_H_INCLUDED

#include "CompEditorData.h"
#include "CompEditorView.h"
#include "CUIEventListener.h"
#include <irrlicht/IGUIEnvironment.h>
#include <memory>
#include <irrlicht/IGUIButton.h>

using namespace irr::gui;
using Event = const irr::SEvent::SGUIEvent;

class CompEditorController
{
public:
	CompEditorController(CompEditorData& data);
	void initView(IGUIEnvironment* guiEnv);
	void performEvent(Event& event);
	void addEventListener(IGUIElement* elm,std::function<bool(Event)> func);

	///controller functions...
	bool test_f(Event& evt);

private:
	CompEditorData&	mData;
	std::shared_ptr<CompEditorView> view;
	CUIEventListener eventListener;
};

#endif // COMPEDITORCONTROLLER_H_INCLUDED
