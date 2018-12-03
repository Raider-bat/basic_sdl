#pragma once

#include "EventsHandler.hpp"

class CWindow: public CAbstractEventDispatchWindow
{
public:
  CWindow();
protected:
  void OnWindowInit(const glm::ivec2 &size) override ;
  void OnUpdateWindow(float deltaSeconds) override;
  void OnDrawWindow(const glm::ivec2 &size) override;

  void OnKeyDown(const SDL_KeyboardEvent &) override;
private:
  void SetupView(const glm::ivec2 &size);
};
