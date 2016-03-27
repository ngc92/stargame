#ifndef IDEBUGDRAW_H_INCLUDED
#define IDEBUGDRAW_H_INCLUDED

namespace irr
{
	namespace video
	{
		class IVideoDriver;
	}
}

class IDebugDraw
{
public:
	virtual ~IDebugDraw() = default;
	virtual void doDraw(irr::video::IVideoDriver* driver) const = 0;
};

#endif // IDEBUGDRAW_H_INCLUDED
