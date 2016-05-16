**Bullets: Second kind of game object that can be created, does not posses substructure but FlightModel**
* bullet specs from file															DONE
* deletion after timeout
* impact handling
* gun component																		DONE
* deactivate impact test between shot and shooter
 
**GFX**
* default game view
	
**Autopilot submodule: lowest level of micro-ai within game thread**
* set desired position, velocity and orientation
* find a way to allow communication between engine and autopilot
* communicate to autopilot
	
**Affiliations: Save team and owning object for relevant objects (object_module)**		DONE
* spaceships are owned by their team													DONE
* bullets/missiles etc are owned by the shooter											DONE


**Refactoring:**
* use boost::range when applicable (boost::any_range!)
* ISpawnManager
* manage data types when loading properties from file.
	
**Permagoals:**
* improve error handling and logging
* commenting, doxygen
* tests!
