#ifndef COMPEDITORCONTROLLER_H_INCLUDED
#define COMPEDITORCONTROLLER_H_INCLUDED

#include "CompEditorData.h"
#include "CompEditorView.h"
#include <irrlicht/IGUIEnvironment.h>
#include <memory>

class CompEditorController
{
public:
	CompEditorController(CompEditorData& data);
	void initView(irr::gui::IGUIEnvironment* guiEnv);

private:
	CompEditorData&	mData;
	std::shared_ptr<CompEditorView> view;

};

#endif // COMPEDITORCONTROLLER_H_INCLUDED
