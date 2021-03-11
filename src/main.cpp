#include "SDL2/SDL.h"
#include "Renderer.h"

constexpr float DesiredFramePerSecond = 60;
constexpr float FramePerSecond = 1000/DesiredFramePerSecond;
constexpr int kScreenHeight = 600;
constexpr int kScreenWidth = 600;
constexpr int kgridHeight = 10;
constexpr int kgridWidth = 10;

int main()
{
    Renderer renderer(kScreenHeight, kScreenWidth, kgridHeight, kgridWidth);

    return 0;
}