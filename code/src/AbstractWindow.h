#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <SDL2/SDL_events.h>

class CAbstractWindow
{
public:
    CAbstractWindow();
    virtual ~CAbstractWindow();

    void ShowFixedSize(glm::ivec2 const& size);
    void DoGameLoop();
    void drawCube(float xrf, float yrf, float zrf);
protected:
    void SetBackgroundColor(glm::vec4 const& color);

    virtual void OnWindowEvent(const SDL_Event &event) = 0;
    virtual void OnUpdateWindow(float deltaSeconds) = 0;
    virtual void OnDrawWindow() = 0;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};
