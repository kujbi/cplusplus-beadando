#ifndef MMAPVIEW_H
#define MMAPVIEW_H

#include <vector>
#include <map>

template <typename Key,typename Value>
class multimap_view
{
    std::vector<std::map<Key,Value>*> multimap; 
public:
//add
    void add(std::map<Key, Value>& d )
    {
        multimap.push_back(&d);

    }
//remove
    void remove(const std::map<Key, Value>& d )
    {
       std::vector<std::map<Key,Value>*> cmultimap;
       for(const auto elem: multimap)
        {
            if(elem!=&d)
            {
            cmultimap.push_back(elem);
            }
        }
        multimap=cmultimap;
    
    }
//count
    unsigned int count(Key k) const 
    {
        unsigned int counter = 0;
        for(const auto elem : multimap)
        {
           counter+=elem->count(k);
        }
        return counter;
    }

//erase (Key)
    unsigned int erase(Key k)
    {
        unsigned int counter = 0;
        for(const auto elem : multimap)
        {
           counter+=elem->erase(k);
        }
        return counter;
    }
    //Compare
    template <class Compare>
	operator std::multimap< Key, Value, Compare> const () 
    {
        std::multimap< Key, Value, Compare > mmap;

        for( auto elem : multimap)
            {
                for ( typename std::map< Key, Value >::const_iterator it = (elem)->cbegin(); it != (elem)->cend(); it++ )
                {
                    mmap.insert( std::pair< Key, Value > (it->first, it->second) );
                }
            }
        return mmap;
    }
};
#endif // MMAPVIEW_H