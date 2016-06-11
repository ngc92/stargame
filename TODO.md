## Interface
- [ ] Fix selection mode buggy text

## Bullets: Second kind of game object that can be created, does not posses substructure but FlightModel
- [x] deletion after timeout
- [ ] impact handling
- [x] deactivate impact test between shot and shooter
- [ ] Damage model:
  - [ ] damage submodule to determine damage dealt
  - [ ] improve Damage.h class and split into damage and modifiers
  - [ ] more details for armour specs
  - [x] destruction of objects

## Physics
- [ ] introduce mass handling for ships
- [ ] scaling of units! 1unit = 1m seems to small
 
## GFX
- [ ] default game view
- [x] object deletion fix
- [ ] engine effect
- [ ] subsystem status views:
  - [ ] propulsion system panel (engine, tank)
  - [ ] weapons panel
  - [ ] impact info in armour view
  - [ ] sensor component and panel

## Autopilot submodule: lowest level of micro-ai within game thread
- [ ] set desired position, velocity and orientation
- [ ] find a way to allow communication between engine and autopilot
- [ ] communicate to autopilot

## Refactoring:
- [ ] use boost::range when applicable (boost::any_range!)
- [ ] ISpawnManager
- [ ] unit conversions
- [ ] manage data types when loading properties from file.
- [x] vertex cache in hull file

## Permagoals:
- [ ] improve error handling and logging
- [ ] commenting, doxygen
- [ ] tests!
- [ ] add a readme
