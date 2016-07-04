#ifndef SET_H
#define SET_H

#include <wx/wx.h>

namespace set
{
  extern wxBitmap wp; // white pawn
  extern wxBitmap wr; // white rook
  extern wxBitmap wn; // white knight
  extern wxBitmap wb; // white bishop
  extern wxBitmap wk; // white king
  extern wxBitmap wq; // white queen

  extern wxBitmap bp; // black pawn
  extern wxBitmap br; // black rook
  extern wxBitmap bn; // black knight
  extern wxBitmap bb; // black bishop
  extern wxBitmap bk; // black king
  extern wxBitmap bq; // black queen

  extern void loadPieces();
  extern bool loadBitmap(wxBitmap& bmp, wxString file);
  extern wxBitmap* getBitmap(char p);
}

#endif
