#include <iostream>
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
    if (arr.empty())
    {
        return false;
    }

    const T* maxElement = &arr[0];
    for (T& arrElem : arr)
    {
        if (less(*maxElement, arrElem))
        {
            maxElement = &arrElem;
        }
    }

    maxValue = *maxElement;

    return true;
}
