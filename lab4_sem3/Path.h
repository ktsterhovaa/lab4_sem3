#ifndef PATH_H
#define PATH_H

#include "DynamicArray.h"

template<typename T>
class Path
{
private:
    DynamicArray<int> distances;
    DynamicArray<T> path;
public:
    Path() = default;

    Path(DynamicArray<int>& distances_, DynamicArray<T>& path_)
    {
        distances = distances_;
        path = path_;
    }

    DynamicArray<int> GetDistances()
    {
        return distances;
    }

    DynamicArray<T> GetPath()
    {
        return path;
    }
};

#endif // PATH_H
