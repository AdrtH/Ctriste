#define LINES 22
#define COLS  10

#define FALSE 0
#define TRUE  1

#define CANVAS_SIZE 4

typedef enum block_t {
  EMPTY = 0, // necessary to force the grid initialization to empty
  LINE,
  J_BLOCK,
  L_BLOCK,
  SQUARE,
  S_BLOCK,
  T_BLOCK,
  Z_BLOCK,
} block;

typedef struct vector_2d_float {
  float x,y;
} v2f;

typedef block canvas[CANVAS_SIZE][CANVAS_SIZE];

typedef struct tetro_t {
  v2f           point_of_rot; // pos of point of rotation
  block         block_type;   // determine the color of the sprite
  canvas        canv;
  v2f           por_in_canv;
  unsigned char rot;
} tetro;

typedef block board[COLS][LINES];

board grid;
board render_grid;

