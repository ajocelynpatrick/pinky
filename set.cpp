#include <iostream>
#include "set.h"

wxBitmap set::wp; // white pawn
wxBitmap set::wr; // white rook
wxBitmap set::wn; // white knight
wxBitmap set::wb; // white bishop
wxBitmap set::wk; // white king
wxBitmap set::wq; // white queen

wxBitmap set::bp; // black pawn
wxBitmap set::br; // black rook
wxBitmap set::bn; // black knight
wxBitmap set::bb; // black bishop
wxBitmap set::bk; // black king
wxBitmap set::bq; // black queen

bool set::loadBitmap(wxBitmap& bmp, wxString file)
{
  bmp  = wxBitmap(file, wxBITMAP_TYPE_PNG);
  if (bmp.Ok()) return true; // well loaded

  #if DEBUG 
  std::cout << "I couldn't load " << file << ".\n";
  std::cout << "Ignoring it.\n" << std::flush;
  #endif

  return false;
}

wxBitmap* set::getBitmap(char p)
{
  if (p == 'R') return &set::wr;
  if (p == 'N') return &set::wn;
  if (p == 'B') return &set::wb;
  if (p == 'K') return &set::wk;
  if (p == 'Q') return &set::wq;
  if (p == 'P') return &set::wp;

  if (p == 'r') return &set::br;
  if (p == 'n') return &set::bn;
  if (p == 'b') return &set::bb;
  if (p == 'k') return &set::bk;
  if (p == 'q') return &set::bq;
  if (p == 'p') return &set::bp;

  return NULL;
}

void set::loadPieces() 
{
  wxImage::AddHandler(new wxPNGHandler);

  //std::cout << "Loading pieces...\n" << std::flush;

  loadBitmap(set::wp, wxT("set/wp.png"));
  loadBitmap(set::wr, wxT("set/wr.png"));
  loadBitmap(set::wn, wxT("set/wn.png"));
  loadBitmap(set::wb, wxT("set/wb.png"));
  loadBitmap(set::wk, wxT("set/wk.png"));
  loadBitmap(set::wq, wxT("set/wq.png"));

  loadBitmap(set::bp, wxT("set/bp.png"));
  loadBitmap(set::br, wxT("set/br.png"));
  loadBitmap(set::bn, wxT("set/bn.png"));
  loadBitmap(set::bb, wxT("set/bb.png"));
  loadBitmap(set::bk, wxT("set/bk.png"));
  loadBitmap(set::bq, wxT("set/bq.png"));
}
