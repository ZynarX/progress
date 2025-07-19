#include <iostream>
#include <string>
#include <optional>
#include <map>

class Item
{
private:
    std::string name;
    std::optional<std::string> description;
    std::optional<int> durability;
public:
    Item(std::string newName) : name(newName) {}
    Item(std::string newName, std::string newDescription) : name(newName), description(newDescription) {}
    Item(std::string newName, int newDurability) : name(newName), durability(newDurability) {}
    Item(std::string newName, std::string newDescription, int newDurability) : name(newName), description(newDescription), durability(newDurability) {}

    std::string get_name()
    {
        return this->name;
    }
    std::optional<std::string> get_description()
    {
        return this->description;
    }
    std::optional<int> get_durability()
    {
        return this->durability;
    }
};

std::optional<Item> GetItemById(std::map<int, Item>& inventory, int id);

int main()
{
    Item first("Coke");
    Item second("Laptoop", "A small computer device!");
    Item third("Wrench", 8);
    Item fourth("Glasses", "Vision glasses for eyes!", 10);

    std::map<int, Item> inventory = {
        {0, first},
        {1, second},
        {2, third},
        {3, fourth}
    };

    std::optional<Item> item = GetItemById(inventory, 2);

    if (item.has_value())
    {
        std::cout << "Item Name: " << item.value().get_name() << std::endl;

        if (item.value().get_description().has_value())
        {
            std::cout << "Item Description: " << item.value().get_description().value() << std::endl;
        }
        else
        {
            std::cout << "Item Description: Undefined" << std::endl;
        }

        if (item.value().get_durability().has_value())
        {
            std::cout << "Item Durability: " << item.value().get_durability().value() << std::endl;
        }
        else
        {
            std::cout << "Item Durability: Undefined" << std::endl;
        }
    }
    else
    {
        std::cout << "Item not found!\n";
    }

    return 0;
}

std::optional<Item> GetItemById(std::map<int, Item>& inventory, int id)
{
    for(auto& pair : inventory)
    {
        if (pair.first == id)
        {
            return pair.second;
        }
    }

    return std::nullopt;
}
