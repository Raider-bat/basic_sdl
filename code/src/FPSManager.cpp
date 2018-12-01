#include <iostream>
#include "FPSManager.hpp"


FPSManager::FPSManager()
: m_lastTime(std::chrono::system_clock::now()){}

void FPSManager::LimitFPS(const std::chrono::milliseconds &framePeriod)
{
  std::chrono::system_clock::time_point nextFrameTime = m_lastTime + framePeriod;
  std::this_thread::sleep_until(nextFrameTime);
}

float FPSManager::GrabDeltaTime()
{
	auto newTime = std::chrono::system_clock::now();
	auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - m_lastTime);
	m_lastTime = newTime;
	return 0.001f * float(timePassed.count());
}

void FPSManager::UpdateCurrentFPS()
{
  auto deltaSeconds = GrabDeltaTime();
  currentFps = 1/deltaSeconds;
}
void FPSManager::ShowCurrentFPS() const
{
  std::cerr << "FPS: " << currentFps << std::endl;
}

float FPSManager::GetCurrentFPS() const
{
  return currentFps;
}

float FPSManager::GetTargetFPS() const
{
  return targetFps;
}
