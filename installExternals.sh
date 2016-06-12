#!/bin/sh

if [ ! -d ./external ]; then
	mkdir external
fi


# install irrlich
if [ ! -h external/irrlicht ]; then
	irrlicht_rev=1.9.0
	echo "Getting and extracting Irrlicht from svn trunk"
	cd ./external/
	svn checkout http://svn.code.sf.net/p/irrlicht/code/trunk irrlicht-code
	cd irrlicht-code/source/Irrlicht
	sed -i -e "s/-O3/-O3 -march=native/g" Makefile
	make NDEBUG=1 sharedlib -j 5
	cd ../../
	cd lib/Linux
	ln -s libIrrlicht.so.${irrlicht_rev} libIrrlicht.so
	ln -s libIrrlicht.so.${irrlicht_rev} libIrrlicht.so.1.9
	cd ../../
	cd ..
	ln -s irrlicht-code/include irrlicht
	ln -s irrlicht-code/lib/Linux irrlicht-lib
	cd ..
	echo "Irrlich revision ${irrlicht_rev} installed as a shared lib"
	echo ""
else
	echo "Irrlicht installed"
	echo ""
fi


# install irrklang
cd $STARGAME_BASE
if [ ! -h ./external/irrklang ]; then
	klang_ver=64bit-1.5.0
	echo "Getting irrklang ${klang_ver}"
	cd ./external/
	wget -q http://www.ambiera.at/downloads/irrKlang-${klang_ver}.zip
	unzip -qq irrKlang-${klang_ver}.zip
	rm irrKlang-${klang_ver}.zip
	ln -s irrKlang-${klang_ver}/include irrklang
	ln -s irrKlang-${klang_ver}/bin/linux-gcc-64 irrklang-lib
	cd ..
	echo "IrrKlang ${klang_ver} installed as a shared lib"
	echo ""
else
	echo "IrrKlang installed"
	echo ""
fi


# compile Box2D
cd $STARGAME_BASE
if [ ! -d ./external/Box2D/Box2D/BuildLinux ]; then
	cd external/Box2D/Box2D/
	mkdir BuildLinux
	cd BuildLinux
	cmake -D BOX2D_BUILD_SHARED=ON -D BOX2D_BUILD_STATIC=OFF -D BOX2D_BUILD_EXAMPLES=OFF -D CMAKE_CXX_FLAGS="-O2 -march=native -std=c++11" ..
	make -j 5
else
	echo "Box2D installed"
	echo ""
fi
