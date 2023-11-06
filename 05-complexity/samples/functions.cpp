#include <iostream>

int f1(int* arr, int size)
{
    if (size == 0)
    {
        return 0;
    }

    return arr[size / 2];
}

bool f2(int* arr, int size, int x)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == x)
        {
            return true;
        }
    }

    return false;
}

bool f3(int* arr, int left, int right, int x)
{
    if (left >= right)
    {
        return false;
    }

    int mid = (left + right) / 2;

    if (arr[mid] == x)
    {
        return true;
    }
    else if (arr[mid] < x)
    {
        return f3(arr, mid + 1, right, x);
    }
    
    return f3(arr, left, mid, x);
}

int f4(int n) {
    if (n <= 1) {
        return n;
    }
    return f4(n - 1) + f4(n - 2);
}

void f5(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            std::cout << i << " - " << j << std::endl;
        }
    }
}

int f6(int n)
{
    int result = 0;

    for (int i = 0; i < n; ++i)
    {
        result += i;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            result += i;
        }
    }

    result += 5;
    result *= 3;
    result -= 2;

    return result;
}

bool f7(int n)
{
	while (n > 1)
	{
		if (n % 2 == 1)
        {
			return false;
        }

		n /= 2;
	}

	return true;
}

void f8(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j += i)
        {
            std::cout << i << " - " << j << std::endl;
        }
    }
}

void f9(int* arr, int& size, int index)
{
    if (index >= size)
    {
        return;
    }

    for (int i = index; i < size - 1; ++i)
    {
        arr[index] = arr[index + 1];
    }

    --size;
}

void f10(int* arr, int size, int index)
{
    if (index >= size)
    {
        return;
    }

    std::swap(arr[index], arr[size - 1]);

    --size;
}
