#ifndef CDEBUGDRAW_H_INCLUDED
#define CDEBUGDRAW_H_INCLUDED

#include <vector>
#include <functional>
#include <mutex>
#include <Box2D/Common/b2Draw.h>
#include "util.h"
#include "IDebugDraw.h"

namespace irr
{
	namespace video
	{
		class IVideoDriver;
	}
}

struct b2AABB;

class CDebugDraw : public b2Draw, public IDebugDraw
{
	public:
		CDebugDraw( irr::video::IVideoDriver* driver );

		virtual ~CDebugDraw() = default;

		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

		void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

		void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;

		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

		void DrawTransform(const b2Transform& xf) override;

		void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

		// control functions
		void setFinished();
		void doDraw() const override;

		// game view module implementation
		void init(  game::IGameWorldView& world_view  ) final{};
		void step( game::IGameWorldView& world_view ) final{};

	private:
		void drawLine(const b2Vec2& p1, const b2Vec2& p2, const color_type& color);

		// double buffered draw list
		mutable std::mutex mWriteMutex;
		std::vector<std::function<void(irr::video::IVideoDriver*)>> mWriteQueue;
		std::vector<std::function<void(irr::video::IVideoDriver*)>> mDrawQueue;

		irr::video::IVideoDriver* mDriver;
};

//extern CDebugDraw d;

#endif // CDEBUGDRAW_H_INCLUDED
