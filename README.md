# stargame
yep, that's the name for now!


## playing
Control your ship with the arrow keys. Shoot with "C".


## Compiling and Running

### On GNU/Linux

Source the setup script and run the Makefile:

    source setup.sh
    make -jN

With N the number of your CPU cores + 1.

If you want to compile for debug:

    make DEBUG=1 -jN

To run the game:

    ./bin/release/Stargame

or the debug version:

    ./bin/debug/Stargame


### On Windows

???