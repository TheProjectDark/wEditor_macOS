/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlightCPP.h"

void SyntaxHighlightCPP::ApplyHighlight(wxTextCtrl* textCtrl)
{

    wxString text = textCtrl->GetValue();

    wxTextAttr normal(*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    //important shi like includes and stuff
    std::vector<wxString> preprocessorDirectives = {
        "#include", "#define", "#ifdef", "#ifndef", "#endif", "#pragma"
    };
    for (const auto& directive : preprocessorDirectives)
    {
        size_t pos = text.find(directive);
        while (pos != wxString::npos) {
            wxTextAttr preprocAttr(wxColour(0, 128, 128));
            textCtrl->SetStyle(pos, pos + directive.length(), preprocAttr);
            pos = text.find(directive, pos + 1);
        }
    }

    //also important shi like namespaces
    std::vector<wxString> namespaces = {
        "std", "namespace"
    };
    for (const auto& ns : namespaces)
    {
        size_t pos = text.find(ns);
        while (pos != wxString::npos) {
            wxTextAttr nsAttr(wxColour(0, 100, 0));
            textCtrl->SetStyle(pos, pos + ns.length(), nsAttr);
            pos = text.find(ns, pos + 1);
        }
    }

    //types
    std::vector<wxString> types = {
        "int", "float", "double", "char", "void", "bool", "long", "short", "unsigned", "signed", "std::string", "std::vector", "std::map", "string", "class"
    };
    for (const auto& type : types)
    {
        size_t pos = text.find(type);
        while (pos != wxString::npos) {
            wxTextAttr typeAttr(wxColour(51, 153, 255));
            textCtrl->SetStyle(pos, pos + type.length(), typeAttr);
            pos = text.find(type, pos + 1);
        }   
    }

    //standard lib functions
    std::vector<wxString> standardLibraryFunctions = {
        "printf", "scanf", "cout", "cin", "endl", "std::cout", "std::cin"
    };
    for (const auto& func : standardLibraryFunctions)
    {
        size_t pos = text.find(func);
        while (pos != wxString::npos) {
            wxTextAttr funcAttr(wxColour(128, 179, 255));
            textCtrl->SetStyle(pos, pos + func.length(), funcAttr);
            pos = text.find(func, pos + 1);
        }
    }

    //some keywords
    std::vector<wxString> keywords = {
        "return", "if", "else", "while"
    };
    for (const auto& word : keywords)
    {
        size_t pos = text.find(word);
        while (pos != wxString::npos) {
            wxTextAttr kw(wxColour(230, 0, 230));
            textCtrl->SetStyle(pos, pos + word.length(), kw);
            pos = text.find(word, pos + 1);
        }
    }

    //control structures
    std::vector<wxString> controlStructures = {
        "for", "switch", "case", "break", "continue"
    };
    for (const auto& cs : controlStructures)
    {
        size_t pos = text.find(cs);
        while (pos != wxString::npos) {
            wxTextAttr csAttr(wxColour(255, 165, 0));
            textCtrl->SetStyle(pos, pos + cs.length(), csAttr);
            pos = text.find(cs, pos + 1);
        }
    }

    //access modifiers
    std::vector<wxString> accessModifiers = {
        "public", "private", "protected"
    };
    for (const auto& modifier : accessModifiers)
    {
        size_t pos = text.find(modifier);
        while (pos != wxString::npos) {
            wxTextAttr modAttr(wxColour(75, 0, 130));
            textCtrl->SetStyle(pos, pos + modifier.length(), modAttr);
            pos = text.find(modifier, pos + 1);
        }
    }

    //literals
    std::vector<wxString> literals = {
        "true", "false", "NULL"
    }; 
    for (const auto& literal : literals)
    {
        size_t pos = text.find(literal);
        while (pos != wxString::npos) {
            wxTextAttr litAttr(*wxRED);
            textCtrl->SetStyle(pos, pos + literal.length(), litAttr);
            pos = text.find(literal, pos + 1);
        }
    }

    //strings
    std::vector<wxString> stringDelimiters = {
        "\"", "'"
    };
    for (const auto& delimiter : stringDelimiters)
    {
        size_t pos = text.find(delimiter);
        while (pos != wxString::npos) {
            size_t endPos = text.find(delimiter, pos + 1);
            if (endPos != wxString::npos) {
                wxTextAttr stringAttr(wxColour(255, 140, 0));
                textCtrl->SetStyle(pos, endPos + 1, stringAttr);
                pos = text.find(delimiter, endPos + 1);
            } else {
                break;
            }
        }

    }

    //operators
    std::vector<wxString> operators_multi = {
        "==", "!=", "<=", ">=", "&&", "||", "++", "--"
    };
    std::vector<wxString> operators_single = {
        "+", "-", "*", "/", "=", "<", ">", 
    };
    for (const auto& op : operators_multi)
    {
        size_t pos = text.find(op);
        while (pos != wxString::npos) {
            wxTextAttr opAttr(wxColour(255, 0, 0));
            textCtrl->SetStyle(pos, pos + op.length(), opAttr);
            pos = text.find(op, pos + 1);
        }
    }
    for (const auto& op : operators_single)
    {
        size_t pos = text.find(op);
        while (pos != wxString::npos) {
            wxTextAttr opAttr(wxColour(255, 0, 0));
            textCtrl->SetStyle(pos, pos + op.length(), opAttr);
            pos = text.find(op, pos + 1);
        }
    }

    //symbols
    std::vector<wxString> symbols = {
        "{", "}", "(", ")", "[", "]", ";", ",", "."
    };
    for (const auto& symbol : symbols)
    {
        size_t pos = text.find(symbol);
        while (pos != wxString::npos) {
            wxTextAttr symAttr(wxColour(255, 102, 204));
            textCtrl->SetStyle(pos, pos + symbol.length(), symAttr);
            pos = text.find(symbol, pos + 1);
        }
    }

    //comms
    std::vector<wxString> comments = {
        "//", "/*", "*/"
    };
    for (const auto& comment : comments)
    {
        size_t pos = text.find(comment);
        while (pos != wxString::npos) {
            size_t endPos;
            if (comment == "//") {
                endPos = text.find("\n", pos);
            } else if (comment == "/*") {
                endPos = text.find("*/", pos) + 2;
            } else {
                pos = text.find(comment, pos + 1);
                continue;
            }
            if (endPos != wxString::npos) {
                wxTextAttr commentAttr(wxColour(128, 255, 170));
                textCtrl->SetStyle(pos, endPos, commentAttr);
                pos = text.find(comment, endPos);
            } else {
                break;
            }
        }
    }
}