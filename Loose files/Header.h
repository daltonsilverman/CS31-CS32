//
//  Header.h
//  PnetPhlixV2
//
//  Created by Dalton Silverman on 3/16/23.
//

#ifndef Header_h
#define Header_h
#include <vector>

#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            
        }
        Iterator(std::vector<ValueType> v)
        {
            m_vector = v;
            m_innerIterator = m_vector.begin();
            if(m_innerIterator == m_vector.end())
                m_valid = false;
            else
                m_valid = true;
        }

        ValueType& get_value() const
        {
            throw 1;  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            return false;  // Replace this line with correct code.
        }

        void advance()
        {
            // Replace this line with correct code.
        }

      private:
    };

    TreeMultimap()
    {
        // Replace this line with correct code.
    }

    ~TreeMultimap()
    {
        // Replace this line with correct code.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        // Replace this line with correct code.
    }

    Iterator find(const KeyType& key) const
    {
        return Iterator();  // Replace this line with correct code.
    }

  private:
};

#endif // TREEMULTIMAP_INCLUDED


#endif /* Header_h */
