#include <iostream>

using namespace std;

template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag)
{
    iter += d;
}

template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag)
{
    if(d>=0)
    {
        while(d--)
        {
            ++iter;
        }
    }
    else
    {
        while(d++)
        {
            --iter;
        }
    }
}

template <typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::input_iterator_tag)
{
    if(d<0)
    {
        throw out_of_range("Negative  distance");
    }
    
    while(d--)
    {
        ++iter;
    }
}


template <typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
    doAdvance(iter, d, iterator_traits<IterT>::iterator_category());
}
