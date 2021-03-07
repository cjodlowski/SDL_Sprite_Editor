#ifndef SPRITE_EDITOR_HPP
#define SPRITE_EDITOR_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

class SpriteEditor {
    public:
        SpriteEditor(char* filepath, int width, int height, int start, int end);
        ~SpriteEditor();

        void Init();
        void Run();
        void Update();
        void Render();

        void LoadSpriteSheet();

        char * m_filepath;

        int s_width;
        int s_height;

        int starting_frame;
        int ending_frame;

    private:

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        SDL_Rect src;
        SDL_Rect dest;

        int x_pos;
        int y_pos;

        int current_frame;

        int num_cols; //number of sprites per row
        int num_rows; //number of rows in spritesheet

        SDL_Surface* m_surface;
        SDL_Texture* m_texture;
};

#endif