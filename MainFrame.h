#pragma once
#include <wx/wx.h>

//creating the frame class with its functions
class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);

    private:
        wxTextCtrl* textCtrl;

        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnText(wxCommandEvent& event);
        void HighlightSyntax();
};