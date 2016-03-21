#include "ShipEditorState.h"
#include "IEngine.h"
#include <irrlicht/IGUIEnvironment.h>
#include <iostream>

ShipEditorState::ShipEditorState(IEngine* engine) : mGUIEnv(engine->getGUIEnvironment())
{

}

void ShipEditorState::update()
{
}

void ShipEditorState::onDraw()
{
	mGUIEnv->drawAll();
}

void ShipEditorState::onActivate()
{
	mRootElement = mGUIEnv->addGUIElement("empty");
	mGUIEnv->addButton(irr::core::rect<irr::s32>(100,100,400,200), mRootElement, -1, L"TEST");
}

void ShipEditorState::onDeactivate() noexcept
{

}

const char* ShipEditorState::getName() const noexcept
{
	return "ShipEditor";
}

IGUIEnvironment* ShipEditorState::getGUIEnvironment() noexcept
{
	return nullptr;
}
