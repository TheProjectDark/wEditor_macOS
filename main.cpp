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
    Bind(wxEVT_TEXT, &MainFrame::OnText, this);
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

void MainFrame::OnText(wxCommandEvent& evt)
{
    HighlightSyntax();
    evt.Skip();
}


void MainFrame::HighlightSyntax()
{
    wxString text = textCtrl->GetValue();

    wxTextAttr normal(*wxBLACK);
    textCtrl->SetStyle(0, text.length(), normal);

    std::vector<wxString> keywords = {
        "return", "if", "else", "while"
    };

    for (const auto& word : keywords)
    {
        size_t pos = text.find(word);
        while (pos != wxString::npos) {
            wxTextAttr kw(wxColour(128, 0, 128));
            textCtrl->SetStyle(pos, pos + word.length(), kw);
            pos = text.find(word, pos + 1);
        }
    }

    std::vector<wxString> types = {
        "string", "char", "int", "float", "double", "bool", "void"
    };
    for (const auto& type : types)
    {
        size_t pos = text.find(type);
        while (pos != wxString::npos) {
            wxTextAttr typeAttr(*wxBLUE);
            textCtrl->SetStyle(pos, pos + type.length(), typeAttr);
            pos = text.find(type, pos + 1);
        }   
    }
    std::vector<wxString> comments = {
        "//", "/*", "*/"
    };
    for (const auto& comment : comments)
    {
        size_t pos = text.find(comment);
        while (pos != wxString::npos) {
            wxTextAttr commentAttr(*wxGREEN);
            textCtrl->SetStyle(pos, pos + comment.length(), commentAttr);
            pos = text.find(comment, pos + 1);
        }
    }
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
    wxMessageBox("wEditor is simple cross-platform and open-souce text editor written on C++ using wxWidgets framework.",
                 "wEditor Alpha v1.2", wxOK | wxICON_INFORMATION);
}

//ts closes the app
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}