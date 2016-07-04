#ifndef BOARD_H
#define BOARD_H

#include <cctype>

class Board 
{
  /* 
     a board is an 10x10 array to make search on boundaries an easier
     job. however, this size won't help the search on the boundary for
     knight moves because knights may try to move two columns or two
     rows beyond the boundary: consider a knight on the boundary of the
     board. 

     but it seems still interesting to use a 10x10 array because this
     way we have a valid board ranging from coordinates (1,1) to (8,8)
     just like the algebraic notation does. so we can treat knights as a
     special case when validating their moves.

     the data type of the array is char because we can mark each square
     with a letter: upper case is white, lower case is black. by
     convention, we use Q for a white queen, and q for black one.
  */

  private:
  char board[10][10];

  // has castling already occurred?
  bool wCastled, bCastled;

  // has any castling required piece moved?
  bool wKingMoved, bKingMoved; 

  // who's turn is it? W for white, B for black
  char turn;

  int underlyingDim() { return 10; }

  public:
  Board(); ~Board();

  int dim() { return 8; }

  void show(); // show the board on the console
  void init(); // initilize the underlying structures

  void setPos(int i, int j, char p); // place a piece
  void movePiece(int fi, int fj, int toi, int toj);
  char getPiece(int i, int j) { return board[i][j]; }
  bool isEmpty(char p) { return p == ' '; }

  bool isWhiteTurn() { return turn == 'W'; }
  bool isBlackTurn() { return turn == 'B'; }
  bool isWhite(char p) { return isupper(p); }
  bool isBlack(char p) { return islower(p); }

  void changeTurn();
  void checkMove(char p, int fi, int fj, int toi, int toj);

};

#endif 
