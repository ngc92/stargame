#include "Options.h"
#include <iostream>
/*#include "Game.h"

#include "SoundOptions.h"
*/
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Standardeinstellungen
Options::Options():					driverType(irr::video::EDT_NULL),
									size(irr::core::dimension2d<irr::s32>(400,300)),
									fullscreen(false),
									colorDepth(24)
{
}

//Funktionen zum Auslesen und Setzen
// Driver Type
void  Options::setDriverType(irr::video::E_DRIVER_TYPE dt){
	if(driverType != dt)
		mustReset = true;
	driverType = dt;
}

irr::video::E_DRIVER_TYPE Options::getDriverType() const{
	return driverType;
}

// Aufl�sung
void Options::setViewportSize(irr::core::dimension2d<u32> nsize) {
	if(nsize != size)
		mustReset = true;
	size = nsize;
}

irr::core::dimension2d<u32> Options::getViewportSize() const {
	return size;
}

// Vollbildmodus
void Options::setFullscreen(bool fscreen) {
	if(fullscreen!=fscreen)
		mustReset = true;
	fullscreen = fscreen;
}
bool Options::getFullscreen() const {
	return fullscreen;
}

// Farbtiefe
void Options::setColorDepth(irr::s32 dpt){
	if(dpt != colorDepth)
		mustReset = true;
	colorDepth = dpt;
}
irr::s32 Options::getColorDepth() const{
	return colorDepth;
}

// -------------------------------------------------------------------------------------------------

bool Options::getReset() const{
	return mustReset;
}

// IrrlichtDevice mit den Anforderungen erstellen
irr::IrrlichtDevice* Options::startDevice() const {
	irr::IrrlichtDevice* d = irr::createDevice(driverType, size, colorDepth, fullscreen, false, false, 0);
//	mustReset = false;
	if( d == 0 ) {
		std::cerr << "\nCould not create device! Please check options.xml!\n";
		std::cout << "\n\n\n\aCould not create device! Please check options.xml!\n\tType h for more information!\n\t";
		char h;
		std::cin >> h;
		if(h == 'h'){
			std::cout<<	"The engine could not create a device. Maybe the settings are not correct. "
						"Look at the values of driverType, viewportWidth, viewportHeight and colorDepth. "
						"Probably one of these values is not correct or not supported by your system. Try to fix "
						"it by yourself or delete the file and restart the game and set the values using the appearing dialog.\n"
						"\nPess d to get a list of all aviable driver types\nPress any other key "
						"to quit the game\n";
			char d;
			std::cin >> d;
			if(d == 'd'){
				getchar(); //ENTER abfangen
				std::cout<<	"\nAviable driver types:\n\tSOFTWARE\t-\tVery dirty but should run on all platforms\n"
							"\tBURNINGSVIDEO\t-\tBetter quality than SOFTWARE but slower\n"
							"\tOpenGL\t\t-\tFast hardware accelerated renderer, available on most platforms\n"
							"Press any key to shut down the game\n";
				getchar();
			}
		}
		exit(-1);
	}
	return d;
}

//! Writes attributes of the scene node.
void Options::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const{
	IAttributeExchangingObject::serializeAttributes(out, options);
	const char* dTL[7];
	dTL[0] = "NULL";
	dTL[1] = "SOFTWARE";
	dTL[2] = "BURNINGSVIDEO";
	dTL[3] = "DIRECT3D8";
	dTL[4] = "DIRECT3D9";
	dTL[5] = "OPENGL";
	dTL[6] = 0;

	out->addEnum("driverType", driverType, dTL);
	out->addInt("viewportWidth", size.Width);
	out->addInt("viewportHeight", size.Height);
	out->addInt("colorDepth", colorDepth);
	out->addBool("fullscreen", fullscreen);
}


//! Reads attributes of the scene node.
void Options::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options){
	const char* enumvs[7];
	enumvs[0] = "NULL";
	enumvs[1] = "SOFTWARE";
	enumvs[2] = "BURNINGSVIDEO";
	enumvs[3] = "DIRECT3D8";
	enumvs[4] = "DIRECT3D9";
	enumvs[5] = "OPENGL";
	enumvs[6] = 0;

	IAttributeExchangingObject::deserializeAttributes(in, options);
	driverType = E_DRIVER_TYPE(in->getAttributeAsEnumeration("driverType", enumvs));
	size.Width = in->getAttributeAsInt("viewportWidth");
	size.Height = in->getAttributeAsInt("viewportHeight");
	colorDepth = in->getAttributeAsInt("colorDepth");
	fullscreen = in->getAttributeAsBool("fullscreen");
}
