#include "text_editor.h"
#include <iostream>

TextEditor::TextEditor()
{
    history.push("");
}

void TextEditor::edit(std::function<std::string(std::string)> editFunction)
{
    // Прилагаме функцията върху върха на стека
    history.push(editFunction(history.top()));
}

void TextEditor::print()
{
    std::cout << history.top() << std::endl;
}

std::string TextEditor::get()
{
    return history.top();
}

void TextEditor::undo()
{
    if (history.size() > 1)
        history.pop();
}