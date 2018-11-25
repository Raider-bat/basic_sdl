#include <iostream>
#include "Utils.hpp"
#include <SDL2/SDL.h>


void CUtils::InitOnceSDL2()
{
  static bool didInit = false;

	if (!didInit)
	{
		if (0 != SDL_Init(SDL_INIT_EVERYTHING))
		{
			std::cerr << "SDL2 initialization failed: " << SDL_GetError() << std::endl;
			std::abort();
		}
	}
}

void CUtils::ValidateSDL2Errors()
{
	std::string message = SDL_GetError();
	if (!message.empty())
	{
		std::cerr << "SDL2 error: " << message << std::endl;
		std::abort();
	}
}

void CUtils::ValidateOpenGLErrors()
{
  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    std::string message;

    switch (error) {
      case GL_INVALID_ENUM:
        message = "An unacceptable value is specified for an enumerated argument. (GL_INVALID_ENUM)";
        break;
      case GL_INVALID_VALUE:
        message = " A numeric argument is out of range. (GL_INVALID_VALUE)";
        break;
      case GL_INVALID_OPERATION:
        message = "The specified operation is not allowed in the current state. (GL_INVALID_OPERATION)";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        message = "The framebuffer object is not complete. (GL_INVALID_FRAMEBUFFER_OPERATION)";
        break;
      case GL_OUT_OF_MEMORY:
        message = "There is not enough memory left to execute the command. (GL_OUT_OF_MEMORY)";
        break;
      case GL_STACK_UNDERFLOW:
        message = "An attempt has been made to perform an operation that would cause an internal stack to underflow. (GL_STACK_UNDERFLOW)";
        break;
      case GL_STACK_OVERFLOW:
        message = "An attempt has been made to perform an operation that would cause an internal stack to overflow. (GL_STACK_OVERFLOW)";
        break;
      default:
        message = "OpenGL caused an unknown error (unknown)";
        break;
    }
    std::cerr<<"OpenGL Error: " << message << std::endl;
    std::abort();
  }
}

CChronometer::CChronometer()
	: m_lastTime(std::chrono::system_clock::now())
{
}

float CChronometer::GrabDeltaTime()
{
	auto newTime = std::chrono::system_clock::now();
	auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - m_lastTime);
	m_lastTime = newTime;
	return 0.001f * float(timePassed.count());
}
