#pragma once

#include "CUtils"
#include <chrono>
#include <thread>

class FPSManager()
{
public:
  void LimitFPS(float _fps);
  void ShowCurrentFPS();
  float GetCurrentFPS();
  float GetTargetFPS();

private:
  float currentFps; //value of current fps
  float targetFps;

  static const float MIN_FPS (15.0);
  static const float MAX_FPS (60.0);
};
