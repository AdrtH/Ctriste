#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./raylib/raylib.h"
#include "./type.h"
#include "./canvas.h"

void render_block_console(block b)
{
  switch(b) {
  case EMPTY:
    printf("  ");
    break;
  default:
    printf("##");
    break;
  }
  return;
}

void render_grid_console(board grid)
{
  for(size_t i=0; i<LINES; ++i) {
    printf("|");
    for(size_t j=0; j<COLS; ++j) {
      render_block_console(grid[j][i]);
    }
    printf("|\n");
  }
  printf("|");
  for(size_t i=0; i<COLS; ++i) {
    printf("--");
  }
  printf("|\n");
}

int check_put(board grid, size_t x, size_t y)
{
  return (x<COLS && y<LINES
       && grid[x][y] == EMPTY);
}

int put_block(board grid, size_t x, size_t y, block b) {
  if(grid[x][y] != EMPTY && b != EMPTY) {
    return FALSE;
  }
  if(x<COLS && y<LINES)
    grid[x][y] = b;
  else return FALSE;
  return TRUE;
}

tetro create_tetro(block b)
{
  tetro ret;
  ret.rot = 0;
  ret.block_type = b;
  switch(b) {
  case LINE:
    copy_canvas(CANVAS_LINE, ret.canv);
    ret.por_in_canv.x  = 2.0f;
    ret.por_in_canv.y  = 2.0f;
    ret.point_of_rot.x = COLS/2;
    ret.point_of_rot.y = 1.0f;
    break;
  case J_BLOCK:
    copy_canvas(CANVAS_J, ret.canv);
    ret.por_in_canv.x  = 2.5f;
    ret.por_in_canv.y  = 2.5f;
    ret.point_of_rot.x = .5f+COLS/2;
    ret.point_of_rot.y = 1.5f;

    break;
  case L_BLOCK:
    copy_canvas(CANVAS_L, ret.canv);
    ret.por_in_canv.x  = 2.5f;
    ret.por_in_canv.y  = 2.5f;
    ret.point_of_rot.x = .5f+COLS/2;
    ret.point_of_rot.y = .5f;
    break;
  case SQUARE:
    copy_canvas(CANVAS_SQUARE, ret.canv);
    ret.por_in_canv.x  = 2.0f;
    ret.por_in_canv.y  = 2.0f;
    ret.point_of_rot.x = COLS/2;
    ret.point_of_rot.y = 1.0f;  
    break;
  case S_BLOCK:
    copy_canvas(CANVAS_S, ret.canv);
    ret.por_in_canv.x  = 2.5f;
    ret.por_in_canv.y  = 2.5f;
    ret.point_of_rot.x = .5f+COLS/2;
    ret.point_of_rot.y = .5f;
    break;
  case T_BLOCK:
    copy_canvas(CANVAS_T, ret.canv);
    ret.por_in_canv.x  = 2.5f;
    ret.por_in_canv.y  = 2.5f;
    ret.point_of_rot.x = .5f+COLS/2;
    ret.point_of_rot.y = .5f;
    break;
  case Z_BLOCK:
    copy_canvas(CANVAS_Z, ret.canv);
    ret.por_in_canv.x  = 2.5f;
    ret.por_in_canv.y  = 2.5f;
    ret.point_of_rot.x = .5f+COLS/2;
    ret.point_of_rot.y = 1.5f;
    break;
  default:
    copy_canvas(CANVAS_EMPTY, ret.canv);
    ret.point_of_rot.x = .0;
    ret.point_of_rot.y = .0f;
  }
  return ret;
}

int is_block_supported(block grid[COLS][LINES], size_t x, size_t y)
{
  return (y==LINES-1 || grid[x][y+1]);
}

#define OBFUSCATED 0
#define SUCCESS    1
#define FALLING    2

