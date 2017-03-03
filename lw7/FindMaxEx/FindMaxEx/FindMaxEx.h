#include <iostream>
#include <vector>

template < typename T, typename Less>

bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
    if (arr.size() == 0)
    {
        return false;
    }

    const T* maxElement = &arr[0];
    for (T arrElem : arr)
    {
        if (less(*maxElement, arr))
        {
            maxElement = arrElem;
        }
    }

    maxValue = *maxElement;

    return true;
}