#ifndef CENGINE_H_INCLUDED
#define CENGINE_H_INCLUDED

#include "IEngine.h"

class CIrrMasterEventReceiver;
class CDebugDraw;
class CDebugConsole;
class ITimeManager;

class CEngine : public IEngine
{
	public:
		CEngine();
		virtual ~CEngine() noexcept;

		bool init(bool dbdraw) override;
		bool tick() override;

		IInputManager& getInputManager() override;
		const IInputManager& getInputManager() const override;

		std::shared_ptr<IGUIManager> createGUIManager() const override;

		IGraphixManager& getGraphixManager() override;
		const IGraphixManager& getGraphixManager() const override;

		IDebugDrawer& getDebugDrawer() override;
		const IDebugDrawer& getDebugDrawer() const override;

		IStateManager& getStateManager() override;
		const IStateManager& getStateManager() const override;

		std::shared_ptr<IGameWorld> loadLevel(const std::string& filename) override;
		std::shared_ptr<IGameWorld> createLevel() override;
	private:
		DeviceType* mIrrlichtDevice;

		std::unique_ptr<CDebugConsole> mDebugConsole;
		std::unique_ptr<CDebugDraw> mDebugDrawer;

		std::unique_ptr<IInputManager> mInputManager;
		std::unique_ptr<CIrrMasterEventReceiver> mMasterEventReceiver;
		std::weak_ptr<IGameWorld> mGameWorld;
		std::unique_ptr<IGraphixManager> mGraphixManager;
		std::unique_ptr<ITimeManager> mTimeManager;

		std::unique_ptr<IStateManager> mStateManager;
};

#endif // CENGINE_H_INCLUDED
