/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlightPython.h"

void SyntaxHighlightPython::ApplyHighlight(wxTextCtrl* textCtrl)
{
    wxString text = textCtrl->GetValue();
    wxTextAttr normal(*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    //import
    std::vector<wxString> moduleTokens = { "import", "from", "as" };
    wxTextAttr moduleAttr(wxColour(0, 128, 128));
    for (const auto& tok : moduleTokens) {
        size_t pos = text.find(tok);
        while (pos != wxString::npos) {
            textCtrl->SetStyle(pos, pos + tok.length(), moduleAttr);
            pos = text.find(tok, pos + 1);
        }
    }

    //types
    std::vector<wxString> types = { "int", "str", "float", "list", "dict", "tuple", "set", "bool" };
    wxTextAttr typeAttr(wxColour(51, 153, 255));
    for (const auto& t : types) {
        size_t pos = text.find(t);
        while (pos != wxString::npos) {
            textCtrl->SetStyle(pos, pos + t.length(), typeAttr);
            pos = text.find(t, pos + 1);
        }
    }

    //built-in library functions
    std::vector<wxString> builtins = {
        "print", "len", "range", "enumerate", "map", "filter", "zip", "sum", "min", "max", "open", "isinstance"
    };
    wxTextAttr funcAttr(wxColour(128, 179, 255));
    for (const auto& f : builtins) {
        size_t pos = text.find(f);
        while (pos != wxString::npos) {
            textCtrl->SetStyle(pos, pos + f.length(), funcAttr);
            pos = text.find(f, pos + 1);
        }
    }

    //some keywords
    std::vector<wxString> keywords = {
        "def", "class", "if", "elif", "else", "for", "while", "return", "try", "except", "finally", "with", "pass", "break", "continue", "lambda", "yield", "await", "async", "import", "from", "as"
    };
    wxTextAttr kwAttr(wxColour(230, 0, 230));
    for (const auto& k : keywords) {
        size_t pos = text.find(k);
        while (pos != wxString::npos) {
            textCtrl->SetStyle(pos, pos + k.length(), kwAttr);
            pos = text.find(k, pos + 1);
        }
    }

    //control structures
    std::vector<wxString> controlStructures = { "try", "except", "finally", "with" };
    wxTextAttr csAttr(wxColour(255, 165, 0));
    for (const auto& cs : controlStructures) {
        size_t pos = text.find(cs);
        while (pos != wxString::npos) {
            textCtrl->SetStyle(pos, pos + cs.length(), csAttr);
            pos = text.find(cs, pos + 1);
        }
    }

    //literals
    std::vector<wxString> literals = { "True", "False", "None" };
    wxTextAttr litAttr(*wxRED);
    for (const auto& l : literals) {
        size_t pos = text.find(l);
        while (pos != wxString::npos) {
            textCtrl->SetStyle(pos, pos + l.length(), litAttr);
            pos = text.find(l, pos + 1);
        }
    }

    //quotes
    wxTextAttr stringAttr(wxColour(255, 140, 0));
    std::vector<wxString> triple = { "\"\"\"", "'''" };
    for (const auto& delim : triple) {
        size_t pos = text.find(delim);
        while (pos != wxString::npos) {
            size_t endPos = text.find(delim, pos + delim.length());
            if (endPos != wxString::npos) {
                textCtrl->SetStyle((long)pos, (long)endPos + (long)delim.length(), stringAttr);
                pos = text.find(delim, endPos + delim.length());
            } else {
                break;
            }
        }
    }

    //quotes single and double
    std::vector<wxString> stringDelimiters = { "\"", "'" };
    for (const auto& delim : stringDelimiters) {
        size_t pos = text.find(delim);
        while (pos != wxString::npos) {
            size_t endPos = text.find(delim, pos + 1);
            // basic escape handling
            while (endPos != wxString::npos && endPos > 0 && text[endPos - 1] == '\\') {
                endPos = text.find(delim, endPos + 1);
            }
            if (endPos != wxString::npos) {
                textCtrl->SetStyle((long)pos, (long)endPos + 1, stringAttr);
                pos = text.find(delim, endPos + 1);
            } else {
                break;
            }
        }
    }

    //operators
    std::vector<wxString> operators_multi = { "==", "!=", "<=", ">=", "+=", "-=", "*=", "/=", "//", "**", "->", "and", "or", "not" };
    std::vector<wxString> operators_single = { "+", "-", "*", "/", "%", "=", "<", ">", ":" };
    wxTextAttr opAttr(wxColour(255, 0, 0));
    for (const auto& op : operators_multi) {
        size_t p = text.find(op);
        while (p != wxString::npos) {
            textCtrl->SetStyle((long)p, (long)p + op.length(), opAttr);
            p = text.find(op, p + 1);
        }
    }
    for (const auto& op : operators_single) {
        size_t p = text.find(op);
        while (p != wxString::npos) {
            textCtrl->SetStyle((long)p, (long)p + op.length(), opAttr);
            p = text.find(op, p + 1);
        }
    }

    //symbols
    std::vector<wxString> symbols = { "(", ")", "[", "]", "{", "}", ",", ".", ";" };
    wxTextAttr symAttr(wxColour(255, 102, 204));
    for (const auto& s : symbols) {
        size_t p = text.find(s);
        while (p != wxString::npos) {
            textCtrl->SetStyle((long)p, (long)p + s.length(), symAttr);
            p = text.find(s, p + 1);
        }
    }

    //comms
    wxTextAttr commentAttr(wxColour(128, 255, 170));
    size_t pos = text.find("#");
    while (pos != wxString::npos) {
        size_t endPos = text.find("\n", pos);
        if (endPos == wxString::npos) endPos = text.length();
        textCtrl->SetStyle((long)pos, (long)endPos, commentAttr);
        pos = text.find("#", endPos);
    }
}