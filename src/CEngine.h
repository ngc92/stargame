#ifndef CENGINE_H_INCLUDED
#define CENGINE_H_INCLUDED

#include "IEngine.h"

class CIrrMasterEventReceiver;
class CDebugConsole;
class ITimeManager;

class CEngine : public IEngine
{
	public:
		CEngine();
		virtual ~CEngine() noexcept;

		bool init(const Options& options) override;
		bool tick() override;

		IInputManager& getInputManager() override;
		const IInputManager& getInputManager() const override;

		IGUIEnvironment* getGUIEnvironment() const override;

		IStateManager& getStateManager() override;
		const IStateManager& getStateManager() const override;

		ISoundManager& getSoundManager() override;
		const ISoundManager& getSoundManager() const override;

	private:
		DeviceType* mIrrlichtDevice;

		std::unique_ptr<CDebugConsole> mDebugConsole;

		std::unique_ptr<IInputManager> mInputManager;
		std::unique_ptr<ITimeManager> mTimeManager;
		std::unique_ptr<IStateManager> mStateManager;
		std::unique_ptr<ISoundManager> mSoundManager;

		std::unique_ptr<CIrrMasterEventReceiver> mMasterEventReceiver;
};

#endif // CENGINE_H_INCLUDED
