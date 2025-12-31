/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlighter.h"
#include "SyntaxHighlightCPP.h"
#include "SyntaxHighlightC.h"
#include "SyntaxHighlightPython.h"
#include "SyntaxHighlightAssembly.h"
#include "SyntaxHighlightSQL.h"

SyntaxHighlighter* HighlighterFactory::CreateHighlighter(const wxString& language) {
    if (language == "Text") {
        return nullptr;
    }
    else if (language == "C++") {
        return new SyntaxHighlightCPP();
    }
    else if (language == "C") {
        return new SyntaxHighlightC();
    } 
    else if (language == "Python") {
        return new SyntaxHighlightPython();    
    }
    else if (language == "Assembly") {
        return new SyntaxHighlightAssembly();
    }
    else if (language == "SQL Script") {
        return new SyntaxHighlightSQL();
    }
    return new SyntaxHighlightCPP();
}

std::vector<wxString> HighlighterFactory::GetAvailableLanguages() {
    return {
        "Text",
        "C++",
        "C",
        "Python",
        "Assembly",
        "SQL Script"
    };
}