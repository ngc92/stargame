#!/bin/sh

if [ ! -d ./external ]; then
	mkdir external
fi


# install irrlich
if [ ! -h external/irrlicht ]; then
	irrlicht_rev=1.8.3
	echo "Getting and extracting Irrlicht ${irrlicht_rev}"
	cd ./external/
	wget http://kent.dl.sourceforge.net/project/irrlicht/Irrlicht%20SDK/${irrlicht_rev:0:3}/${irrlicht_rev}/irrlicht-${irrlicht_rev}.zip
	unzip -qq irrlicht-${irrlicht_rev}.zip
	rm irrlicht-${irrlicht_rev}.zip
	cd irrlicht-${irrlicht_rev}/source/Irrlicht
	sed -i -e "s/-O3/-O3 -march=native/g" Makefile
	make NDEBUG=1 sharedlib -j 5
	cd ../../
	ln -s libIrrlicht.so.${irrlicht_rev} lib/Linux/libIrrlicht.so
	cd ..
	ln -s irrlicht-${irrlicht_rev}/include irrlicht
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
	cd ..
	echo "IrrKlang ${klang_ver} installed as a shared lib"
	echo ""
else
	echo "IrrKlang installed"
	echo ""
fi


# install box2d
cd $STARGAME_BASE
if [ ! -d external/Box2D ]; then
	echo "Getting box2d"
	cd ./external
	git clone -q https://github.com/erincatto/Box2D.git
	cd Box2D/Box2D
	mkdir BuildLinux
	cd BuildLinux
	cmake -D BOX2D_BUILD_SHARED=ON -D BOX2D_BUILD_STATIC=OFF -D BOX2D_BUILD_EXAMPLES=OFF -D CMAKE_CXX_FLAGS="-O3 -march=native -std=c++11" ..
	make -j 5
	cd ../../../..
	echo $PWD
else
	echo "Box2d installed"
	echo ""
fi
