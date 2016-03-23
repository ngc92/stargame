#include "ActionList.h"

void ActionList::push(std::unique_ptr<IAction> action)
{
	mList.push_back( std::move(action) );
}
