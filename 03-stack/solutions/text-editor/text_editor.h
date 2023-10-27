#include "../stack/stack.h"
#include <functional>
#include <string>

class TextEditor
{
private:
    // Ще държим стек, който пази стойностите на текста след всяка модифицираща операция. Това, което е на върха на стека, е текущата версия на текста в редактора.
    Stack<std::string> history;

public:
    TextEditor();

    void edit(std::function<std::string(std::string)> editFunction);
    void print();
    void undo();
    std::string get();
};