int try_put_tetro(board grid, tetro t, board render_grid)
{
  int ret = FALLING;
  for(int i=0; i<CANVAS_SIZE; ++i) {   // check if a block is colliding
    for(int j=0; j<CANVAS_SIZE; ++j) {
      if(t.canv[i][j] != EMPTY) {
      size_t x = (size_t)(t.point_of_rot.x - t.por_in_canv.x + j);
      size_t y = (size_t)(t.point_of_rot.y - t.por_in_canv.y + i);
	if(!check_put(grid, x, y)) {
	  return FALSE;
	} else if (is_block_supported(grid, x, y)) {
	  ret = SUCCESS;
	}
      }
    }
  }
  for(int i=0; i<COLS; ++i) {
    for(int j=0; j<LINES; ++j) {
      render_grid[i][j] = grid[i][j];
    }
  }
  for(int i=0; i<CANVAS_SIZE; ++i) {
    for(int j=0; j<CANVAS_SIZE; ++j) {
      if(t.canv[i][j] == EMPTY) continue;
      size_t x = (size_t)(t.point_of_rot.x - t.por_in_canv.x + j);
      size_t y = (size_t)(t.point_of_rot.y - t.por_in_canv.y + i);
      render_grid[x][y] = t.block_type;
      if(ret == SUCCESS) grid[x][y] = t.block_type;
    }
  }
  return ret;
}

// TODO : factor out in different file ie math for min/max, grid, tetro, block
int min(int a, int b)
{
  return (a<b? a:b);
}

int max(int a, int b)
{
  return (a<b? b:a);
}

Color match_block_color(block b)
{
  switch(b) {
  case LINE:    return SKYBLUE;
  case J_BLOCK: return DARKBLUE;
  case L_BLOCK: return ORANGE;
  case SQUARE:  return GOLD;
  case S_BLOCK: return GREEN;
  case T_BLOCK: return PURPLE;
  case Z_BLOCK: return RED;
  default:      return DARKGRAY;
  }
}

void draw_grid(int s_width, int s_height, board grid)
{
  int padding = 25;
  int min_dim = min(s_width-2*padding, s_height-2*padding);
  int grid_height  = (min_dim-padding);
  int block_size   = grid_height/LINES;
  int grid_width   = COLS*block_size;
  grid_height      = 22*block_size; // for rounding error
  DrawRectangle((s_width-grid_width)/2, (s_height-grid_height)/2, grid_width, grid_height, DARKGRAY);
  for(size_t x=0; x<COLS; ++x) {
    for(size_t y=0; y<LINES; ++y) {
      if(grid[x][y] == EMPTY) continue;
      Color block_color = match_block_color(grid[x][y]);
      DrawRectangle(x*block_size+((s_width-grid_width)/2),
		    y*block_size+((s_height-grid_height)/2),
		    block_size, block_size, block_color);
    }
  }
  // draw separation for each block
  for(int h=0; h<=grid_height; ++h) {
    for(int w=0; w<=grid_width; ++w) {
      if(!(w%block_size && h%block_size)) {
	DrawRectangle(w+((s_width-grid_width)/2),
		      h+((s_height-grid_height)/2),
		      1, 1, BLACK);
      }
    }
  }
}

tetro spawn_random_tetro()
{
  int b = 1+(rand()%(Z_BLOCK));
  return create_tetro((block)b);
}

int check_col_empty(tetro *t, size_t col)
{
  for(size_t line=0; line<CANVAS_SIZE; ++line) {
    if(t->canv[line][col] != EMPTY) return 0;
  }
  return 1;
}

const canvas* match_rot(block b)
{
  switch(b) {
  case LINE:
    return LINE_ROT;
  case J_BLOCK:
    return J_ROT;
  case L_BLOCK:
    return L_ROT;
  case SQUARE:
    return SQUARE_ROT;
  case S_BLOCK:
    return S_ROT;
  case T_BLOCK:
    return T_ROT;
  case Z_BLOCK:
    return Z_ROT;
  default:
    return NULL;
  }
}

