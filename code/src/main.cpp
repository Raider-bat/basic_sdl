#include <iostream>
#include <SDL.h>

int main(int argc, char const *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  else
    std::cout << "Succsess compile! " << '\n';
    std::cout <<" Изменение файла" << '\n';
	SDL_Quit();
	return 0;
}
