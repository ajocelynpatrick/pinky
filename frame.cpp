#include <iostream>
#include <wx/wx.h>
#include "pinky.h"
#include "panel.h"
#include "frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::onQuit)
  EVT_MENU(wxID_ABOUT, Frame::onAbout)
  EVT_SIZE(Frame::onSize)
END_EVENT_TABLE()

void Frame::onQuit(wxCommandEvent& WXUNUSED(e))
{
  Close(true);
}

void Frame::onSize(wxSizeEvent& e)
{
  wxSize s; s = e.GetSize();
  
  #ifdef DEBUG
  std::cout << "New size: " << s.GetWidth() 
            << " by " << s.GetHeight() << "\n" << std::flush;
  #endif
}

void Frame::onAbout(wxCommandEvent& WXUNUSED(e))
{
  wxBeginBusyCursor();
  wxMessageDialog dialog(this,
                         wxT("Enjoy this program. Enjoy this life.\n"),
                         wxT("About this program"), wxOK | wxICON_INFORMATION);
  dialog.ShowModal(); wxEndBusyCursor();
}

Frame::Frame(wxFrame *fr, const wxChar* title)
  : wxFrame(fr, wxID_ANY, title)
{
  // size of a square; dimentions of the board
  pxSquare = 44; nWid = nHei = 8; 

  // the width of a pen to paint borders of squares
  penWidth = 1;

  // create the panel
  pan = new Panel(this, 0, 0, szSquare() * dimWid(), szSquare() * dimHei());

  #if USE_STATUS_BAR
  // it actually makes a difference where we create the status bar
  // because of the size of frames, panels, et cetera; i haven't figured
  // out how to properly arrange the status bar without bothering the
  // panel, so i'm leaving this out for now
  CreateStatusBar(1); SetStatusText(wxT("Pinky is ready."));
  #endif

  // let's put a sizer on this frame and attach the panel to it
  wxBoxSizer* sizerPanel = new wxBoxSizer(wxVERTICAL);
  
  // take the exact size of the panel
  sizerPanel->Add(pan, 1, 0, 0); 

  // attach this sizer to the frame
  SetSizer(sizerPanel);

  // fit the frame to the panel
  sizerPanel->Fit(this); 

  // dont get smaller than the panel
  sizerPanel->SetSizeHints(this);
}

Frame::~Frame()
{
  std::cout << "Shutting down...\n";
}
