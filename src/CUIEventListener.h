#ifndef CUIEVENTLISTENER_H_INCLUDED
#define CUIEVENTLISTENER_H_INCLUDED

#include "IUIEventListener.h"
#include <unordered_map>

class CUIEventListener : public IUIEventListener
{
	using listeners_map = std::unordered_map<irr::gui::IGUIElement*, listener_list>;

public:
	virtual ~CUIEventListener();

	listener_iter registerListenerForElement( irr::gui::IGUIElement* element, listener_f listener) override;
	void removeListenerForElement(irr::gui::IGUIElement* element, listener_iter listener) override;
	bool onEvent(irr::SEvent::SGUIEvent) const override;
private:
	listeners_map mListeners;
};

#endif // CUIEVENTLISTENER_H_INCLUDED
