#include <iostream>
#include <cctype>
#include "board.h"

Board::~Board()
{
}

Board::Board()
{
  // initialize the board
  init(); wCastled = bCastled = wKingMoved = bKingMoved = false; turn = 'W';
}

void Board::movePiece(int fi, int fj, int toi, int toj)
{
  // save, erase, write
  char p = board[fi][fj];

  // don't let a ghost piece move
  if (p == ' ') return;

  // wait your turn
  if (isupper(p) && turn == 'B') {
    std::cout << "It's not your turn." << std::endl;
    return;
  }

  if (islower(p) && turn == 'W') {
    std::cout << "It's not your turn." << std::endl;
    return;
  }

  // if white is moving to a square already taken by white, return
  if (turn == 'W' && isupper(board[toi][toj])) { 
    std::cout << "Illegal move. Same color overlaps." << std::endl;
    return;
  }
  // if black is moving to a square already taken by black, return
  if (turn == 'B' && islower(board[toi][toj])) {
    std::cout << "Illegal move. Same color overlaps." << std::endl;
    return;
  }

  #ifdef DEBUG
  std::cout << "Moving: " << p << std::endl;
  #endif

  // we're ready to make a move; so we check if it's a valid move: check
  // whether it's a check, checkmate, castling, et cetera. each piece
  // has its own validator function which is explicitly called by
  // checkMove(). for now, we only check whether a move is valid
  // regardless of checks, checkmates, castling, and capture en passant.

  checkMove(p, fi, fj, toi, toj);
  
  board[fi][fj] = ' '; board[toi][toj] = p;
  changeTurn(); show();
}

void Board::checkMove(char p, int fi, int fj, int toi, int toj) 
{

}

void Board::changeTurn()
{
  if (turn == 'W') { turn = 'B'; return; }
  if (turn == 'B') { turn = 'W'; return; }
  
}

void Board::setPos(int i, int j, char p)
{
  board[i][j] = p;
}


void Board::show()
{
  // show the board on the console
  for (int i=1; i <= dim(); ++i) {
    for (int j=1; j <= dim(); ++j) {
      std::cout << "["<< board[i][j] <<"]";
    }

    if (i == 1) { //show who's turn it is
      std::cout << "[" << turn << "]";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

void Board::init()
{
  // the border around the board is filled with 'X'; this way we can
  // easily identify it when we need to.

  for (int i=0; i < underlyingDim(); ++i)
    for (int j=0; j < underlyingDim(); ++j) {
      if (i == 0 || j == 0 || i==underlyingDim()-1 || j==underlyingDim()-1) {
        board[i][j] = 'X'; continue;
      }

      board[i][j] = ' '; // empty square
    }
}
