#include "Window.hpp"


namespace
{

  const glm::vec3 YELLOW = {1.f, 1.f, 0.f};
  const glm::vec4 LIGHT_YELLOW_RGBA = {1.f, 1.f, 0.5f, 1.f};
  const glm::vec3 ORANGE = {1.f, 0.5f, 0.f};
  const glm::vec3 PINK = {1.f, 0.3f, 0.3f};
  const glm::vec4 WHITE_RGBA = {1, 1, 1, 1};

  void SetupOpenGLState()
  {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
  }
}

CWindow::CWindow()
{
   SetBackgroundColor(LIGHT_YELLOW_RGBA);
}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
  (void) size;
  SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{

}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);
}

void CWindow::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);

    // Матрица вида возвращается камерой и составляет
    // начальное значение матрицы GL_MODELVIEW.

    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
    const float fieldOfView = glm::radians(70.f);
    const float aspect = float(size.x) / float(size.y);
    const float zNear = 0.01f;
    const float zFar = 100.f;
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{

}