void rotate_clockwise(tetro *t)
{
  const canvas* rot;
  for(size_t i=0; i<CANVAS_SIZE; ++i) {
    for(size_t j=0; j<CANVAS_SIZE; ++j) {
      if(t->canv[i][j] == EMPTY) continue;
      rot = match_rot(t->canv[i][j]);
      break;
    }
  }
  t->rot = (t->rot+1)%NUMBER_OF_ROT;
  copy_canvas(rot[t->rot],t->canv);
}

void rotate_counterwise(tetro *t)
{
  const canvas* rot;
  for(size_t i=0; i<CANVAS_SIZE; ++i) {
    for(size_t j=0; j<CANVAS_SIZE; ++j) {
      if(t->canv[i][j] == EMPTY) continue;
      rot = match_rot(t->canv[i][j]);
      break;
    }
  }
  t->rot = (t->rot+CANVAS_SIZE-1)%NUMBER_OF_ROT;
  copy_canvas(rot[t->rot],t->canv);
}

void handle_key_press(board grid, tetro *t)
{
  switch(GetKeyPressed()) {
  case KEY_LEFT:
    int abs_min_x = (int)(t->point_of_rot.x-t->por_in_canv.x);
    if(abs_min_x > 0 || check_col_empty(t, -abs_min_x)) {
      --(t->point_of_rot.x);
    }
    break;
  case KEY_RIGHT:
    int abs_max_x = CANVAS_SIZE + (int)(t->point_of_rot.x-t->por_in_canv.x);
    if(abs_max_x < COLS || check_col_empty(t, CANVAS_SIZE-(abs_max_x%COLS)-1)) {
	++(t->point_of_rot.x);
      }
    break;
  case KEY_C:
    {
      board placeholder;
      int res;
      do {
	rotate_clockwise(t);
	res = try_put_tetro(grid, *t, placeholder);
      } while(res==OBFUSCATED);
      break;
    }
  case KEY_V:
    {
      board placeholder;
      int res;
      do{
	rotate_counterwise(t);
	res = try_put_tetro(grid, *t, placeholder);	
      } while(res==OBFUSCATED);
    }
  }
}

void check_filled_lines(board grid, int filled_lines[LINES]) 
{
  for(int line=0; line<LINES; ++line) {
    filled_lines[line] = TRUE;
    for(int col=0; col<COLS; ++col) {
      if(grid[col][line] == EMPTY) {
	filled_lines[line] = FALSE;
	break;
      }
    }
  }
}

void delete_block(board grid, int x, int y)
{
  if(grid[x][y] == EMPTY) return;
  if(y > 0) { 
    grid[x][y] = grid[x][y-1];
    delete_block(grid, x, y-1);
  } else grid[x][y] = EMPTY;
}

void delete_lines(board grid, int filled_lines[LINES])
{
  for(int line=0; line<LINES; ++line) {
    if(!filled_lines[line]) continue;
    for(int col=0; col<COLS; ++col) {
      delete_block(grid, col, line);
    }
  }
}

#ifndef THIS_IS_CURSED
int main(void)
{
  SetExitKey(KEY_ESCAPE);
  srand(time(0));
  tetro t  = spawn_random_tetro();
  
  int screen_width  = 800;
  int screen_height = 450;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screen_width, screen_height, "Ctriste");
  SetTargetFPS(60);
  clock_t tick = clock();
  while(!WindowShouldClose()) {
    int filled_lines[LINES];
    check_filled_lines(grid, filled_lines);
    delete_lines(grid, filled_lines);
    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();
    clock_t t_curr = clock();
    handle_key_press(grid, &t);
    if((double)(t_curr-tick)/CLOCKS_PER_SEC >= 0.3) {
      t.point_of_rot.y++;
      int res = try_put_tetro(grid, t, render_grid);
      if(res == OBFUSCATED) {
	break;
      } else if(res == SUCCESS) {
	t = spawn_random_tetro();
	try_put_tetro(render_grid, t, render_grid);
      }
      tick = t_curr;
    }
    BeginDrawing();
      ClearBackground(LIGHTGRAY);
      draw_grid(screen_width, screen_height, render_grid);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
#endif // THIS_IS_CURSED
