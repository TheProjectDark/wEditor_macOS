#include "SyntaxHighlightAssembly.h"

void SyntaxHighlightAssembly::ApplyHighlight(wxTextCtrl* textCtrl)
{
    wxString text = textCtrl->GetValue();

    wxTextAttr normal (*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    //assembly instructions
    std::vector<wxString> instructions = {
        "mov", "add", "sub", "mul", "div", "jmp", "cmp", "je", "jne", "call", "ret", "push", "pop", "jg", "jl", "jge", "jle", "and", "or", "xor", "not", "shl", "shr", "lea", "int", "nop", "add"
    };

    for (const auto& instr : instructions)
    {
        size_t pos = text.find(instr);
        while (pos != wxString::npos) {
            wxTextAttr instrAttr(wxColour(0, 153, 51));
            textCtrl->SetStyle(pos, pos + instr.length(), instrAttr);
            pos = text.find(instr, pos + 1);
        }
    }

    //assembly registers
    std::vector<wxString> registers = {
        "eax", "ebx", "ecx", "edx", "esi", "edi", "esp", "ebp",
        "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rsp", "rbp",
        "ax", "bx", "cx", "dx", "si", "di", "sp", "bp",
        "al", "bl", "cl", "dl"
    };

    for (const auto& reg : registers)
    {
        size_t pos = text.find(reg);
        while (pos != wxString::npos) {
            wxTextAttr regAttr(wxColour(0, 102, 204));
            textCtrl->SetStyle(pos, pos + reg.length(), regAttr);
            pos = text.find(reg, pos + 1);
        }
    }

    //comments
    size_t commentPos = text.find(";");
    while (commentPos != wxString::npos) {
        wxTextAttr commentAttr(wxColour(128, 128, 128));
        textCtrl->SetStyle(commentPos, text.length(), commentAttr);
        commentPos = text.find(";", commentPos + 1);
    }

    //numbers
    for (size_t i = 0; i < text.length(); ++i) {
        if (wxIsdigit(text[i])) {
            size_t start = i;
            while (i < text.length() && wxIsdigit(text[i])) {
                ++i;
            }
            wxTextAttr numberAttr(wxColour(204, 0, 204));
            textCtrl->SetStyle(start, i, numberAttr);
        }
    }

    //labels
    size_t labelPos = text.find(":");
    while (labelPos != wxString::npos) {
        size_t start = text.rfind('\n', labelPos);
        if (start == wxString::npos) start = 0; else start += 1;
        wxTextAttr labelAttr(wxColour(255, 153, 0));
        textCtrl->SetStyle(start, labelPos + 1, labelAttr);
        labelPos = text.find(":", labelPos + 1);
    }
}