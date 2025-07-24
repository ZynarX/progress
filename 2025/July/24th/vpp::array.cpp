#include <iostream>
#include <vector>
#include <functional>

namespace vpp
{
    template <typename T>
    class array
    {
    private:
        std::vector<T> elements;
        size_t size;
    public:
        void insert(T element)
        {
            this->elements.push_back(element);
            this->size++;
        }
        bool remove(T element)
        {
            size_t index = -1;

            for(size_t i = 0; i < this->elements.size(); i++)
            {
                if(element == this->elements[i])
                {
                    index = i;
                }
            }

            if(index != -1)
            {
                this->elements.erase(this->elements.begin() + index);

                return true;
            }
            else
            {
                return false;
            }
        }
        bool remove(size_t index)
        {
            if(index < this->elements.size())
            {
                this->elements.erase(this->elements.begin() + index);

                return true;
            }
            else
            {
                return false;
            }
        }

        void foreach(void func(T element, size_t index))
        {
            for(size_t i = 0; i < this->elements.size(); i++)
            {
                func(this->elements[i], i);
            }
        }
    };
}

int main()
{
    vpp::array<int> array;
    array.insert(10);
    bool res = array.remove((int)10);

    if (res)
    {
        std::cout << "Removed 10\n";
    }
    else
    {
        std::cout << "Didn't remove 10\n";
    }

    array.insert(10);
    array.insert(20);
    array.insert(30);

    array.foreach([](int element, size_t index){
        std::cout << element << " at index " << index << std::endl;
    });
}
