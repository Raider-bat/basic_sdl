#pragma once

#include "Utils.hpp"
#include <chrono>
#include <thread>

class FPSManager
{
public:
  FPSManager();

  void LimitFPS(const std::chrono::milliseconds &framePeriod);
  float GrabDeltaTime();
  void UpdateCurrentFPS();
  void ShowCurrentFPS() const;
  void SetTargetFPS();
  float GetCurrentFPS() const;
  float GetTargetFPS() const;

private:
  float currentFps; //value of current fps
  float targetFps;
  std::chrono::time_point<std::chrono::system_clock> m_lastTime;
  const  float MIN_FPS = 15.0;
  const  float MAX_FPS = 60.0;
  //static const float;
};
