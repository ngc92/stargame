#ifndef COMPEDITORVIEW_H_INCLUDED
#define COMPEDITORVIEW_H_INCLUDED

#include "CompEditorData.h"
#include <irrlicht/IGUIEnvironment.h>

class CompEditorController;

class CompEditorView
{
public:
	CompEditorView(CompEditorData& data,CompEditorController& controller,irr::gui::IGUIEnvironment* guiEnv);

};

#endif // COMPEDITORVIEW_H_INCLUDED
