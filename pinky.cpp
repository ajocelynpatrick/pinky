#include <iostream>
#include <wx/wx.h>
#include <wx/menu.h>
#include "pinky.h"
#include "frame.h"

IMPLEMENT_APP(Pinky)

bool Pinky::OnInit()
{
  Frame *fr = new Frame((wxFrame*) NULL, wxT("Pinky"));

  // we don't currently have a need for a menu
  #if USE_MENU
  wxMenu *filemenu = new wxMenu;
  wxMenu *helpmenu = new wxMenu;
  helpmenu->Append(wxID_ABOUT, wxT("&About...\tF1"), 
                   wxT("Show about dialog"));

  filemenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), 
                   wxT("End this program"));

  wxMenuBar *menubar = new wxMenuBar();
  menubar->Append(filemenu, wxT("&File"));
  menubar->Append(helpmenu, wxT("&Help"));
  fr->SetMenuBar(menubar);
  #endif

  // show the frame, and set it as our top level window
  fr->Show(true); SetTopWindow(fr); 

  // if we don't return true, we'll never live
  return true;
}
