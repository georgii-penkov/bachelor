#include <iostream>

class ArrElement
{
    public: //just make members public instead of using setter/getter methods
    int m_value;
    ArrElement *m_next;
    bool is_last;
    ArrElement()
    {
        m_value = 0;
        m_next = nullptr;
        is_last = true;
    };
    //does not dynamically allocate (no new) -> default destructor good enough
    
};

class DynArray
{
    private:
    ArrElement *m_first;
    int m_length;
    public:
    ArrElement* operator[](int index)
    {
        ArrElement* ptr = m_first;
        for (int i = 0; i < index; ++i)
        {
            ptr = ptr->m_next;
            if (i < index-1 and ptr->is_last)
            {
                std::cout << "Tried to iterate off end of array" << std::endl;
                return ptr;
            };
        };
            
        return ptr;
    };

    DynArray(int size)
    {
        m_first = new ArrElement();
        m_length = 1;
        for (int i = 0; i < size-1; ++i)
        {
            ++m_length;
            ((*this)[i])->m_next = new ArrElement();
            ((*this)[i])->is_last = false;
  
        };
        ((*this)[m_length-1])->is_last = true;
    };
    ~DynArray()
    {
        for (int i = m_length-1; i > 0; --i)
            {
                delete ((*this)[i])->m_next;
            };
        delete m_first;
    };

    void Set(int pos, int value)
    {
        (*this)[pos-1]->m_value = value;
    };

    int Get(int pos)
    {
        return ((*this)[pos-1])->m_value;
    };

    void Extend(int additional_entries)
    {
        int old_length = m_length;
        ((*this)[m_length-1])->is_last = false;
        for (int i = old_length-1; i < old_length + additional_entries-1; ++i)
        {
            ++m_length;
            ((*this)[i])->m_next = new ArrElement();
            ((*this)[i])->is_last = false;
        };
    };

    int Length()
    {
        return(m_length);
    }
    void Resize()
    {
        //remove last n elements from array. DRY would be better to have removelastnelements method, and have the destructor call it with entire n=length
    };
};



int main()
{
    DynArray arr(5);
    for (int i = 1; i <= 5; ++i)
    {
        arr.Set(i, i);
    };
    
    for (int i = 1; i <= 5; ++i)
    {
        std::cout << arr.Get(i) << std::endl;
    };
    arr.Extend(3);
    std::cout << arr.Get(7) << std::endl;
    std::cout << "length  " << arr.Length() << std::endl;
    return 0;
}