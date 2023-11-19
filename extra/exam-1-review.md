# Контролно 1

## Най-често срещани грешки

* Задачата не се разбива на подзадачи
* Работа с динамична памет
    * Изтриване на памет, която не е динамично задалена
    * Насочване на указател към памет, която е заделена на стековата рамка
    * Неизползване на динамична памет
* Технически неточности
    * обхаждане на списък до предполседния му елемент
    * неточно бороване с индекси


## Задачата не се разбива на подзадачи

**Пример 1 - Втори вариант, задача 2**

Решение 1:
```c++
template <typename T>
void split(box<T>* L1, box<T>* L2, std::function<T(bool)> p){

    while(L1 != nullptr){

        if(p(L1->data)){
            remove(L1);
            pushBack(L2, L1->data);
        }

        L1 = L1->next;
    }
}
```

Решение 2:
```c++
template <typename T>
void split(box<T>*& head1, box<T>*& head2, bool(*p) (T&))
{
    box<T>* tail = head2;
    box<T>* copy_head1 = head1;
    box<T>* copy_head2 = head2;
    while (head2 != nullptr)
    {
        tail = head2;
        head2 = head2->next;
    }
    head2 = copy_head2;
    while(head1 != nullptr)
    {
        if (p(head1->data))
        {
            box<T>* temp = new box<T>(head1->data);
            tail->link(temp);
            tail = temp;

            box<T>* remove = head1;
            if (remove->prev == nullptr && remove->next != nullptr)
            {
                head1->next->prev = nullptr;
                head1 = head1->next;
                delete remove;
            }

            else if (remove->next != nullptr)
            {
                head1->prev->next = head1->next;
                head1->next->prev = head1->prev;
                head1 = head1->next;
                delete remove;
            }
            else
            {
                head1 = head1->next;
                delete remove;
            }
        }
    }
    head1 = copy_head1;
    head2 = copy_head2;
}
```

**Пример 2 - Втори вариант, задача 3**

Решение 1:

```c++
template <typename T>
bool sublist(box<T> *l1, box<T> *l2)
{
    while(l2 != nullptr)
    {
        if(startsWith(l1, l2))
        {
            return true;
        }
        l2 = l2->next;
    }

    return false;
}
```


Решение 2:

```c++
template <typename T>
bool sublist(box<T>* L1, box<T>* L2) {
    box<T>* curr = L2;
    while (curr != nullptr) {
        box<T> *curr1 = L1;
        box<T> *curr2 = curr;
        while (curr1->data == curr->data) {
            if (curr1->next == nullptr) {
                return true;
            }
            if (curr2->next == nullptr) {
                break;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        curr = curr->next;
    }
    return false;
}
```


## Технически неточности

Решават се с писане на тестове:

* Функцията ми работи ли добре с невалидни входни данни?
* Функцията ми работи ли добре с празни входни данни(списък/стек/вектор без елемент)?
* Функцията ми работи ли добре, ако във входната структура от данни има 1/2/3 ... елемента?
* Функцията ми работи ли добре, ако резултатът е на първа/последна позиция в структурата от данни?
* Функцията ми работи ли добре за големи обеми от входни данни?


**За домашно!**

Решенията на задачите от тема 3 и тема 4 нямат написани тестове. Изберете си задача/и и напишете изчерпателно количество тестове.

Попълнете името си в таблицата за задачата, която сте си избрали и отворете [Pull Request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request) с написаните от вас тестове.

Ако имате проблем с работата с GitHub, или питайте за съдействие, или пратете решенията си по имейл.


| Задача                    | Студент                | Линк към Pull Request |
| ------------------------- | ---------------------- | --------------------- | 
| Tема 4, Задача 1          |                        |                       |
| Tема 4, Задача 2          |                        |                       |
| Tема 4, Задача 4          |                        |                       |
| Tема 4, Задача 5          |                        |                       |
| Tема 5, Задача 3          |                        |                       |
| Tема 5, Задача 5          |                        |                       |
| Tема 5, Задача 6          |                        |                       |
