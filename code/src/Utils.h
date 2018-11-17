#pragma once
#include <chrono>
class CUtils
{
public:
  CUtils() = delete;

  static void InitOnceSDL2();
  static void ValidateSDL2Errors();

};

class CChronometer
{
public:
	CChronometer();
	float GrabDeltaTime();

private:
	std::chrono::time_point<std::chrono::system_clock> m_lastTime;
};
