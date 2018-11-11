#include <iostream>
#include <SDL.h>

bool init(const char*, int, int, int, int, int);
void render();
void handleEvents();
void clean();

SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;
bool g_bRunning = false;


int main(int argc, char const *argv[]) {

  init("Test Window", 0, 0, 400, 600, SDL_WINDOW_SHOWN);
  while (g_bRunning)
  {
    render();
    handleEvents();
  }

	clean();
	return 0;
}

bool init (const char* title, int xpos,int ypos, int height, int width, int flags)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
  {
    // FIXME: передача параметров экрана через аргументы
    //SDL_DisplayMode displayMode;
    //int request = SDL_GetDesktopDisplayMode(0,&displayMode);

    g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
    if (g_pWindow != nullptr)
    {
      g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (g_pRenderer == nullptr)
      {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
      }
    }
    else
    {
      std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
      return false;
    }
  }
  else
  {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }
  g_bRunning = true;
  return true;
}

void render() //функция для отрисовки
{
  // Применяем желтый цвет для рендера
  SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 0, 255);

  // очищаем окно в желтый цвет
  SDL_RenderClear(g_pRenderer); //Очистка рендера

  // Показываем окно
  SDL_RenderPresent(g_pRenderer);
}

void handleEvents()// отлов событий
{
  SDL_Event event;
  if (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        g_bRunning = false;
        break;

      default:
        break;
    }
  }
}

void clean() // очищение ресурсов
{
  SDL_DestroyWindow(g_pWindow); //Удаляем окно
  SDL_DestroyRenderer(g_pRenderer); //Удаляем рендер
  SDL_Quit(); //Выходим из рендера
}
