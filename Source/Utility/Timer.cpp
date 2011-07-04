//------------------------------------------------------------------------|
#include "StdAfx.h"
#include "Timer.h"
//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
Timer::Timer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_iTicksPerSecond);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iInitialTicks);

	m_iLastTicks = m_iCurrentTicks = m_iOneSecondTicks = m_iInitialTicks;

	m_iTotalStoppedTime = 0;
	m_iStopTime = 0;
	m_iMaxFrameRate = 0;
	m_iFrameCount = 0;
	m_iCurrentFrameRate = 0;

	m_bPaused = false;
	m_bUseFixedDelta = false;

	m_dDelta = 0.0f;
	m_dFixedDelta = 0.0f;
	m_dMSPerFrame = 0.0f;
	m_dSecondsPerTick = 1 / (double)m_iTicksPerSecond;
	m_dMSInv = 1 / 1000;
}
//------------------------------------------------------------------------|
Timer::~Timer()
{
}
//------------------------------------------------------------------------|
void Timer::Update()
{
	if(m_bPaused)
	{
		m_dDelta = 0.0f;
		return;
	}

	m_iLastTicks = m_iCurrentTicks;
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iCurrentTicks);

	if(m_bUseFixedDelta)
	{
		m_dDelta = m_dFixedDelta;		
	}
	else
	{
		m_dDelta = (m_iCurrentTicks - m_iLastTicks) * m_dSecondsPerTick;
	}

	double t = 1 / m_dDelta;

	if(m_dDelta < 0.0)
	{
		m_dDelta = 0.0f;
		m_dMSPerFrame = 0.0f;
	}

	if(m_dDelta > 0)
	{
		m_dMSPerFrame = 1000 / (1/m_dDelta);
	}


	if((m_iCurrentTicks - m_iOneSecondTicks) * m_dSecondsPerTick < 0.5)
	{
		m_iFrameCount++;
	}
	else
	{
		m_iCurrentFrameRate = m_iFrameCount * 2;		

		if(m_iCurrentFrameRate > m_iMaxFrameRate)
			m_iMaxFrameRate = m_iCurrentFrameRate;

		m_iFrameCount = 0;
		m_iOneSecondTicks = m_iCurrentTicks;
	}
}
//------------------------------------------------------------------------|
void Timer::Start()
{
	if(m_bPaused)
	{
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		m_iTotalStoppedTime += startTime - m_iStopTime;
		m_iLastTicks = startTime;
		m_iStopTime = 0;
		m_bPaused = false;
	}
}
//------------------------------------------------------------------------|
void Timer::Stop()
{
	if(!m_bPaused)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_iStopTime = currTime;
		m_bPaused = true;
	}
}
//------------------------------------------------------------------------|
bool Timer::Toggle()
{
	if(m_bPaused)
	{
		Start();
	}
	else
	{
		Stop();
	}
	return m_bPaused;
}
//------------------------------------------------------------------------|
void Timer::SetFixed(double rate)
{
	if(rate <= 0)
	{
		m_bUseFixedDelta = false;
		m_dFixedDelta = 0.0f;
	}
	else
	{
		m_bUseFixedDelta = true;
		m_dFixedDelta = rate;
	}
}
//------------------------------------------------------------------------|
double Timer::GameTime()
{
	return (m_iCurrentTicks - m_iInitialTicks - m_iTotalStoppedTime) * m_dSecondsPerTick;
}
//------------------------------------------------------------------------|
double Timer::TotalTime()
{
	return (m_iCurrentTicks - m_iInitialTicks) * m_dSecondsPerTick;
}
//------------------------------------------------------------------------|
int Timer::FrameRate()
{
	return m_iCurrentFrameRate;
}
//------------------------------------------------------------------------|
int Timer::MaxFrameRate()
{
	return m_iMaxFrameRate;
}
//------------------------------------------------------------------------|