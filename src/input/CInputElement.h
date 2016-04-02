#ifndef CINPUTELEMENT_H_INCLUDED
#define CINPUTELEMENT_H_INCLUDED

#include "IInputElement.h"
#include <mutex>
#include <atomic>

namespace input
{
    class CInputElement: public virtual IInputElement
    {
	public:
		CInputElement(std::string name, float value);

		float value() const override;
		const std::string& name() const override;
		void update() override;

	protected:
		virtual float getNewValue() = 0;

		const std::string mName;
        std::atomic<float> mValue;
        std::mutex mMutex;
    };
}

#endif // CINPUTELEMENT_H_INCLUDED
