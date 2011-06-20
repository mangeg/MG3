#include "Application.h"
#include "W32Window.h"

using namespace MG3;

class BasicApplication : public Application
{
public:
	BasicApplication();
	
	virtual bool Initialize();
	virtual void Update();
	virtual void Exit();

protected:

	W32Window* m_pWindow;
};