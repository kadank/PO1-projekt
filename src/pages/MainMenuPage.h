#ifndef PROJEKT_MAINMENUPAGE_H
#define PROJEKT_MAINMENUPAGE_H
#include <wx/clrpicker.h>
#include <wx/wx.h>

wxDECLARE_EVENT(MAIN_MENU_QUIT, wxCommandEvent);
wxDECLARE_EVENT(MAIN_MENU_NEW_GAME, wxCommandEvent);
wxDECLARE_EVENT(MAIN_MENU_ABOUT, wxCommandEvent);

class MainMenuPage : public wxPanel {
private:
    wxColourPickerCtrl* characterColorPicker;
    void OnExit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnNewGame(wxCommandEvent& evt);

public:
    MainMenuPage(wxWindow* parent);
};



#endif //PROJEKT_MAINMENUPAGE_H
