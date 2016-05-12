#!/bin/sh

if [ ! -d ./external ]; then
	mkdir external
fi


# install irrlich
if [ ! -h external/irrlicht ]; then
	irrlich_rev=5296
	echo "Getting and extracting Irrlicht at revision ${irrlich_rev}"
	cd ./external/
	wget -q https://sourceforge.net/code-snapshots/svn/i/ir/irrlicht/code/irrlicht-code-${irrlich_rev}-trunk.zip
	unzip -qq irrlicht-code-${irrlich_rev}-trunk.zip
	rm irrlicht-code-${irrlich_rev}-trunk.zip
	cd irrlicht-code-${irrlich_rev}-trunk/source/Irrlicht
	sed -i -e "s/-O3/-O3 -march=native/g" Makefile
	make NDEBUG=1 sharedlib -j 5
	cd ../../..
	ln -s irrlicht-code-${irrlich_rev}-trunk/ irrlicht
	cd ..
	echo "Irrlich revision ${irrlich_rev} installed as a shared lib"
	echo ""
else
	echo "Irrlicht installed"
	echo ""
fi


# install irrklang
if [ ! -h ./external/irrKlang ]; then
	klang_ver=64bit-1.5.0
	echo "Getting irrklang ${klang_ver}"
	cd ./external
	wget -q http://www.ambiera.at/downloads/irrKlang-${klang_ver}.zip
	unzip -qq irrKlang-${klang_ver}.zip
	rm irrKlang-${klang_ver}.zip
	ln -s irrKlang-${klang_ver} irrKlang
	cd ..
	echo "IrrKlang ${klang_ver} installed as a shared lib"
	echo ""
else
	echo "IrrKlang installed"
	echo ""
fi


# install box2d
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
