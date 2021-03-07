#include "SpriteEditor.hpp"


SpriteEditor::SpriteEditor(char * filepath, int width, int height, int start, int end) {
    this->m_filepath = filepath;
    this->s_width = width;
    this->s_height = height;
    this->starting_frame = start;
    this->ending_frame = end;

    current_frame = starting_frame;
}

SpriteEditor::~SpriteEditor() {
    m_window = NULL;
    m_renderer = NULL;
    m_surface = NULL;
    m_texture = NULL;

    printf("Quitting_SDL\n");
    SDL_Quit();
}

void SpriteEditor::Init() {
    m_window = SDL_CreateWindow("Sprite Editor", 100, 100, 720, 480, SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        printf("Could not create window\n");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if( m_renderer == nullptr ){
        printf("Could not create renderer\n");
    }

    this->LoadSpriteSheet();

    num_cols = ceil((double)m_surface->w / s_width);
    num_rows = ceil((double)m_surface->h / s_height);
    printf("Height: %d Width: %d\n", m_surface->h, m_surface->w);
    printf("NumRows: %d NumCols: %d\n", num_rows, num_cols);

    //if number of frames from user input is greater than sprite sections
    //set ending_frame to last frame in spritesheet (bottom-right)
    if (ending_frame >= num_rows * num_cols) {
        ending_frame = (num_cols * num_rows) - 1;
    }
}

void SpriteEditor::LoadSpriteSheet() {
    m_surface = SDL_LoadBMP(m_filepath);

    if(m_surface == NULL) {
        printf("Could not create surface\n");
    } else {
        m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
    }
}

void SpriteEditor::Run() {
    int startTime, currentTime = 0;
    while(1) {
        //Check if User Quits Window
        SDL_Event e;
        if(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                printf("Broken out of Run while loop\n");
                break;
            }/*else if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE) {
                        break;
                    }
                    else if(e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) {
                        current_frame--;
                    }
                    else if(e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
                        current_frame++;
                    }
                }
                */
        }

        //Caps to 30 FPS to view animation
    
        currentTime = SDL_GetTicks();

        if(currentTime - startTime <= 33) {
	      int elapsedTime = currentTime - startTime;
	      SDL_Delay(33 - elapsedTime);
	      currentTime = SDL_GetTicks();
        }
        startTime = currentTime;
        

        Update();
        Render();
    }
}

void SpriteEditor::Update() {
    current_frame++;

    if(current_frame > ending_frame || current_frame < starting_frame) {
        current_frame = starting_frame;
    }

    int row = current_frame / num_cols;
    int col = current_frame % num_cols;

    //printf("Current Frame; %d Row: %d Col: %d\n", current_frame, row, col);

    src.x = s_width * col;
    src.y = s_height * row;
    src.w = s_width;
    src.h = s_height;

    //printf("TL: (%d, %d )TR: (%d, %d) BL: (%d, %d) BR: (%d, %d)\n", 
    //src.x,src.y, src.x + src.w, src.y, src.x, src.y + src.h, src.x + src.w, src.y + src.h);

    dest.x = 360 - (s_width / 2);
    dest.y = 240 - (s_height / 2);
    dest.w = s_width;
    dest.h = s_height ;

}

void SpriteEditor::Render() {
    SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);

    SDL_RenderClear(m_renderer);

    SDL_RenderCopy(m_renderer, m_texture, &src, &dest);

    SDL_RenderPresent(m_renderer); 
}