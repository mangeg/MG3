//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|

//------------------------------------------------------------------------|
namespace MG3
{
	class Timer
	{
	public:
		Timer();
		virtual ~Timer();

		void Reset();
		void Update();
		void Stop();
		void Start();
		bool Toggle();
		void SetFixed(double rate);

		double GameTime();
		double TotalTime();
		double Delta();

		int	FrameRate();
		int MaxFrameRate();

	protected:

		bool	m_bPaused;
		bool	m_bUseFixedDelta;

		double	m_dDelta;
		double	m_dMSPerFrame;
		double	m_dMSInv;
		double	m_dSecondsPerTick;
		double	m_dFixedDelta;

		int		m_iFrameCount;
		int		m_iCurrentFrameRate;
		int		m_iMaxFrameRate;

		unsigned __int64 m_iTicksPerSecond;
		unsigned __int64 m_iInitialTicks;
		unsigned __int64 m_iCurrentTicks;
		unsigned __int64 m_iLastTicks;
		unsigned __int64 m_iOneSecondTicks;
		unsigned __int64 m_iStopTime;
		unsigned __int64 m_iTotalStoppedTime;
	};
}