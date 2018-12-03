#include "Window.hpp"
#include <SDL.h>

namespace
{
  const glm::ivec2 WINDOW_SIZE {800, 600};
  const char WINDOW_TITLE[] = "TestApp";
  const char WINDOW_FAIL_TITLE[]  = "Error Message";
}


int main()
{
  try
  {
    CWindow window;
    window.Show(WINDOW_SIZE, WINDOW_TITLE);
    window.DoGameLoop();
  }
  catch (const std::exception &ex)
  {
    const char *message = ex.what();
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, WINDOW_FAIL_TITLE, message, nullptr);
  }
    return 0;
}
