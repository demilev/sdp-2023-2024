# Измерване на времето за изпълнение на дадена функция

Стандартната библиотека на c++ ни позволява да работим със системния часовник и по този начин да измерваме времето за изпълнение на дадена функция.

По следния начин можем да вземем текущото време:

```c++
#include <chrono>

std::chrono::high_resolution_clock::now();
```

А по следния начин можем да измерим разликата между две времена:

```c++
#include <chrono>

std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
```


Имайки тези две техники можем да измерим колко време отнема произволна част от кода ни:


```c++
#include <chrono>
#include <iostream>

int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();

    // ...
    // ...
    // някакъв код, който искаме да измерим
    // ...
    // ...

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

    std::cout << "It took: " << duration.count() / 1000.0 <<  " seconds" << std::endl;

    return 0;
}
```


## Binary Search vs Linear Search

Използвайки тази техника можем да сравним търсенето в сортиран масив с техниката `Binary Search` и стандартното търсене в несортиран масив, което изисква обхождане на всички елементи.

Резултатите са впечатляващи!

```
Linear search took 0.385 seconds
Binary search took 0.001 seconds
```

```c++
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
 

// Функция за търсене в несортиран вектор
// Сложност по време - O(n)
bool find(std::vector<int>& v, int x)
{
    for (int i : v)
    {
        if (i == x)
        {
            return true;
        }
    }

    return false;
}

// Функция за търсене в сортиран вектор
// Сложност по време - O(lgn)
bool binarySearch(std::vector<int>& v, int left, int right, int x)
{
    if (left >= right)
    {
        return false;
    }

    int mid = (left + right) / 2;

    if (v[mid] == x)
    {
        return true;
    }
    else if (v[mid] < x)
    {
        return binarySearch(v, mid + 1, right, x);
    }
    
    return binarySearch(v, left, mid, x);
}

int main()
{
    
    // Генерираме 1 милион произволни числа
    std::vector<int> randomNumbers(1000000);
    auto f = []() -> int { return rand() % 10000; };
    std::generate(randomNumbers.begin(), randomNumbers.end(), f);
    
    // Щe пазим две версии на този вектор - сортирана и несортирана
    std::vector<int> unsorted = randomNumbers;
    std::vector<int> sorted = randomNumbers;
    std::sort(sorted.begin(), sorted.end());
    
    int x = rand() % 10000;

    auto start = std::chrono::high_resolution_clock::now();
    
    // Измерваме колко време отнема за линейно търсене в несортираната версия
    find(unsorted, x);

    auto stop = std::chrono::high_resolution_clock::now();
 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
 
    std::cout << "Linear search took " << duration.count() / 1000.0 << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    // Измерваме колко време отнема за двоично търсене в сортираната версия
    binarySearch(sorted, 0, sorted.size(), x);

    stop = std::chrono::high_resolution_clock::now();
 
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
 
    std::cout << "Binary search took " << duration.count() / 1000.0 << " seconds" << std::endl;
 
    return 0;
}
```