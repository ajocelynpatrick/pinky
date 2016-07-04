#include <iostream>
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include "panel.h"
#include "frame.h"
#include "set.h"

BEGIN_EVENT_TABLE(Panel, wxPanel)
  EVT_PAINT(Panel::onPaint)
  EVT_LEFT_DOWN(Panel::onLeftButton)
  EVT_ERASE_BACKGROUND(Panel::onErase)
END_EVENT_TABLE()

void Panel::onErase(wxEraseEvent& e)
{
}

void Panel::clearLastSquare()
{
  wxClientDC dc(this);

  wxPen pen = *wxBLACK_PEN; pen.SetWidth(fr->penWid());
   dc.SetPen(pen); dc.SetBrush(*wxTRANSPARENT_BRUSH);
  dc.DrawRectangle(last.x, last.y, fr->szSquare(), fr->szSquare());

  marked = false;
}

void Panel::markCurrentSquare()
{
  // we have to improve this mark. we gotta paint a thick border around
  // the square, not just inner it. im thinking on a simple, but fast
  // way, to do this. the truth may be that we shouldn't be painting
  // here. just mark the underlying board and generate a paint event.

  wxClientDC dc(this);

  wxPen pen = *wxRED_PEN; pen.SetWidth(fr->penWid());
  dc.SetPen(pen); dc.SetBrush(*wxTRANSPARENT_BRUSH);
  dc.DrawRectangle(cur.x, cur.y, fr->szSquare(), fr->szSquare()); 

  marked = true;
}

wxPoint& Panel::getIndexByMouse(wxPoint& mouse, wxPoint& p)
{
  // convert mouse click to square indices; the point p is returned to
  // make it programmer friendly; you don't necessarily need to care
  // about the return value.

  int len = fr->szSquare();

  p.x = (mouse.x / len) + 1;
  p.y = (mouse.y / len) + 1;

  return p;
}

wxPoint& Panel::getSquareByMouse(wxPoint& mouse)
{
  // convert mouse click to square point; saves in cur; we return a
  // reference to cur just to make it programmer friendly; this way, we
  // can write getSquareByMouse().x or getSquareByMouse().y

  int len = fr->szSquare();

  cur.x = (mouse.x / len) * len;
  cur.y = (mouse.y / len) * len;

  return cur;
}

void Panel::showLastSquare()
{
  // tmp will be changed and returned by getIndexByMouse; i wish i
  // didn't have to use a tmp object here. so getIndexByMouse() could
  // return a static object; is that a good idea?

  wxPoint tmp;

  std::cout << "Last square @ ";
  std::cout << "["<< getIndexByMouse(last, tmp).y <<"]";
  std::cout << "["<< getIndexByMouse(last, tmp).x <<"]" << std::endl;
}

void Panel::showCurrentSquare()
{
  // tmp will be changed and returned by getIndexByMouse; i wish i
  // didn't have to use a tmp object here. so getIndexByMouse() could
  // return a static object... is that a good idea?

  wxPoint tmp;

  std::cout << "Current square @ ";
  std::cout << "["<< getIndexByMouse(cur, tmp).y <<"]";
  std::cout << "["<< getIndexByMouse(cur, tmp).x <<"]" << std::endl;
}

void Panel::onLeftButton(wxMouseEvent& e)
{
  wxPoint mouse; wxClientDC dc(this);
  mouse = e.GetLogicalPosition(dc);

  int len = fr->szSquare();

  if (mouse.x >= len*fr->dimWid() || mouse.y >= len*fr->dimHei()) 
    return; // out of board

  // save last square position before we lose the information
  last = cur; 

  // set cur to the new selected square
  getSquareByMouse(mouse);

  // is this just a first selection? if so, we're done
  if (!marked) { markCurrentSquare(); return; }

  // was this an unselection?
  if (last == cur) { 
    if (marked) clearLastSquare(); else markCurrentSquare();
    return; 
  }

  // if last square is a legal piece, then this is a move
  movePiece(last, cur); clearLastSquare(); //markCurrentSquare();

  Refresh();  // paint now
}

