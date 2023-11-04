#include <iostream>
#include <stack>

// Помощна функция, която проверява дали можем да минем през позиция (i, j)
bool canMove(bool matrix[100][100], int rows, int cols, int i, int j)
{
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        return false;
    return matrix[i][j];
}

// Рекурсивното решение от първи курс
bool pathExistsHelper(bool matrix[100][100], int rows, int cols, int fromRow, int fromCol, int toRow, int toCol)
{
    if (fromRow == toRow && fromCol == toCol)
        return true;

    if (canMove(matrix, rows, cols, fromRow + 1, fromCol) && pathExistsHelper(matrix, rows, cols, fromRow + 1, fromCol, toRow, toCol))
    {
        return true;
    }

    if (canMove(matrix, rows, cols, fromRow, fromCol + 1) && pathExistsHelper(matrix, rows, cols, fromRow, fromCol + 1, toRow, toCol))
    {
        return true;
    }

    if (canMove(matrix, rows, cols, fromRow + 1, fromCol + 1) && pathExistsHelper(matrix, rows, cols, fromRow + 1, fromCol + 1, toRow, toCol))
    {
        return true;
    }

    return false;
}

struct Position
{
    int row;
    int col;
};

// Решение със стек
bool pathExistsStack(bool matrix[100][100], int rows, int cols)
{
    // Подържаме стек с клетките, които трябва да обходим
    std::stack<Position> positions;
    // Започваме с първата
    positions.push({0, 0});

    // Докато стекът не е празен
    while (!positions.empty())
    {
        // Вземаме текущата
        Position current = positions.top();
        positions.pop();

        // Ако тя съвпада с крайната цел, връщаме истина
        if (current.row == (rows - 1) && current.col == (cols - 1))
        {
            return true;
        }

        // В противен случай симулираме рекурсивните извиквания със слагане на елементи на стека
        if (canMove(matrix, rows, cols, current.row + 1, current.col))
        {
            positions.push({current.row + 1, current.col});
        }

        if (canMove(matrix, rows, cols, current.row, current.col + 1))
        {
            positions.push({current.row, current.col + 1});
        }

        if (canMove(matrix, rows, cols, current.row + 1, current.col + 1))
        {
            positions.push({current.row + 1, current.col + 1});
        }
    }

    // Ако не сме стигнали до финалната, значи път няма
    return false;
}

bool pathExists(bool matrix[100][100], int rows, int cols)
{
    return pathExistsHelper(matrix, rows, cols, 0, 0, rows - 1, cols - 1);
}

int main()
{
    bool labyrinth[100][100] = {{1, 0, 0, 0},
                                {1, 1, 1, 1},
                                {0, 1, 0, 1},
                                {0, 1, 0, 1}};

    std::cout << "Path exists recursive: " << pathExists(labyrinth, 4, 4) << std::endl;
    std::cout << "Path exists stack: " << pathExistsStack(labyrinth, 4, 4) << std::endl;

    return 0;
}