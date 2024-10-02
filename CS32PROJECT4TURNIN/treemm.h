#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            m_valid = false;
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
            return *m_innerIterator;
        }

        bool is_valid() const
        {
            return m_valid;
        }

        void advance()
        {
            if(!is_valid())
                throw 2;
            m_innerIterator++;
            if(m_innerIterator == m_vector.end())
                m_valid = false;
        }

      private:
        typename std::vector<ValueType>::iterator m_innerIterator;
        std::vector<ValueType> m_vector;
        bool m_valid;
    };
    

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        delete m_root;
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if(m_root == nullptr){
            m_root = new Node(key);
            m_root->container.push_back(value);
            return;
        }
        Node* it = m_root;
        while(it != nullptr){
            if(key < it->key){
                if(it->left == nullptr)
                    it->left = new Node(key);
                it = it->left;
            }
            else if(it->key < key){
                if(it->right == nullptr)
                    it->right = new Node(key);
                it = it->right;
            }
            else
                break;
        }
        it->container.push_back(value);
    }

    Iterator find(const KeyType& key) const
    {
        if(m_root == nullptr)
            return Iterator();
        Node* it = m_root;
        while(it != nullptr){
            if(key < it->key)
                it = it->left;
            else if(it->key < key)
                it = it->right;
            else
                return Iterator(it->container);
        }
        return Iterator();
    }

  private:
    struct Node{
        Node(KeyType k){
            key = k;
            left = nullptr;
            right = nullptr;
        }
        ~Node(){
            delete left;
            delete right;
        }
        Node* left;
        Node* right;
        KeyType key;
        std::vector<ValueType> container;
    };
    Node* m_root;
};

#endif // TREEMULTIMAP_INCLUDED
