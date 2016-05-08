#include "CEngine.h"
#include "CStateManager.h"
#include "CInputManager.h"
#include "CSoundManager.h"
#include "CIrrMasterEventReceiver.h"
#include "CTimeManager.h"
#include "Options.h"
#include "debug/CDebugConsole.h"
#include "IState.h"

using namespace irr;

CEngine::CEngine() :	mIrrlichtDevice( nullptr ),
						mDebugConsole( make_unique<CDebugConsole>() ),
						mInputManager( make_unique<CInputManager>() ),
						mStateManager ( make_unique<CStateManager>(this) ),
						mSoundManager( make_unique<CSoundManager>() ),
						mMasterEventReceiver(make_unique<CIrrMasterEventReceiver>(mInputManager.get(), mStateManager.get()))
{
}

CEngine::~CEngine() noexcept
{
}

bool CEngine::init(const Options& options)
{
	// init debug console
	///! \todo add debug commands
	mDebugConsole->startConsole();
	// create things depending on irrlicht
	mIrrlichtDevice = options.startDevice();
	mMasterEventReceiver->setDevice(mIrrlichtDevice);
	mTimeManager = make_unique<CTimeManager>( );

	return mIrrlichtDevice;
}

bool CEngine::tick()
{
	if(mIrrlichtDevice->run())
	{
		mDebugConsole->step();
		if(!mStateManager->step())
		{
			return false;
		};

		if(mTimeManager->waitTillNextFrame() || true)
		{
			mIrrlichtDevice->getVideoDriver()->beginScene(true, true, video::SColor(0,0,0,0));
			
			// called after engine drawing is finished
			mStateManager->getCurrentState()->onDraw();

			mIrrlichtDevice->getVideoDriver()->endScene();
		}
		 else
		{
			LOG_MESSAGE(ELogCategory::ELC_IRRLICHT, "dropped frame!");
		}
		return true;
	}

	return false;
}

IGUIEnvironment* CEngine::getGUIEnvironment() const
{
	return mIrrlichtDevice->getGUIEnvironment();
}

DeviceType& CEngine::getIrrlichDevice() const
{
	return *mIrrlichtDevice;
}

//! this macro generates the getter function for the different managers in CEngine
#define MAKE_GETTER(name)\
I##name& CEngine::get##name(){ \
return *(m##name); } \
const I##name& CEngine::get##name() const { \
return *(m##name); }

MAKE_GETTER(StateManager);
MAKE_GETTER(InputManager);
MAKE_GETTER(SoundManager);

