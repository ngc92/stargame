#include "CDebugDraw.h"
#include "consts.h"
#include "game/IGameWorld.h"
#include <irrlicht/irrlicht.h>
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

inline irr::core::vector3df b2i(b2Vec2 v)
{
	return irr::core::vector3df( BOX_TO_METERS * v.x, 0, BOX_TO_METERS * v.y );
}

CDebugDraw::CDebugDraw( irr::video::IVideoDriver* driver ) : mDriver(driver)
{
	SetFlags(e_shapeBit);
}

void CDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& col)
{
	irr::video::SColor color(255, col.r * 255, col.g * 255, col.b * 255);
	for(int i = 0; i < vertexCount - 1; ++i)
	{
		drawLine(vertices[i], vertices[i+1], color);
	}
	drawLine(vertices[vertexCount-1], vertices[0], color);
}

void CDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& col)
{
	irr::video::SColor color(255, col.r * 255, col.g * 255, col.b * 255);
	for(int i = 0; i < vertexCount - 1; ++i)
	{
		drawLine(vertices[i], vertices[i+1], color);
	}
	drawLine(vertices[vertexCount-1], vertices[0], color);
}

void CDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& col)
{
	irr::video::SColor color(255, col.r * 255, col.g * 255, col.b * 255);
	for(float f = 0; f < 2*3.1415; f += 3.1415/10)
	{
		b2Vec2 o1(std::sin(f), std::cos(f));
		b2Vec2 o2(std::sin(f+3.1415/10), std::cos(f+3.1415/10));
		drawLine( center+radius*o1, center + radius*o2, color );
	}
}

void CDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& ax, const b2Color& col)
{
	DrawCircle(center, radius, col);
	irr::video::SColor color(255, col.r * 255, col.g * 255, col.b * 255);
	drawLine( center, center + radius * ax, color );
}

void CDebugDraw::drawLine(const b2Vec2& p1, const b2Vec2& p2, const color_type& color)
{
	std::lock_guard<std::mutex> lck(mWriteMutex);
	mWriteQueue.push_back([=](irr::video::IVideoDriver* driver){
						driver->draw3DLine( b2i(p1), b2i(p2), color );
						});
}

void CDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& col) {
	irr::video::SColor color(255, col.r * 255, col.g * 255, col.b * 255);
	drawLine( p1, p2, color );
}

void CDebugDraw::DrawTransform(const b2Transform& xf)
{
	/// \todo what to draw here?
}

void CDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	/// \todo add something here
}

void CDebugDraw::setFinished()
{
	std::lock_guard<std::mutex> lck(mWriteMutex);
	std::swap(mDrawQueue, mWriteQueue);
}

void CDebugDraw::doDraw() const
{
	using namespace irr;
	video::SMaterial mat;
	mat.setFlag(video::EMF_LIGHTING, false);
	mDriver->setMaterial( mat );
	mDriver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
	std::lock_guard<std::mutex> lck(mWriteMutex);
	for(auto& f : mDrawQueue)
		f(mDriver);
}

void CDebugDraw::init(  game::IGameWorld& world  )
{
//	world.getWorld().SetDebugDraw(this);
}

void CDebugDraw::step( game::IGameWorld& world, const game::spawn::ISpawnManager& spawner )
{
	mWriteQueue.clear();
//	world.getWorld().DrawDebugData();
	setFinished();
}

