#pragma once

#include "MG3.h"

namespace MG3
{
	class Application
	{
	public:
		Application();

		static Application* GetApplication();

		virtual bool Initialize() = 0;
		virtual void Update() = 0;
		virtual void Exit() = 0;

	protected:
		static Application* ms_pAppliction;
	};
}
