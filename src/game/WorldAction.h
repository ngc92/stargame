#ifndef WORLDACTION_H_INCLUDED
#define WORLDACTION_H_INCLUDED

#include <functional>
#include <iterator>

namespace game
{
	class IGameWorld;
	class ISpawnManager;
	
	/// this class allows pushing new actions into the action queue
	class WorldActionQueue
	{
	public:
		using action_fn = std::function<void(IGameWorld&, const ISpawnManager&)>;
		using action_fn_w = std::function<void(IGameWorld&)>;

		template<class Container>
		WorldActionQueue( Container& target )
		{
			auto inserter = std::back_inserter(target);
			mInsertFunction = [inserter](action_fn a) mutable
			{  
				*inserter = std::move(a);
			};
		}
		
		void operator()(action_fn action) {	mInsertFunction(std::move(action)); }
		void operator()(action_fn_w action) 
		{
			/// \todo move action into the lambda
			/// double indirection here! function -> lambda -> function. does this matter for efficiency?
			mInsertFunction([action](IGameWorld& w, const ISpawnManager& s){ action(w); }); 
		}
		
	private:
		std::function<void(action_fn)> mInsertFunction;
	};
}


#endif // WORLDACTION_H_INCLUDED
