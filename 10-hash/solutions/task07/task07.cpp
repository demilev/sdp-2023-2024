#include <vector>
#include <string>
#include <iostream>

#include "../hashtable.h"

struct Student
{
    std::string firstName;
    std::string lastName;

    // Добавяме и оператор равно за класа, който се ползва в имплементацията на хеш таблица за сравняване на ключовете
    bool operator==(const Student &other)
    {
        return firstName == other.firstName && lastName == other.lastName;
    }
};

struct StudentData
{
    int fn;
    std::string address;
    std::vector<double> grades;
};

// Версия на std::hash за Student
template <>
struct std::hash<Student>
{
    std::size_t operator()(const Student &k) const
    {
        // просто преизползваме std::hash за стринг като смятаме хеш стойността на string-a, който се получава чрез конкатенацията на първото и второ име на студента
        return std::hash<std::string>()(k.firstName + " " + k.lastName);
    }
};

int main()
{
    HashTable<Student, StudentData> students(100);

    Student ivan = {"Ivan", "Ivanov"};

    students.put(ivan, {81352, "Sofia", {5.5, 6, 3}});

    std::cout << "The faculty number of Ivan Ivanov is: " << students.get(ivan).fn << std::endl;

    return 0;
}