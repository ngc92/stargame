## General
- [ ] Set version in README.md, Doxyfile, git tag
- [ ] create a logo and add it to the README.md and Doxyfile
- [ ] add a license
- [ ] write a nice readme
- [ ] add a roadmap
- [ ] add a nice documentation
- [ ] add a coding style, also covering documentation style.

## Interface
- [ ] Set default mode: 1280x800 windowed

## Bullets: Second kind of game object that can be created, does not posses substructure but FlightModel
- [x] deletion after timeout
- [ ] impact handling
- [x] deactivate impact test between shot and shooter
- [ ] Damage model:
  - [ ] damage submodule to determine damage dealt
  - [ ] improve Damage.h class and split into damage and modifiers
  - [ ] more details for armour specs
  - [x] destruction of objects
- [ ] remove bullets on impact

## Physics
- [ ] introduce mass handling for ships
- [x] scaling of units! 1unit = 1m seems to small
- [ ] allow adding custom collision filtering info to physic objects (refactor setIgnoreCollisionTarget)
- [ ] add change listeners for physics properties (restitution, friction, ...)

## Event system
- [ ] add generic infrastructure for event handling, within both game and view thread
- [ ] ship destruct event
  - [ ] create exlosion gfx effect
  - [ ] play explosion sound
  - [ ] spawn debris
 
## GFX
- [x] default game view
- [x] object deletion fix
- [x] engine effect
- [ ] explosion effect
- [ ] bullet graphic
- [ ] subsystem status views:
  - [ ] propulsion system panel (engine, tank)
  - [ ] weapons panel
  - [ ] impact info in armour view
  - [ ] sensor component and panel
- [ ] light manager (we'll need that later for nice effects)

## Autopilot submodule: lowest level of micro-ai within game thread
- [ ] set desired position, velocity and orientation
- [ ] find a way to allow communication between engine and autopilot
- [ ] communicate to autopilot

## AI

## Threading
- [x] remove futures from event listener references
- [x] split world into master and slave world
- [x] despawn event
- [x] save handling of object ids
- [ ] events for adding and removing properties
- [ ] events for adding and removing subobjects
- [ ] complete serialization over event stream - no "spawn" in view thread!  
- [ ] remove all threading stuff from listeners?
- [ ] profiling stuff

## Sound

## Refactoring:
- [ ] use boost::range when applicable (boost::any_range!)
- [x] ISpawnManager
- [x] unit conversions
- [ ] manage data types when loading properties from file.
- [x] vertex cache in hull file
- [ ] get rid of dynamic_cast in src/graphic/EngineExhaustAnimator.cpp to use
      irrlicht without changing default compilation flags.
- [x] add a thin wrapper layer around Box2D that provides the most used functions
      in a variant that automatically converts from SI units to Box units.

## Permagoals:
- [ ] improve error handling and logging
- [ ] commenting, doxygen
- [ ] tests!