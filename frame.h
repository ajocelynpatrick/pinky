#ifndef FRAME_H
#define FRAME_H

#include <wx/wx.h>

class Panel;

class Frame : public wxFrame
{
  public:
  Frame(wxFrame* fr, const wxChar* title); 
  ~Frame();

  // inline functions
  int szSquare() { return pxSquare; }
  int dimWid() { return nWid; }
  int dimHei() { return nHei; }
  int penWid() { return penWidth; }

  void onQuit(wxCommandEvent& e);
  void onAbout(wxCommandEvent& e);
  void onSize(wxSizeEvent& e);

  private:
  // the size in pixels a square
  int pxSquare;

  // the dimensions (in sq units) of the board
  int nWid; int nHei;

  // the thickness of the pen
  int penWidth;

  // let's keep a handle to the panel
  Panel* pan;

  DECLARE_EVENT_TABLE();
};

enum
{
};

#endif
