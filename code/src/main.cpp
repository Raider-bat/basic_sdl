#include "AbstractWindow.h"
#include <SDL.h>
#include <iostream>

class CWindow : public CAbstractWindow
{
protected:
    void OnWindowEvent(const SDL_Event &event) override
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_r:
              SetBackgroundColor({1, 0, 0, 1});
              std::cout << "INFO: U press r, change color red" << '\n';
                break;
            case SDLK_g:
                SetBackgroundColor({0, 1, 0, 1});
                std::cout << "INFO: U press g, change color green" << '\n';
                break;
            case SDLK_b:
                SetBackgroundColor({0, 0, 1, 1});
                std::cout << "INFO: U press b, change  color blue" << '\n';
                break;
            }
        }
    }

    void OnUpdateWindow(float deltaSeconds) override
    {
      std::cout << "FPS: " <<1/deltaSeconds<< '\n';
        (void)deltaSeconds;
    }

    void OnDrawWindow() override
    {
    }
};


int main()
{
    CWindow window;
    window.ShowFixedSize( {800, 600} );
    window.DoGameLoop();


}
