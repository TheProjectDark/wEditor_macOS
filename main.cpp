/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */


#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/file.h>
#include "MainFrame.h"

//app class to launch this fuckass editor
class App : public wxApp
{
    public:
        bool OnInit();
};

//the main part of the code
MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    wxButton* save = new wxButton(panel, wxID_ANY, "Save");
    wxButton* open = new wxButton(panel, wxID_ANY, "Open");
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    buttonSizer->Add(save, 0, wxRIGHT, 5);
    buttonSizer->Add(open, 0);
    mainSizer->Add(buttonSizer, 0, wxALL | wxALIGN_LEFT, 5);
    mainSizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);

    panel->SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);

    save->Bind(wxEVT_BUTTON, &MainFrame::OnSave, this);
    open->Bind(wxEVT_BUTTON, &MainFrame::OnOpen, this);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
}

wxIMPLEMENT_APP(App);

//showing the frame
bool App::OnInit() {
    SetExitOnFrameDelete(true);

    MainFrame* mainFrame = new MainFrame("wEditor");
    mainFrame->SetClientSize(mainFrame->FromDIP(wxSize(800, 600)));
    mainFrame->Show();
    return true;
}

//save file function
void MainFrame::OnSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(
        this,
        "Save file",
        "",
        "",
        "Text & Code files (*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini)|*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini|All files (*.*)|*.*",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString path = saveFileDialog.GetPath();
    wxString content = textCtrl->GetValue();

    wxFile file;
    if (file.Open(path, wxFile::write))
    {
        file.Write(content);
        file.Close();
        wxMessageBox("File saved succesfully");
    }
    else
    {
        wxMessageBox("File saving error");
    }
}

//open file function
void MainFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(
        this,
        "Open file",
        "",
        "",
        "Text & Code files (*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini)|*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxFile file;
    if (!file.Open(openFileDialog.GetPath()))
    {
        wxMessageBox("Failed to open file");
        return;
    }

    wxString text;
    file.ReadAll(&text);
    file.Close();

    textCtrl->SetValue(text);
}

//ts shows the about window
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("wEditor Alpha v1.1",
                 "wEditor is simple cross-platform and open-souce text editor written on C++ using wxWidgets framework.", wxOK | wxICON_INFORMATION);
}

//ts closes the app
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}