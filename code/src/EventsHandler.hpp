#pragma once
#include "AbstractWindow.hpp"

namespace sdl_handle
{
  void EventHandle(const SDL_Event &event, IEventActor &actor);
}

class IEventActor
{
public:
  virtual ~IEventActor();

  virtual void OnResize(){};

  virtual void OnMouseUp(const SDL_MouseButtonEvent &){}
  virtual void OnMouseDown(const SDL_MouseButtonEvent &){}
  virtual void OnMouseMotion(const SDL_MouseMotionEvent &) {}
  virtual void OnMouseWheel(const SDL_MouseWheelEvent &) {}
  virtual void OnKeyDown(const SDL_KeyboardEvent &) {}
  virtual void OnKeyUp(const SDL_KeyboardEvent &) {}
};

class CAbstractEventDispatchWindow
        : public CAbstractWindow
        , public IEventActor
{
protected:
    void OnWindowEvent(const SDL_Event &event) final
    {
        sdl_handle::EventHandle(event, *this);
    }
};
