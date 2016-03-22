#include "CUIEventListener.h"
#include <irrlicht/IGUIElement.h>
#include <algorithm>

CUIEventListener::~CUIEventListener()
{
    /// \todo remove all listeners
    for(auto& pair_llist : mListeners)
	{
		for(auto& listener : pair_llist.second)
		{
			// one drop for each listener
            pair_llist.first->drop();
		}
	}
}

CUIEventListener::listener_iter CUIEventListener::registerListenerForElement( irr::gui::IGUIElement* element, listener_f listener)
{
	// when adding a listener, grab the element to prevent accidential deletion
	element->grab();

	auto lstlst = mListeners.find(element);
	if(lstlst != mListeners.end())
	{
        lstlst->second.push_back( listener );
        return --lstlst->second.end();
	}
	else
	{
		listener_list lst;
		lst.push_back( listener );
		mListeners[element] = lst;
		return --mListeners[element].end();
	}
}

void CUIEventListener::removeListenerForElement(irr::gui::IGUIElement* element, listener_iter listener)
{
	auto lstlst = mListeners.find(element);
	if(lstlst != mListeners.end())
	{
		element->drop();
        lstlst->second.erase(listener);
	}
}

bool CUIEventListener::onEvent(irr::SEvent::SGUIEvent event) const
{
    auto elem = event.Caller;
	auto lstlst = mListeners.find(elem);
	if(lstlst != mListeners.end())
	{
		return std::any_of(lstlst->second.begin(), lstlst->second.end(), [&event](const listener_f& l){ return l(event); });
	}
	return false;
}
