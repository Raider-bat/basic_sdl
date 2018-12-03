#include "EventsHandler.hpp"

namespace
{
glm::vec2 GetMousePosition(const SDL_MouseButtonEvent &event)
{
    return { event.x, event.y };
}

glm::vec2 GetMousePosition(const SDL_MouseMotionEvent &event)
{
    return { event.x, event.y };
}
}

void sdl::EventHandle(const SDL_Event &event,IEventActor &actor)
{
  switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
      actor.OnMouseDown(event.button);
      break;
    case SDL_MOUSEBUTTONUP:
      actor.OnMouseUp(event.button);
      break;
    case SDL_MOUSEMOTION:
      actor.OnMouseMotion(event.motion);
      break;
    case SDL_MOUSEWHEEL:
      actor.OnMouseWheel(event.wheel);
      break;
    case SDL_KEYDOWN:
      actor.OnKeyDown(event.key);
      break;
    case SDL_KEYUP:
      actor.OnKeyUp(event.key);
      break;
   }
}
