#pragma once

#include "Window.h"

namespace MG3
{
	class W32Window : public Window
	{
	public:
		W32Window();
		virtual ~W32Window();

		virtual void Initialize();
		virtual void Exit();
		virtual void Paint();
	};
}