#include "display.h"
#include <math.h>

// defining variables and initialize them
int window_width = WINDOW_WIDTH;
int window_height = WINDOW_HEIGHT;
bool realFullscreen = USE_REAL_FULLSCREEN;

SDL_Window* window = NULL; // make sure if its NULL
SDL_Renderer* renderer = NULL;

uint32_t *color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    if (!realFullscreen) {
        // fake fullscreen - we are not changing the mode of the video to be fullscreen
        SDL_DisplayMode display_mode;
        SDL_GetCurrentDisplayMode(0, &display_mode);
        window_width = display_mode.w;
        window_height = display_mode.h;
    }
    
    // Create a SDL window
    window = SDL_CreateWindow(
        #ifdef WINDOW_BORDERS
            "My SDL window",
        #else
            NULL, // No title
        #endif
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        #ifndef WINDOW_BORDERS
            SDL_WINDOW_BORDERLESS
        #else
            0
        #endif
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    if (realFullscreen) {
        // can stretch low res window to fullscreen
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }

    // Create a SDL renderer
    renderer = SDL_CreateRenderer(
        window,
        -1, // get first(default) display device
        0 // no flags
    );
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }
    return true;
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void create_color_buffer(void) {
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    if (!color_buffer) {
        fprintf(stderr, "Error allocating memory for color buffer.\n");
        exit(-1);
    }

    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, // we will update this texture frequently (dynamic flexible texture)
        window_width,
        window_height
    );
}

void clear_color_buffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL, // update whole texture
        color_buffer,
        (int)(window_width * sizeof(uint32_t)) // make sure if it's int, number of bytes in a row of pixel data
        );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid(void) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            if (x % 20 == 0 || y % 20 == 0)
                color_buffer[(window_width * y) + x] = 0xFF555555; // gray color
        }
    }
}

void draw_dot_grid(void) {
    for (int y = 0; y < window_height; y += 10) {
        for (int x = 0; x < window_width; x += 10) {
                color_buffer[(window_width * y) + x] = 0xFF555555; // gray color
        }
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            draw_pixel(current_x, current_y, color);
        }
    }
}

void draw_pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < window_width && y >= 0 && y < window_height)
        color_buffer[(window_width * y) + x] = color;
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color) {
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);

    int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

    // heart of DDA algorithm, being calculated once, they are the same for each step
    float x_inc = (float)delta_x / longest_side_length;
    float y_inc = (float)delta_y / longest_side_length;

    float current_x = x0;
    float current_y = y0;
    for (int i = 0; i <= longest_side_length; i++) {
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);

}