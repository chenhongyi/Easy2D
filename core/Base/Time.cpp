#include "..\e2dbase.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// 时钟频率
static LARGE_INTEGER s_tFreq;
// 游戏开始时间
static LARGE_INTEGER s_tStart;
// 当前时间
static LARGE_INTEGER s_tNow;
// 上一帧刷新时间
static LARGE_INTEGER s_tFixedUpdate;
// 上一次更新时间
static LARGE_INTEGER s_tLastUpdate;
// 每一帧间隔
static LONGLONG s_tExceptedInvertal;

// 上一帧与当前帧的时间间隔
static unsigned int s_nInterval = 0;
// 游戏开始时长
static unsigned int s_nTotalTime = 0;


double e2d::Time::getTotalTime()
{
	return s_nTotalTime / 1000.0;
}

unsigned int e2d::Time::getTotalTimeMilliseconds()
{
	return s_nTotalTime;
}

double e2d::Time::getDeltaTime()
{
	return s_nInterval / 1000.0;
}

unsigned int e2d::Time::getDeltaTimeMilliseconds()
{
	return s_nInterval;
}

bool e2d::Time::__init()
{
	::timeBeginPeriod(1);					// 修改时间精度
	::QueryPerformanceFrequency(&s_tFreq);	// 获取时钟频率
	::QueryPerformanceCounter(&s_tNow);		// 刷新当前时间
	s_tStart = s_tLastUpdate = s_tFixedUpdate = s_tNow;
	s_tExceptedInvertal = 15LL * s_tFreq.QuadPart / 1000LL;
	return true;
}

void e2d::Time::__uninit()
{
	::timeEndPeriod(1);	// 重置时间精度
}

bool e2d::Time::__isReady()
{
	return s_tExceptedInvertal < (s_tNow.QuadPart - s_tFixedUpdate.QuadPart);
}

void e2d::Time::__updateNow()
{
	::QueryPerformanceCounter(&s_tNow);
}

void e2d::Time::__updateLast()
{
	s_tFixedUpdate.QuadPart += s_tExceptedInvertal;
	s_tLastUpdate = s_tNow;

	::QueryPerformanceCounter(&s_tNow);
	s_nInterval = static_cast<unsigned int>((s_tNow.QuadPart - s_tLastUpdate.QuadPart) * 1000LL / s_tFreq.QuadPart);
	s_nTotalTime = static_cast<unsigned int>((s_tNow.QuadPart - s_tStart.QuadPart) * 1000LL / s_tFreq.QuadPart);
}

void e2d::Time::__sleep()
{
	// 计算挂起时长
	int nWaitMS = 16 - static_cast<int>((s_tNow.QuadPart - s_tFixedUpdate.QuadPart) * 1000LL / s_tFreq.QuadPart);
	// 挂起线程，释放 CPU 占用
	if (nWaitMS > 1)
	{
		::Sleep(nWaitMS);
	}
}
