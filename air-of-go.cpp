// https://blog.csdn.net/2301_76848549/article/details/135495859?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22135495859%22%2C%22source%22%3A%222301_76848549%22%7D
#include "utils.hpp"
// Use a greedy (or greedy-like?) algorithm
// But actually the chess board is so small that we don't have to use sparse arrays
// If using sparse arrays how can we find if an point has neighbors quickly?:
// cross-linked red black trees
// 1. There is a hash map to retrieve all the row or column linked list heads
// 2. This could possibly be implemented by map of maps in C++ because every node involves two red-black trees
//    C version could probably be more elegant than C++

enum point
  {
    BLANK = 0,
    WHITE,
    BLACK
  };
void air_of_go (point board[19][19], int& black_air, int & white_air)
{
  // write a more general one testing every point with boundary conditions
  // -- If you write seperate loops for boundary points the efficiency might be better though
  white_air = black_air = 0;
  for (int i = 0; i < 19; i++)
    for (int j = 0; j < 19; j++)
      if (board[i][j] == BLANK)
	{
	  if (i > 0 && board[i-1][j] == WHITE ||
	      i < 18 && board[i+1][j] == WHITE ||
	      j > 0 && board[i][j-1] == WHITE ||
	      j < 18 && board[i][j+1] == WHITE)
	    white_air += 1;
	  if (i > 0 && board[i-1][j] == BLACK ||
	      i < 18 && board[i+1][j] == BLACK ||
	      j > 0 && board[i][j-1] == BLACK ||
	      j < 18 && board[i][j+1] == BLACK)
	    black_air += 1;
	}
}

int main (int argc, char *argv[])
{
  point board[19][19] { BLANK };
  auto blacks = read_space_seperated_ints_inf ();
  auto whites = read_space_seperated_ints_inf ();
  auto blacks_it = blacks.begin (),
    whites_it = whites.begin ();
  // Should have defined a single function for these two loops
  while (blacks_it != blacks.end ())
    {
      int row = *blacks_it++;
      int column = *blacks_it++;
      if (board[row][column] != BLANK)
	throw std::invalid_argument ("");
      board[row][column] = BLACK;
    }
  while (whites_it != whites.end ())
    {
      int row = *whites_it++;
      int column = *whites_it++;
      if (board[row][column] != BLANK)
	throw std::invalid_argument ("");
      board[row][column] = WHITE;
    }
  int black_air, white_air;
  air_of_go (board, black_air, white_air);
  printf ("black air: %d\n", black_air);
  printf ("white air: %d\n", white_air);
}
