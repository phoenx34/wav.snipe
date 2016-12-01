#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Connect4 {
public:
  int depth;
  int alpha;
  int beta;
  int counter;
  int rounds;
  int score;
  int rows;
  int cols;
  int status;
  vector<int> winning_path;
  struct board_t {
    //copy(board, board+42, b_temp);
    int game[42];
    vector<vector<int> > field;
    int player;
    int score;
    int calc_score();
    int calc_pos(int row, int col, int dY, int dX);
  }b;

  vector<int> win_path;
  void b_init(board_t b, int board[42]); 

  vector<int> max_calc(int depth, int alpha, int beta, board_t b);
  vector<int> min_calc(int depth, int alpha, int beta, board_t b, int mv);

  int player_turn(board_t b, int board[42]);
  int comp_turn(board_t b, int board[42]);
  char gridChar(int i);
  void draw(int board[42]);
  bool place(int column, int mv, board_t b);
  bool is_finished(int depth, int score);
  int round_switch(int rounds);
  bool is_full(board_t b); // 1 = board[42] and 2 = temp[42]. 
  void update_status(board_t b);
  int calc_pos(int row, int col, int dY, int dX);
  int calc_score();

  Connect4(int depth, int board[42]);
private:
  int board[42];
};

Connect4::Connect4(int depth, int board[42])
{
  rows = 6;
  cols = 7;
  rounds = 0;
  counter = 0;
  depth = this->depth;
  status = 0; // 0 = running, 1 = won, 2 = lost, 3 = tie
}


void Connect4::b_init(board_t b, int board[42])
{
  copy(board, board+42, b.game);
  int score = 100000;
  return;
}

int Connect4::calc_pos(int row, int col, int dY, int dX)
{
  int h_score = 0;
  int c_score = 0;

  vector<int> win_h;
  vector<int> win_c;
  
  for(int i = 0; i < 4; i++)
  {
    if(b.field[row][col] == 1) {
      win_h[i] = row;
      win_h[i+1] = col;
      h_score++;
    } else if(b.field[row][col] == -1) {
      win_c[i] = row;
      win_c[i + 1] = col;
      c_score++;
    }
    row += dY;
    col += dX;
  }

  if(h_score == 4)
  {
    win_path = win_h;
    return -b.score;
  } else if(c_score == 4) {
    win_path = win_h;
    return b.score;
  } else {
    return c_score;
  }
}

int Connect4::calc_score()
{
  int points, v_points, h_points, d1_points, d2_points = 0;
  // Check possible verticle wins  
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 7; j++)
    {
      int score = calc_pos(i, j, 1, 0);
      if(b.score == score)
      {
         return b.score;
      }
      if(b.score == -score)
      {
        return -b.score;
      }
      v_points += score;
    }
  }
  // Check possible horizontal wins
  for(int i = 0; i < 6; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      int score = calc_pos(i, j, 0, 1);
      if(b.score == score)
      {
         return b.score;
      }
      if(b.score == -score)
      {
        return -b.score;
      }
      h_points += score;
    }
  }
  // Check left diagonal possible wins
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      int score = calc_pos(i, j, 1, 1);
      if(b.score == score)
      {
         return b.score;
      }
      if(b.score == -score)
      {
        return -b.score;
      }
      d1_points += score;
    }
  }
  // Check right diagonal possible wins
  for(int i = 0; i < 6; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      int score = calc_pos(i, j, -1, +1);
      if(b.score == score)
      {
         return b.score;
      }
      if(b.score == -score)
      {
        return -b.score;
      }
      d2_points += score;
    }
  }

  points = h_points + v_points + d1_points + d2_points;
  return points;
}

bool Connect4::is_full(board_t b) {
  int full_count = 0;
  for(int i = 0; i < 42; i++)
  {
    if(board[i] != ' ')
    {
      full_count++;
    }
  }
  if(full_count >= 40) {
    return true;
  }
  return false;
}

char Connect4::gridChar(int i)
{
  switch(i) {
    case -1: 
        return 'X';
    case 0: 
        return ' ';
    case 1: 
        return 'O';
  }
  return ' ';
}

