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
<<<<<<< HEAD
  float GetTargetFPS();

private:
=======
  float GetLimitFPS();

private:

>>>>>>> dff4130033fe7b80f6efc9f0c876fca2693c8d2a
  float currentFps; //value of current fps
  float targetFps;

  static const float MIN_FPS (15.0);
  static const float MAX_FPS (60.0);
};
