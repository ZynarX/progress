#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

/*EXCEPTIONS*/

class FileError : public std::exception
{
private:
    std::string message;
public:
    FileError(const std::string& msg) : message(msg) {}
    FileError(const char* msg) : message(std::string(msg)) {}

    const char* what() const noexcept override
    {
        return this->message.c_str();
    }
};

class ParseError : public std::exception
{
private:
    std::string message;
public:
    ParseError(const std::string& msg) : message(msg) {}
    ParseError(const char* msg) : message(std::string(msg)) {}

    const char* what() const noexcept override
    {
        return this->message.c_str();
    }
};

class ItemError : public std::exception
{
private:
    std::string message;
public:
    ItemError(const std::string& msg) : message(msg) {}
    ItemError(const char* msg) : message(std::string(msg)) {}

    const char* what() const noexcept override
    {
        return this->message.c_str();
    }
};

/*CLASSES*/

class Item
{
protected:
    std::string name;
    int quantity;
public:
    virtual std::string GetDetails() const = 0;
    virtual std::string GetType() const = 0;

    std::string GetName()
    {
        return this->name;
    }
    int GetQuantity()
    {
        return this->quantity;
    }

    virtual ~Item() = default;
};

class Book : public Item
{
public:
    Book(const std::string& Name, const int& Quantity)
    {
        this->name = Name;
        this->quantity = Quantity;
    }

    std::string GetDetails() const override
    {
        std::string details = "Book: " + this->name + "\nQty: " + std::to_string(this->quantity);

        return details;
    }
    std::string GetType() const override
    {
        return "Book";
    }
};

class Electronics : public Item
{
public:
    Electronics(const std::string& Name, const int& Quantity)
    {
        this->name = Name;
        this->quantity = Quantity;
    }

    std::string GetDetails() const override
    {
        std::string details = "Electronics: " + this->name + "\nQty: " + std::to_string(this->quantity);

        return details;
    }
    std::string GetType() const override
    {
        return "Electronic";
    }
};

class Inventory
{
private:
    std::vector<Item*> inventory;
protected:
public:
    Inventory() = default;
    void Add(Item* item)
    {
        this->inventory.push_back(item);
    }
    void Remove(const std::string& name)
    {
        bool is_removed = false;

        for(size_t i = 0; i < this->inventory.size(); i++)
        {
            if(this->inventory[i]->GetName() == name)
            {
                delete this->inventory[i];

                this->inventory.erase(this->inventory.begin() + i);
                is_removed = true;
                break;
            }
        }

        if (!is_removed)
        {
            throw ItemError("Item Not Found To Remove!");
        }
    }
    void DisplayItems()
    {
        std::cout << std::setw(15) << std::left << "Type"
                  << std::setw(20) << std::left << "Name"
                  << std::setw(10) << std::left << "Quantity\n";
        
        for(Item* item : this->inventory)
        {
            std::cout << std::setw(15) << std::left << item->GetType()
                      << std::setw(20) << std::left << item->GetName()
                      << std::setw(10) << std::left << item->GetQuantity()
                      << '\n';
        }
    }
    void Clear()
    {
        for(size_t i = 0; i < this->inventory.size(); i++)
        {
            delete this->inventory[i];
        }

        this->inventory.clear();
    }
    std::vector<Item*> GetInventory()
    {
        return this->inventory;
    }

    ~Inventory() = default;
};

/*FUNCTIONS DECLARATION*/

void HandleAdd(Inventory& inventory);
void HandleRemove(Inventory& Inventory);
void SaveToFile(const std::string& filename, Inventory& inventory);
void LoadFromFile(const std::string& filename, Inventory& inventory);

/*MAIN*/

int main()
{
    try
    {
        Inventory inventory;
        std::string filename = "data.txt";
        LoadFromFile(filename, inventory); // file already made so no error here
        
        char choice;

        do
        {
            do
            {
                std::cout << "--------------- Inventory Management ---------------\n";
                std::cout << "1. Add Item\n2. Remove Item\n3. Display Items\n4. Exit\nChoose an option: ";
                std::cin >> choice;

                if (choice != '1' && choice != '2' && choice != '3' && choice != '4')
                {
                    choice = '\0';
                }
            } while (choice == '\0');

            switch(choice)
            {
                case '1':
                    HandleAdd(inventory);
                    break;
                case '2':
                    HandleRemove(inventory);
                    break;
                case '3':
                    inventory.DisplayItems();
                    break;
                case '4':
                    break;
                default:
                    std::cout << "Invalid Input!\n";
                    break;
            }
            
        } while (choice != '4');
        

        SaveToFile(filename, inventory);
    }
    catch(const FileError& e)
    {
        std::cerr << "File Error: " << e.what() << '\n';
    }
    
    return 0;
}

/*FUNCTIONS DEFINITION*/

void HandleAdd(Inventory& inventory)
{
    char type = '\0';

    std::cout << "----- Item Addition -----\n";

    do
    {
        std::cout << "Item Type (1. Book, 2. Electronics): ";
        std::cin >> type;

        if (type != '1' && type != '2')
        {
            type = '\0';
        }
    } while (type == '\0');

    Item* item = nullptr;
    
    std::string name = "";
    int quantity = -1;

    do
    {
        std::cout << "Item Name (20 Characters Max): ";
        std::getline(std::cin >> std::ws, name);
    } while (name.empty());

    do
    {
        try
        {
            std::cout << "Item Quantity: ";
            std::cin >> quantity;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    } while (quantity < 0);
    
    if (type == '1')
    {
        item = new Book(name, quantity);
    }
    else if (type == '2')
    {
        item = new Electronics(name, quantity);
    }

    inventory.Add(item);
}
void HandleRemove(Inventory& inventory)
{
    std::string name = "";

    std::cout << "----- Item Removing -----\n";

    do
    {
        std::cout << "Item Name: ";
        std::getline(std::cin >> std::ws, name);
    } while (name.empty());
    
    try
    {
        inventory.Remove(name);
    }
    catch(const ItemError& e)
    {
        std::cerr << "Item Error: " << e.what() << '\n';
    }
    
}

void SaveToFile(const std::string& filename, Inventory& inventory)
{
    std::ofstream outFile(filename);

    if(!outFile)
    {
        throw FileError("Couldn't open file to save!");
    }

    std::vector<Item*> inventoryItems = inventory.GetInventory();

    for (Item* item : inventoryItems)
    {
        outFile << item->GetType()
                << ',' << item->GetName()
                << ',' << item->GetQuantity()
                << '\n';
    }

    inventory.Clear();
}
void LoadFromFile(const std::string& filename, Inventory& inventory)
{
    std::ifstream inFile(filename);

    if(!inFile)
    {
        throw FileError("Couldn't open file to load!");
    }
    
    try
    {
        std::string line;

        while(std::getline(inFile, line))
        {
            Item* item;

            std::istringstream iss(line);

            std::string type;
            std::string name;
            int quantity;

            std::getline(iss, type, ',');
            std::getline(iss, name, ',');

            if(!(iss >> quantity))
            {
                throw ParseError("Failed to set quantity!");
            }

            if (type == "Book")
            {
                item = new Book(name, quantity);
            }
            else if (type == "Electronics")
            {
                item = new Electronics(name, quantity);
            }

            inventory.Add(item);
        }
    }
    catch(const ParseError& e)
    {
        std::cerr << "Parse Error: " << e.what() << '\n';
    }
}
