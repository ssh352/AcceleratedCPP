#ifndef MEDIANTEMPLATE_H
#define MEDIANTEMPLATE_H

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <mediantemplate.h>

using std::vector;
using std::domain_error;
using std::sort;



template <class T>
T median(std::vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;

    vec_sz size = v.size();
    if (size == 0)
        throw domain_error("median of an empty vector");

    sort( v.begin(), v.end() );

    vec_sz mid = size/2;

    return size % 2 == 0 ? (v[mid] + v[mid-1]) / 2 : v[mid];
}


#endif // MEDIANTEMPLATE_H