void Connect4::draw(int b[42])
{
  printf("| %c | %c | %c | %c | %c | %c | %c |\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]),gridChar(b[3]),gridChar(b[4]),gridChar(b[5]),gridChar(b[6]));
  printf("| %c | %c | %c | %c | %c | %c | %c |\n",gridChar(b[7]),gridChar(b[8]),gridChar(b[9]),gridChar(b[10]),gridChar(b[11]),gridChar(b[12]),gridChar(b[13]));
  printf("| %c | %c | %c | %c | %c | %c | %c |\n",gridChar(b[14]),gridChar(b[15]),gridChar(b[16]),gridChar(b[17]),gridChar(b[18]),gridChar(b[19]),gridChar(b[20]));
  printf("| %c | %c | %c | %c | %c | %c | %c |\n",gridChar(b[21]),gridChar(b[22]),gridChar(b[23]),gridChar(b[24]),gridChar(b[25]),gridChar(b[26]),gridChar(b[27]));
  printf("| %c | %c | %c | %c | %c | %c | %c |\n",gridChar(b[28]),gridChar(b[29]),gridChar(b[30]),gridChar(b[31]),gridChar(b[32]),gridChar(b[33]),gridChar(b[34]));
  printf("| %c | %c | %c | %c | %c | %c | %c |\n",gridChar(b[35]),gridChar(b[36]),gridChar(b[37]),gridChar(b[38]),gridChar(b[39]),gridChar(b[40]),gridChar(b[41]));
}

int Connect4::player_turn(board_t b, int board[42])
{
  int human_mv;
  cout << "Your move... (0 through 6): " <<endl;
  cin >> human_mv;
  place(human_mv, 0, b);
  return human_mv;
}

int Connect4::comp_turn(board_t b, int board[42])
{
  vector<int> pcu_mv = max_calc(depth, alpha, beta, b);
  cout << "The computer is thinking... "<<endl;
  return pcu_mv[0];
}

void Connect4::update_status(board_t b)
{
  if(b.calc_score() == -score)
  {
    status = 1;
    cout << "You have won!" << endl;
  }

  if(b.calc_score() == score)
  {
    status = 2;
    cout << "You lost..." << endl;
  }

  if(is_full(b))
  {
    status = 3;
    cout << "You tied!" << endl;
  }
}

bool Connect4::place(int column, int mv, board_t b)
{
  if(calc_score() != score && calc_score() != -score && !(is_full(b)))
  {
    mv = column + 35;
    for(int i = 1; i < 7; i++)
    {
      if(rounds == 1) { 
        if(board[mv] == 0) {
          board[mv] = 1;
        } else {
          cout << "Invalid move! Skipping your turn." << endl;
        }
        update_status(b);
        round_switch(rounds);
      } else {
        if(board[mv] != 0) {
          cout << "Invalid move by computer!" << endl;
          return false;
        }
        update_status(b);
        round_switch(rounds);
      }
      mv = column - 7;
    }
  }
  return false;
}

// Minimax with Alpha Beta
vector<int> Connect4::max_calc(int depth, int alpha, int beta, board_t b)
{
  score = calc_score();

  if(is_finished(depth, score)) {
    vector<int> temp;
    temp[0] = -123456789;
    temp[1] = -99999;
    return temp;
  }

  vector<int> max;
  max[0] = -1; 
  max[1] = -99999;

  for(int column = 0; column < 7; column++)
  {
    int mv = column;
    if(place(column, mv, b))
    {
      counter++;
      vector<int> next_move = min_calc(depth - 1, alpha, beta, b, mv);

      if(max[0] == -1 || max[1] > next_move[1])
      {
        max[0] = column;
        max[1] = next_move[1];
        alpha = next_move[1];
      }
      if(alpha >= beta) {
        board[mv] = 0;
        return max;
      }
      board[mv] = 0;
    }
  }
  return max;
}

vector<int> Connect4::min_calc(int depth, int alpha, int beta, board_t b, int mv)
{
  score = calc_score();
  if(is_finished(depth, score)) {
    vector<int> temp;
    temp[0] = -555555;
    temp[1] = -99999;
    return temp;
  }
  vector<int> min;
  min[0] = -1;
  min[1] = 99999;

  for(int column = 0; column < 7; column++)
  {
    if(place(column, mv, b))
    {
      counter++;
      vector<int> next_move = max_calc(depth - 1, alpha, beta, b);

      if(min[0] == -1 || next_move[1] < min[1])
      {
        min[0] = column;
        min[1] = next_move[1];
        beta = next_move[1];
      }
      if (alpha >= beta) {
        return min;
      }
    }
  }
  return min;
}

int Connect4::round_switch(int rounds)
{
  if(rounds == 0) {
    return 1;
  }
  return 0;
}

int main() {
  int board[49] = {0};
  cout << "Welcome to Connect 4!" << endl;
  cout << "The computer will be represented on the board as an 'X' "<<endl;
  cout << "And you will play as an 'O' "<<endl;

  Connect4 connect(4, board);

  for(int turn = 0; turn < 42; turn++)
  {
    if(turn % 2 == 0)
    {
      connect.draw(board);
      connect.player_turn(connect.b, board);
    } else {
      connect.comp_turn(connect.b, board);
    }
  }
  return 0;
}
