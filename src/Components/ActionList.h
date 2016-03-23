#ifndef ACTIONLIST_H_INCLUDED
#define ACTIONLIST_H_INCLUDED

#include <deque>
#include <memory>
#include <algorithm>
#include "IAction.h"

class ActionList : public IActionListInterface
{
public:
	void push(std::unique_ptr<IAction>) override;

	template<class T>
	void act( T&& t );
private:
	std::deque<std::unique_ptr<IAction>> mList;
};

template<class T>
void ActionList::act( T&& t )
{
	using namespace std;
	auto nl = remove_if( begin(mList), end(mList), [&](const std::unique_ptr<IAction>& action){ return action->act(t); } );
	mList.resize(distance(begin(mList), nl));
}


#endif // ACTIONLIST_H_INCLUDED
