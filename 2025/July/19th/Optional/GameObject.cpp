#include <iostream>
#include <string>
#include <optional>

class GameObject{
private:
    std::optional<std::string> name;
public:
    GameObject() = default;
    GameObject(const std::string& newName) : name(newName) {}

    std::optional<std::string> get_name(){
        return this->name;
    }
};

int main()
{
    GameObject object;
    GameObject secondObject("Block");

    if (object.get_name() != std::nullopt)
    {
        std::cout << "Object No. 1: " << object.get_name().value() << std::endl;
    }
    else
    {
        std::cout << "Object No. 1: Unnamed" << std::endl;
    }

    if (secondObject.get_name() != std::nullopt)
    {
        std::cout << "Object No. 2: " << secondObject.get_name().value() << std::endl;
    }
    else
    {
        std::cout << "Object No. 2: Unnamed" << std::endl;
    }

    return 0;
}
