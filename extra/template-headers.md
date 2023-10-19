# Header файлове с шаблонни класове

Обикновено разделяме `c++` програмите на заглавни файлове с разширение `.h`, в които стоят само декларациите на класове/функции, и имплементационни файлове с разширение `.cpp`, в които добавяме заглавните файлове с `#include` и в които даваме дефиницията/имплементацията на класовете/функциите в заглавния файл. Когато искаме да ползваме тези класове/функции на друго място добавяме само заглавните файлове, защото процесът по компилация и свързване в `c++ ` ни позволява разделно компилиране. Пример за тази структура:

`example.h`:
```c++
class Test {
private:
    int a;
public:
    Test(int);
    int getA();
};
```

`example.cpp`:
```c++
#include "example.h"

Test::Test(int a): a(a) {}

int Test::getA() {
    return a;
}
```

`main.cpp`:
```c++
#include <iostream>
#include "example.h"

int main() {
    Test t(5);
    std::cout << t.getA();

    return 0;
}
```


## Класове шаблони

Нека обаче да видим как изглежда това, когато работим с класове шаблони

`box.h`:
```c++
template <typename T>
class Box {
private:
    T a;
public:
    Box(T);
    T getA();
};
```

`box.cpp`:
```c++
#include "box.h"

template <typename T>
Box<T>::Box(T a): a(a) {}

template <typename T>
T Box<T>::getA() {
    return a;
}
```

`main.cpp`:
```c++
#include <iostream>
#include "box.h"

int main() {
    Box<int> b(5);
    std::cout << b.getA();

    return 0;
}
```

При опит да компилираме горния код получаваме грешка:

```
Undefined symbols for architecture x86_64:
  "Box<int>::getA()"
```

Причината за това е, че шаблоните са просто шаблони. 
Компилацията на `box.cpp` не води до нищо.
"Истински" клас `Box` с конкретен тип за него се генерира, когато бъде използван. 
В случая в `main` функцията се ползва `Box<int>`.
При това позлване компилаторът ще генерира версия на класа `Box` с тип `int`.
Тъй като обаче сме добавили само заглавния файл `box.h`, то компилирана имплементация за `Box<int>` не съществува и съответно компилаторът не успява да компилира и `main.cpp`.

Ршението на проблема е да държим декларация и дефиниция на шаблонен клас на едно място и винаги да ги #include-ваме заедно, където ги ползваме. Това може да се постигне по няколко начина:

## 1. `#include "box.cpp"`

Вместо да добавяме само заглавния файл, добавяме файлът с имплементацията на шаблона.

`main.cpp`:
```c++
#include <iostream>
#include "box.cpp"

int main() {
    Box<int> b(5);
    std::cout << b.getA();

    return 0;
}
```

## 2. `box.h` съдържа и имплементацията

Слагаме декларация и имплементация заедно в заглавния файл

`box.h`:
```c++
template <typename T>
class Box {
private:
    T a;
public:
    Box(T);
    T getA();
};

template <typename T>
Box<T>::Box(T a): a(a) {}

template <typename T>
T Box<T>::getA() {
    return a;
}
```

`main.cpp`:
```c++
#include <iostream>
#include "box.h"

int main() {
    Box<int> b(5);
    std::cout << b.getA();

    return 0;
}
```

## 3. `box.h` добавя `box.tpp`

Това е вариация на предния подход, при който все пак имаме два отделни файла.

`box.h`:
```c++
template <typename T>
class Box {
private:
    T a;
public:
    Box(T);
    T getA();
};

#include "box.tpp"
```

`box.tpp`:
```c++
#include "box.h"

template <typename T>
Box<T>::Box(T a): a(a) {}

template <typename T>
T Box<T>::getA() {
    return a;
}
```

`main.cpp`:
```c++
#include <iostream>
#include "box.h"

int main() {
    Box<int> b(5);
    std::cout << b.getA();

    return 0;
}
```