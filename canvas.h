const canvas CANVAS_LINE = 
  {{0,   0,   0,   0},
   {LINE,LINE,LINE,LINE},
   {0,   0,   0,   0},
   {0,   0,   0,   0}};

const canvas CANVAS_J  = 
  {{0,0,      0,      0},
   {0,J_BLOCK,0,      0},
   {0,J_BLOCK,J_BLOCK,J_BLOCK},
   {0,0,      0,      0}};

const canvas CANVAS_L =	 
  {{0,0,      0,      0},
   {0,0,      0,      L_BLOCK},
   {0,L_BLOCK,L_BLOCK,L_BLOCK},
   {0,0,      0,      0}};

const canvas CANVAS_SQUARE =
  {{0,0,     0,     0},
   {0,SQUARE,SQUARE,0},
   {0,SQUARE,SQUARE,0},
   {0,0,     0,     0}};

const canvas CANVAS_S =
  {{0,0,      0,      0},
   {0,0,      S_BLOCK,S_BLOCK},
   {0,S_BLOCK,S_BLOCK,0},
   {0,0,      0,      0}};

const canvas CANVAS_T =	 
  {{0,0,      0,      0},
   {0,0,      T_BLOCK,0},
   {0,T_BLOCK,T_BLOCK,T_BLOCK},
   {0,0,      0,      0}};

const canvas CANVAS_Z =
  {{0,0,      0,      0},
   {0,Z_BLOCK,Z_BLOCK,0},
   {0,0,      Z_BLOCK,Z_BLOCK},
   {0,0,      0,      0}};


const canvas CANVAS_EMPTY = 
  {{0,0,0,0},
   {0,0,0,0},
   {0,0,0,0},
   {0,0,0,0} 
  };

void copy_canvas(const canvas from, canvas to)
{
  for(size_t i=0; i<CANVAS_SIZE; ++i) {
    for(size_t j=0; j<CANVAS_SIZE; ++j) {
      to[i][j] = from[i][j];
    }
  }
}

#define NUMBER_OF_ROT 4
const canvas LINE_ROT[NUMBER_OF_ROT] = {{{0,   0,   0,   0},
					 {LINE,LINE,LINE,LINE},
					 {0,   0,   0,   0},
					 {0,   0,   0,   0}},
					{{0,0,LINE,0},
					 {0,0,LINE,0},
					 {0,0,LINE,0},
					 {0,0,LINE,0}},
					{{0,0,0,0},
					 {0,0,0,0},
					 {LINE,LINE,LINE,LINE},
					 {0,0,0,0}},
					{{0,LINE,0,0},
					 {0,LINE,0,0},
					 {0,LINE,0,0},
					 {0,LINE,0,0}}};

const canvas J_ROT[NUMBER_OF_ROT] = {{{0,0,      0,      0},
				      {0,J_BLOCK,0,      0},
				      {0,J_BLOCK,J_BLOCK,J_BLOCK},
				      {0,0,      0,      0}},
				     {{0,0,J_BLOCK,J_BLOCK},
				      {0,0,J_BLOCK,0},
				      {0,0,J_BLOCK,0},
				      {0,0,0,0}},
				     {{0,0,0,0},
				      {0,0,0,0},
				      {0,J_BLOCK,J_BLOCK,J_BLOCK},
				      {0,0,0,J_BLOCK}},
				     {{0,0,0,0},
				      {0,0,J_BLOCK,0},
				      {0,0,J_BLOCK,0},
				      {0,J_BLOCK,J_BLOCK,0}}};

const canvas L_ROT[NUMBER_OF_ROT] = {{{0,0,      0,      0},
				      {0,0,      0,      L_BLOCK},
				      {0,L_BLOCK,L_BLOCK,L_BLOCK},
				      {0,0,      0,      0}},
				     {{0,0,0,0},
				      {0,0,L_BLOCK,0},
				      {0,0,L_BLOCK,0},
				      {0,0,L_BLOCK,L_BLOCK}},
				     {{0,0,0,0},
				      {0,0,0,0},
				      {0,L_BLOCK,L_BLOCK,L_BLOCK},
				      {0,L_BLOCK,0,0}},
				     {{0,0,0,0},
				      {0,L_BLOCK,L_BLOCK,0},
				      {0,0,L_BLOCK,0},
				      {0,0,L_BLOCK,0}}};

const canvas SQUARE_ROT[NUMBER_OF_ROT] = {{{0,0,     0,     0},
					   {0,SQUARE,SQUARE,0},
					   {0,SQUARE,SQUARE,0},
					   {0,0,     0,     0}},
					  {{0,0,     0,     0},
					   {0,SQUARE,SQUARE,0},
					   {0,SQUARE,SQUARE,0},
					   {0,0,     0,     0}},
					  {{0,0,     0,     0},
					   {0,SQUARE,SQUARE,0},
					   {0,SQUARE,SQUARE,0},
					   {0,0,     0,     0}},
					  {{0,0,     0,     0},
					   {0,SQUARE,SQUARE,0},
					   {0,SQUARE,SQUARE,0},
					   {0,0,     0,     0}}};

const canvas S_ROT[NUMBER_OF_ROT] = {{{0,0,      0,      0},
				      {0,0,      S_BLOCK,S_BLOCK},
				      {0,S_BLOCK,S_BLOCK,0},
				      {0,0,      0,      0}},
				     {{0,0,0,0},
				      {0,S_BLOCK,0,0},
				      {0,S_BLOCK,S_BLOCK,0},
				      {0,0,S_BLOCK,0}},
				     {{0,0,      0,      0},
				      {0,0,      S_BLOCK,S_BLOCK},
				      {0,S_BLOCK,S_BLOCK,0},
				      {0,0,      0,      0}},
				     {{0,0,0,0},
				      {0,S_BLOCK,0,0},
				      {0,S_BLOCK,S_BLOCK,0},
				      {0,0,S_BLOCK,0}}};

const canvas  T_ROT[NUMBER_OF_ROT] = {{{0,0,      0,      0},
				       {0,0,      T_BLOCK,0},
				       {0,T_BLOCK,T_BLOCK,T_BLOCK},
				       {0,0,      0,      0}},
				      {{0,0,0,0},
				       {0,0,T_BLOCK,0},
				       {0,0,T_BLOCK,T_BLOCK},
				       {0,0,T_BLOCK,0}},
				      {{0,0,0,0},
				       {0,0,0,0},
				       {0,T_BLOCK,T_BLOCK,T_BLOCK},
				       {0,0,T_BLOCK,0}},
				      {{0,0,0,0},
				       {0,0,T_BLOCK,0},
				       {0,T_BLOCK,T_BLOCK,0},
				       {0,0,T_BLOCK,0}}};

const canvas Z_ROT[NUMBER_OF_ROT] = {{{0,0,      0,      0},
				      {0,Z_BLOCK,Z_BLOCK,0},
				      {0,0,      Z_BLOCK,Z_BLOCK},
				      {0,0,      0,      0}},
				     {{0,0,0,0},
				      {0,0,0,Z_BLOCK},
				      {0,0,Z_BLOCK,Z_BLOCK},
				      {0,0,Z_BLOCK,0}},
				     {{0,0,      0,      0},
				      {0,Z_BLOCK,Z_BLOCK,0},
				      {0,0,      Z_BLOCK,Z_BLOCK},
				      {0,0,      0,      0}},
				     {{0,0,0,0},
				      {0,0,0,Z_BLOCK},
				      {0,0,Z_BLOCK,Z_BLOCK},
				      {0,0,Z_BLOCK,0}},				     
};
