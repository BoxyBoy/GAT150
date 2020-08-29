#pragma once
////<include the system header>
#include "Core/System.h"
#include "Core/Assert.h"
#include <fmod.hpp>

namespace nc
{
	class AudioSystem : public System
	{
	public:
		//<implement System pure virtual functions>

		virtual bool Startup() override;
		virtual void Shutdown() override;
		virtual void Update() override;

	public:
		friend class Sound;

	protected:
		FMOD::System* m_system{ nullptr };

	};
}
