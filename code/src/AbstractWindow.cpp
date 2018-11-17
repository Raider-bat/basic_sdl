#include "AbstractWindow.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <thread>         // std::this_thread::sleep_for
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    }

    void SwapBuffers()
    {
        // Вывод нарисованного кадра в окно на экране.
        // Обмен двух буферов вместо создания новых позволяет не тратить ресурсы впустую.
        SDL_GL_SwapWindow(m_pWindow.get());
    }

    void drawCube(float xrf, float yrf, float zrf){
    	glLoadIdentity();
    	glTranslatef(0.0f, 0.0f, -7.0f);	// Сдвинуть вглубь экрана

    	glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
    	glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
    	glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z

    	glBegin(GL_QUADS);		// Рисуем куб

    	glColor3f(0.0f, 1.0f, 0.0f);		// Синяя сторона (Верхняя)
    	glVertex3f( 1.0f, 1.0f, -1.0f);		// Верхний правый угол квадрата
    	glVertex3f(-1.0f, 1.0f, -1.0f);		// Верхний левый
    	glVertex3f(-1.0f, 1.0f,  1.0f);		// Нижний левый
    	glVertex3f( 1.0f, 1.0f,  1.0f);		// Нижний правый

    	glColor3f(1.0f, 0.5f, 0.0f);		// Оранжевая сторона (Нижняя)
    	glVertex3f( 1.0f, -1.0f,  1.0f);	// Верхний правый угол квадрата
    	glVertex3f(-1.0f, -1.0f,  1.0f);	// Верхний левый
    	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
    	glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

    	glColor3f(1.0f, 0.0f, 0.0f);		// Красная сторона (Передняя)
    	glVertex3f( 1.0f,  1.0f, 1.0f);		// Верхний правый угол квадрата
    	glVertex3f(-1.0f,  1.0f, 1.0f);		// Верхний левый
    	glVertex3f(-1.0f, -1.0f, 1.0f);		// Нижний левый
    	glVertex3f( 1.0f, -1.0f, 1.0f);		// Нижний правый

    	glColor3f(1.0f,1.0f,0.0f);			// Желтая сторона (Задняя)
    	glVertex3f( 1.0f, -1.0f, -1.0f);	// Верхний правый угол квадрата
    	glVertex3f(-1.0f, -1.0f, -1.0f);	// Верхний левый
    	glVertex3f(-1.0f,  1.0f, -1.0f);	// Нижний левый
    	glVertex3f( 1.0f,  1.0f, -1.0f);	// Нижний правый

    	glColor3f(0.0f,0.0f,1.0f);			// Синяя сторона (Левая)
    	glVertex3f(-1.0f,  1.0f,  1.0f);	// Верхний правый угол квадрата
    	glVertex3f(-1.0f,  1.0f, -1.0f);	// Верхний левый
    	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
    	glVertex3f(-1.0f, -1.0f,  1.0f);	// Нижний правый

    	glColor3f(1.0f,0.0f,1.0f);			// Фиолетовая сторона (Правая)
    	glVertex3f( 1.0f,  1.0f, -1.0f);	// Верхний правый угол квадрата
    	glVertex3f( 1.0f,  1.0f,  1.0f);	// Верхний левый
    	glVertex3f( 1.0f, -1.0f,  1.0f);	// Нижний левый
    	glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

    	glEnd();	// Закончили квадраты

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
    float xrf = 0, yrf = 0, zrf = 0;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	     SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

   	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
   	glClearDepth(1.0);
   	glDepthFunc(GL_LESS);
   	glEnable(GL_DEPTH_TEST); // включаем тест глубины
   	glShadeModel(GL_SMOOTH);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	gluPerspective(45.0f, (float) 800/ (float) 600, 0.1f, 100.0f); // настраиваем трехмерную перспективу
   	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим

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
          xrf -= 0.5;
		        yrf -= 0.5;
		          zrf -= 0.5;
            m_pImpl->Clear();
            m_pImpl -> drawCube(xrf, yrf, zrf);
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
