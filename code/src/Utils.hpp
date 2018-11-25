#pragma once
#include <chrono>
#include <cstring>
#include <GL/glu.h>


class CUtils
{
public:
  CUtils() = delete;

  static void InitOnceSDL2();
  static void ValidateSDL2Errors();
  static void ValidateOpenGLErrors();
};

class CChronometer
{
public:
	CChronometer();
	float GrabDeltaTime();

private:
	std::chrono::time_point<std::chrono::system_clock> m_lastTime;
};
