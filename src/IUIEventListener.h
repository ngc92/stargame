#ifndef UIEVENTLISTENER_H_INCLUDED
#define UIEVENTLISTENER_H_INCLUDED

#include <functional>
#include <list>
#include "util.h"
#include <irrlicht/IEventReceiver.h>

namespace irr
{
	namespace gui
	{
		class IGUIElement;
	}
}

class IUIEventListener : public ObjectCounter<IUIEventListener>
{
protected:
	using listener_f = std::function<bool(irr::SEvent::SGUIEvent)>;
	using listener_list = std::list<listener_f>;
	using listener_iter = listener_list::iterator;
public:
	virtual ~IUIEventListener() = default;

	virtual listener_iter registerListenerForElement( irr::gui::IGUIElement* element, listener_f listener) = 0;
	virtual void removeListenerForElement(irr::gui::IGUIElement* element, listener_iter listener) = 0;
	virtual bool onEvent(irr::SEvent::SGUIEvent) const = 0;
};

#endif // UIEVENTLISTENER_H_INCLUDED