void Panel::drawBoard(wxDC& dc)
{
  int i, j; int len = fr->szSquare();

  wxPen pen = *wxBLACK_PEN;
  pen.SetWidth(fr->penWid()); dc.SetPen(pen);

  dc.SetBrush(*wxWHITE_BRUSH);
  for (i = 0; i < fr->dimHei(); i=i+2)
    for (j = 0; j < fr->dimWid(); j=j+2)
      dc.DrawRectangle(i*len, j*len, len, len);

  for (i = 1; i < fr->dimHei(); i=i+2)
    for (j = 1; j < fr->dimWid(); j=j+2)
      dc.DrawRectangle(i*len, j*len, len, len);

  wxBrush pink(wxColor(0xff,0xb5,0xc5),wxSOLID);
  dc.SetBrush(pink);
  for (i = 1; i < fr->dimHei(); i=i+2)
    for (j = 0; j < fr->dimWid(); j=j+2)
      dc.DrawRectangle(i*len, j*len, len, len);

  for (i = 0; i < fr->dimHei(); i=i+2)
    for (j = 1; j < fr->dimWid(); j=j+2)
      dc.DrawRectangle(i*len, j*len, len, len);

  if (marked) {
    markCurrentSquare();
  }

  // put the pieces in place
  for(int i=1; i <= curBoard.dim(); ++i)
    for (int j=1; j <= curBoard.dim(); ++j) {
      wxBitmap* m = set::getBitmap(curBoard.getPiece(i,j));
      if (m == NULL) continue;
      drawPiece(dc, *m, j, i);
    }
}

void Panel::drawPiece(wxDC& dc, wxBitmap map, int i, int j)
{
  dc.DrawBitmap(map, getXY(i), getXY(j), true);
}

void Panel::movePiece(wxPoint& from, wxPoint& to)
{
  curBoard.movePiece(getJI(from.y), getJI(from.x), getJI(to.y), getJI(to.x));
}

int Panel::getJI(int p)
{
  // return board index from a pixel coordinate p
  return p / fr->szSquare() + 1;
}

int Panel::getXY(int i)
{
  // the first row of the board is 1, not 0; do not treat the board as
  // an array, though it is one. let's account for all index arithmetic
  // inside functions, not in callers. since we deal with the algebraic
  // chess notation, this convention will be useful because it will
  // match the notation rows and columns --- the algebraic notation
  // begins at 1 and ends at 8

  return (fr->szSquare() * (i - 1));
}

void Panel::onPaint(wxPaintEvent& e)
{
  // we're painting on a memory device which will be copied to the
  // panel's device context. in panel's constructor, we tell the window
  // system that we don't want it to erase the panel background or paint
  // it; so this request plus our buffered device gives us no
  // flickering. this is not the fastest thing that we can do, but it's
  // enough for now.

  wxBufferedPaintDC dc(this); drawBoard(dc);  
}

Panel::Panel(Frame *f, int x, int y, int w, int h)
  : wxPanel((wxWindow*) f , wxID_ANY, wxPoint(x, y), wxSize(w, h))
{
  // initially, there's no marked square; we only mark one when a user
  // clicks at one; fr is a pointer to our frame; the frame keeps many
  // details about the application which while painting we need, so it's
  // a useful pointer
  fr = f; marked = false;

  // initially, current[1][1] = last[1][1] with both @ (0,0)
  last = cur = wxPoint(0,0);

  // load the set of pieces in memory
  set::loadPieces();

  // i'm drawing a standard board below, but in production we won't do
  // this here; we will do this in some setup board function; what we
  // will do here is read the current board (a 10x10 array) and paint
  // the pieces accordingly

  curBoard.setPos(8,1,'R'); 
  curBoard.setPos(8,2,'N'); 
  curBoard.setPos(8,3,'B'); 
  curBoard.setPos(8,4,'Q'); 
  curBoard.setPos(8,5,'K'); 
  curBoard.setPos(8,6,'B'); 
  curBoard.setPos(8,7,'N'); 
  curBoard.setPos(8,8,'R'); 

  for (int j = 1; j <= fr->dimWid(); j++)
    curBoard.setPos(7,j,'P');

  curBoard.setPos(1,1,'r'); 
  curBoard.setPos(1,2,'n'); 
  curBoard.setPos(1,3,'b'); 
  curBoard.setPos(1,4,'q'); 
  curBoard.setPos(1,5,'k'); 
  curBoard.setPos(1,6,'b'); 
  curBoard.setPos(1,7,'n'); 
  curBoard.setPos(1,8,'r'); 

  for (int j = 1; j <= fr->dimWid(); j++)
    curBoard.setPos(2,j,'p');

  curBoard.show();

  // we'll handle the background ourselves
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}
