# script for setting up standalone environment, i.e. without installing
# irrlich, irrKlang and Box2D.
#
# usage:
# in Stargame base dir, source this file:
# source setup.sh

if [ "x$STARGAME_BASE" != "x" ]; then
	echo "Standalone environment already loaded"
	return
fi

export STARGAME_BASE=$PWD
LD_LIBRARY_PATH_APPEND=$STARGAME_BASE/external/irrlicht-lib:$STARGAME_BASE
LD_LIBRARY_PATH_APPEND=$STARGAME_BASE/external/irrklang-lib:$LD_LIBRARY_PATH_APPEND
LD_LIBRARY_PATH_APPEND=$STARGAME_BASE/external/Box2D/Box2D/BuildLinux/Box2D:$LD_LIBRARY_PATH_APPEND

if [ "x$LD_LIBRARY_PATH" = "x" ]; then
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH_APPEND
else
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH_APPEND:$LD_LIBRARY_PATH
fi

# install external libraries
sh +x installExternals.sh
