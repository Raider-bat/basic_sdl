#include "AbstractWindow.hpp"
#include "Utils.hpp"
#include <glm/glm.hpp>
#include <GL/glu.h>
#include "FPSManager.hpp"
#include <boost/lexical_cast.hpp>

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
  void Show(glm::ivec2 const& size,char const* title)
	{
		CUtils::InitOnceSDL2();

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    m_pWindow.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                         size.x, size.y, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE));

    // Создаём контекст OpenGL, связанный с окном.
    m_pGLContext.reset(SDL_GL_CreateContext(m_pWindow.get()));
		if (!m_pGLContext)
    {
			CUtils::ValidateSDL2Errors();
    }
  }

	glm::ivec2 GetWindowSize() const
	{
		return m_size;
	}

	bool isTerminated()const
	{
		return m_isTerminated;
	}

	void SetBackgroundColor(const glm::vec4 &color)
  {
		m_clearColor = color;
  }

	void SetTitle(const std::string &title)
	{
		SDL_SetWindowTitle(m_pWindow.get(), title.c_str());
	}

  void Clear() const
  {
  	// Заливка кадра цветом фона средствами OpenGL
    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

  void SwapBuffers() const
  {
  	// Вывод нарисованного кадра в окно на экране.
    // Обмен двух буферов вместо создания новых позволяет не тратить ресурсы впустую.
    SDL_GL_SwapWindow(m_pWindow.get());
  }

	bool ConsumeEvent(const SDL_Event &event)
	{
		bool consumed = false;
		if (event.type == SDL_QUIT)
		{
			m_isTerminated = true;
			consumed = true;
		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			OnWindowEvent(event.window);
			consumed = true;
		}
		return consumed;
	}


private:

	void OnWindowEvent(const SDL_WindowEvent &event)
	{
		if (event.event == SDL_WINDOWEVENT_RESIZED)
		{
			m_size = {event.data1, event.data2};
		}
	}
    SDLWindowPtr m_pWindow;
    SDLGLContextPtr m_pGLContext;
    glm::vec4 m_clearColor;
		glm::ivec2 m_size;
		bool m_isTerminated = false;
};

//Идиома Pimpl(чеширский кот)
CAbstractWindow::CAbstractWindow()
    : m_pImpl(new Impl)
{
}

CAbstractWindow::~CAbstractWindow()
{
}

void CAbstractWindow::Show(const glm::ivec2 &size, char const* title)
{
    m_pImpl->Show(size, title);
}

void CAbstractWindow::DoGameLoop()
{
  SDL_Event event;
	const std::chrono::milliseconds FRAME_PERIOD(20);
	FPSManager fpscontrol;
  while (true)
  {
  	while (SDL_PollEvent(&event) != 0)
    {
      if (!m_pImpl->ConsumeEvent(event))
      {
        OnWindowEvent(event);
      }
    }
		if (m_pImpl->isTerminated())
		{
			break;
		}

    // Очистка буфера кадра, обновление и рисование сцены, вывод буфера кадра.
    m_pImpl->Clear();
		fpscontrol.UpdateCurrentFPS();
		fpscontrol.ShowCurrentFPS();
		OnDrawWindow(m_pImpl->GetWindowSize());
    //  OnUpdateWindow(deltaSeconds);
		CUtils::ValidateOpenGLErrors();
    m_pImpl->SwapBuffers();
		fpscontrol.LimitFPS(FRAME_PERIOD);
  }
}

void CAbstractWindow::SetBackgroundColor(const glm::vec4 &color)
{
    m_pImpl->SetBackgroundColor(color);
}

void CAbstractWindow::SetTitle(const std::string &title)
{
	m_pImpl->SetTitle(title);
}
