#include "AbstractWindow.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <GL/glu.h>

namespace
{
const char WINDOW_TITLE[] = "TestApp";
}

namespace detail
{
struct SDLWindowDeleter
{
	void operator()(SDL_Window *ptr)
	{
		SDL_DestroyWindow(ptr);
	}
};
struct SDLGLContextDeleter
{
	void operator()(SDL_GLContext ptr)
	{
		SDL_GL_DeleteContext(ptr);
	}
};
}

// Используем unique_ptr с явно заданным функтором удаления вместо delete.
using SDLWindowPtr = std::unique_ptr<SDL_Window, detail::SDLWindowDeleter>;

// Используем unique_ptr с явно заданным функтором удаления вместо delete.
using SDLGLContextPtr = std::unique_ptr<void, detail::SDLGLContextDeleter>;

class CAbstractWindow::Impl
{
public:
    void ShowFixedSize(glm::ivec2 const& size)
	{
		CUtils::InitOnceSDL2();

        m_pWindow.reset(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                         size.x, size.y, SDL_WINDOW_OPENGL));

        // Создаём контекст OpenGL, связанный с окном.
        m_pGLContext.reset(SDL_GL_CreateContext(m_pWindow.get()));
        if (!m_pGLContext)
        {
			       CUtils::ValidateSDL2Errors();
        }
    }

    void SetBackgroundColor(const glm::vec4 &color)
    {
        m_clearColor = color;
    }

    void Clear() const
    {
        // Заливка кадра цветом фона средствами OpenGL
        glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SwapBuffers()
    {
        // Вывод нарисованного кадра в окно на экране.
        // Обмен двух буферов вместо создания новых позволяет не тратить ресурсы впустую.
        SDL_GL_SwapWindow(m_pWindow.get());
    }

private:
    SDLWindowPtr m_pWindow;
    SDLGLContextPtr m_pGLContext;
    glm::vec4 m_clearColor;
};
//Идиома Pimpl(чеширский кот)
CAbstractWindow::CAbstractWindow()
    : m_pImpl(new Impl)
{
}

CAbstractWindow::~CAbstractWindow()
{
}

void CAbstractWindow::ShowFixedSize(const glm::ivec2 &size)
{
    m_pImpl->ShowFixedSize(size);
}

void CAbstractWindow::DoGameLoop()
{
    SDL_Event event;
    CChronometer chronometer;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else
            {
                OnWindowEvent(event);
            }
        }
        // Очистка буфера кадра, обновление и рисование сцены, вывод буфера кадра.
        if (running)
        {
            m_pImpl->Clear();
            const float deltaSeconds = chronometer.GrabDeltaTime();
            OnUpdateWindow(deltaSeconds);
            OnDrawWindow();
            m_pImpl->SwapBuffers();
        }
    }
}

void CAbstractWindow::SetBackgroundColor(const glm::vec4 &color)
{
    m_pImpl->SetBackgroundColor(color);
}
