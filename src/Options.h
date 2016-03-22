#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#include <irrlicht/irrlicht.h>

class Options: public irr::io::IAttributeExchangingObject {
	private:
		//Graphikoptionen / Performance
		//Speichert den verwendeten Driver
		irr::video::E_DRIVER_TYPE driverType;

		//Größe des Fensters / Videomodus
		irr::core::dimension2d<irr::u32> size;

		//Vollbild?
		bool fullscreen;

		//Farbtiefe
		irr::s32 colorDepth;

		//True, wenn das Device neu gestartet werden muss
		bool mustReset;

	public:
		//Konstruktor
		Options();

		//Funktionen zum Auslesen und Setzen
		void setDriverType(irr::video::E_DRIVER_TYPE dt);
		irr::video::E_DRIVER_TYPE getDriverType() const;

		void setViewportSize(irr::core::dimension2d<irr::u32> size);
		irr::core::dimension2d<irr::u32> getViewportSize() const;

		void setFullscreen(bool fscreen);
		bool getFullscreen() const;

		void setColorDepth(irr::s32 dpt);
		irr::s32 getColorDepth() const;

		bool getReset() const;

		//Device mit den Einstellungen starten
		irr::IrrlichtDevice* startDevice() const;

		//
		void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const;
		void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0);
};

#endif // OPTIONS_H_INCLUDED
