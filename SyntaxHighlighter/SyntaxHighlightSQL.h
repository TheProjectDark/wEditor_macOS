/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#pragma once
#include <wx/wx.h>
#include "SyntaxHighlighter.h"

class SyntaxHighlightSQL : public SyntaxHighlighter {
    void ApplyHighlight(wxTextCtrl* textCtrl) override;
    wxString GetLanguageName() const override { return "SQL Script"; }
};