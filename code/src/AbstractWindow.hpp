#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <boost/noncopyable.hpp>
#include <SDL2/SDL_events.h>
#include <GL/glu.h>

class CAbstractWindow : private boost::noncopyable
{
public:
    CAbstractWindow();
    virtual ~CAbstractWindow();

    void Show(glm::ivec2 const& size, char const* title);
    void DoGameLoop();
protected:
    void SetBackgroundColor(glm::vec4 const& color);
    void SetTitle(const std::string &title);

    virtual void OnWindowInit(const glm::ivec2 &size) = 0;
    virtual void OnWindowEvent(const SDL_Event &event) = 0;
    virtual void OnUpdateWindow(float deltaSeconds) = 0;
    virtual void OnDrawWindow(glm::ivec2 const& size) = 0;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};
