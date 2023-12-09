#ifndef DISPLAY_H
#define DISPLAY_H

/////////////////////////
// needed includes
/////////////////////////
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

//////////////////////////////////////////////////////
// Declaring but not defining the variables.
// They gonna be defined and initialized in external files
//////////////////////////////////////////////////////
extern int window_width;
extern int window_height;
extern bool fakeFullscreen;
extern bool realFullscreen;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern uint32_t *color_buffer;
extern SDL_Texture* color_buffer_texture; 

///////////////////////////////////////////
// function prototypes (signatures)
///////////////////////////////////////////
bool initialize_window(void);
void destroy_window(void);

void create_color_buffer(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);

void draw_grid(void);
void draw_dot_grid(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

// typedef struct {
//     vec3_t position;
//     vec3_t rotation;
//     float fov_angle;
// } camera_t;

// camera_t mycam = {
//     { 0, 0, 0 },
//     { 0.3, -2.0, 0.0 },
//     0.78
// };

#endif