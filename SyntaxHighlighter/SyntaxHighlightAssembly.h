#pragma once
#include <wx/wx.h>
#include "SyntaxHighlighter.h"

class SyntaxHighlightAssembly : public SyntaxHighlighter {
    void ApplyHighlight(wxTextCtrl* textCtrl) override;
    wxString GetLanguageName() const override { return "Assembly"; }
};