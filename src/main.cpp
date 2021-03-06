#include "CEngine.h"
#include "IStateManager.h"
#include "Options.h"
#include "ShipEditor/ShipEditorState.h"
#include "GameState/GameState.h"
#include <irrlicht/irrlicht.h>
#include <iostream>


using namespace irr;


void cmd_getsettings(Options& opt);


IEngine* getGlobalEngine()
{
	static std::shared_ptr<IEngine> engine = std::make_shared<CEngine>( );
	return engine.get();
}


std::shared_ptr<IState> createShipEditorState(const irr::io::IAttributes* param)
{
	return std::make_shared<ShipEditorState> (getGlobalEngine());
}


std::shared_ptr<IState> createGameState(const irr::io::IAttributes* param)
{
	return std::make_shared<GameState> (getGlobalEngine());
}


int main(int argc, char *argv[])
{
	Options opt;
	auto device = irr::createDevice(irr::video::EDT_NULL);
	if (device->getFileSystem()->existFile("config.xml")) {
		// Attribute laden
		irr::io::IAttributes* att= device->getFileSystem()->createEmptyAttributes();
		irr::io::IXMLReader* reader = device->getFileSystem()->createXMLReader("config.xml");
		att->read(reader);

		opt.deserializeAttributes(att);

		att->drop();
		reader->drop();
	} else {
		cmd_getsettings(opt);

		irr::io::IAttributes* att= device->getFileSystem()->createEmptyAttributes();
		irr::io::IXMLWriter* writer= device->getFileSystem()->createXMLWriter("config.xml");
		opt.serializeAttributes(att);

		att->write(writer, true);

		att->drop();
		writer->drop();
	}
	// basic setup
	try {
		auto engine = getGlobalEngine();

		// create irrlicht
		if (!engine->init(opt))
			return 1;

		engine->getStateManager().addFactory("ShipEditor", createShipEditorState);
		engine->getStateManager().addFactory("GameState", createGameState);
		engine->getStateManager().createState("GameState", nullptr);

		// main game loop
		while(engine->tick());

	} catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}

	std::cout << "SHUT DOWN\n";

	return 0;
}


void cmd_getsettings(Options& opt)
{
	std::cout << "Game Controls:\n"
	          << "\tArrow up/down: engine power\n"
	          << "\tArrow left/right: rotate\n"
	          << "\tSpace: Primary Weapon\n"
	          << "\tR Ctrl: Secondary Weapon\n"
	          << "\t+- (keyboard) Radar Range\n"
	          << "\tK, L: Target Lock\n"
	          << "\tR Shift: Afterburner\n"
	          << "\t<,Y dodge\n"
	          << "\t. Switch missile type\n\n\n";

	std::cout << "This game is still in early alpha stages,"
	          << "many features are still missing and is probably full of bugs.\n\n";

	std::cout << "Select Mode\n"
	          << "\ta)\tOpenGL 800 x 600\n"
	          << "\tb)\tOpenGL 1024 x 768\n"
	          << "\tc)\tOpenGL 1280 x 800\n"
	          << "\td)\tOpenGL 1368 x 766\n"
	          << "\te)\tOpenGL 1920 x 1080\n";

	char c;
	std::cin >> c;

	switch(c) {
	case 'a':
	default:
		opt.setDriverType(video::EDT_OPENGL);
		opt.setViewportSize(irr::core::dimension2d<u32>(800, 600));
		opt.setColorDepth(32);
		break;
	case 'b':
		opt.setDriverType(video::EDT_OPENGL);
		opt.setViewportSize(irr::core::dimension2d<u32>(1024, 768));
		opt.setColorDepth(32);
		break;
	case 'c':
		opt.setDriverType(video::EDT_OPENGL);
		opt.setViewportSize(irr::core::dimension2d<u32>(1280, 800));
		opt.setColorDepth(32);
		break;
	case 'd':
		opt.setDriverType(video::EDT_OPENGL);
		opt.setViewportSize(irr::core::dimension2d<u32>(1368, 768));
		opt.setColorDepth(32);
		break;
	case 'e':
		opt.setDriverType(video::EDT_OPENGL);
		opt.setViewportSize(irr::core::dimension2d<u32>(1920, 1080));
		opt.setColorDepth(32);
		break;
	}

	std::cout << "Full Screen (y/n)?\n";
	std::cin >> c;

	if(c == 'y' || c == 'j' || c == '1')
		opt.setFullscreen(true);
}
