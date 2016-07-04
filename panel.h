#ifndef PANEL_H
#define PANEL_H

#include <wx/wx.h>
#include "board.h"

class Frame;

class Panel : public wxPanel
{
  public: 
  Panel(Frame* fr, int x, int y, int w, int h);

  // event functions
  void onPaint(wxPaintEvent& e);
  void onLeftButton(wxMouseEvent& e);
  void onErase(wxEraseEvent& e);

  // user functions
  void movePiece(wxPoint& from, wxPoint& to);

  int getXY(int i); // get {x,y}-coord from an index i
  int getJI(int p); // get {j,i}-coord from a position p

  void clearLastSquare();
  void markCurrentSquare();
  wxPoint& getSquareByMouse(wxPoint& mouse);
  wxPoint& getIndexByMouse(wxPoint& mouse, wxPoint& p);

  // drawing functions
  void drawBoard(wxDC& dc);
  void drawPiece(wxDC& dc, wxBitmap bmp, int i, int j);

  // informational functions
  void showCurrentSquare();
  void showLastSquare();

  private:
  Frame *fr; // a pointer to the main frame
  wxPoint last; // last marked square
  wxPoint cur; // current marked square
  bool marked; // weather a squared is currently selected

  Board curBoard; // the current board

  DECLARE_EVENT_TABLE();
};

#endif
