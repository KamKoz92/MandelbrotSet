#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL2/SDL.h>
class Screen
{
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer1;
    int SCREEN_HEIGHT;
    int SCREEN_WIDTH;
public:

    Screen(int width, int height);
    bool init();
    bool processEvents();
    void close();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void clear();
};

#endif /* SCREEN_H */