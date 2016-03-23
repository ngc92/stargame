#ifndef COMPEDITORVIEW_H_INCLUDED
#define COMPEDITORVIEW_H_INCLUDED

#include "CompEditorData.h"
#include <irrlicht/IGUIEnvironment.h>

class CompEditorController;

class CompEditorView
{
public:
	CompEditorView(CompEditorData& data,CompEditorController& controller,irr::gui::IGUIEnvironment* guiEnv);

private:
	irr::gui::IGUIEnvironment* env;
	const int def_l = 100;
	const int def_h = 100;

	void initMenuBar();
	irr::gui::IGUIContextMenu* compMenu;

};

#endif // COMPEDITORVIEW_H_INCLUDED
