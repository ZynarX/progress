#include <iostream>
#include <fstream>
#include <memory>
#include <string>

class Logger
{
private:
    std::ofstream fileoutput;
public:
    std::string filepath;
    Logger(std::string filepath)
    {
        this->filepath = filepath;

        fileoutput.open(this->filepath);

        if(!fileoutput.is_open())
        {
            fileoutput.open(filepath);
        }
    }
    ~Logger()
    {
        if(this->fileoutput.is_open())
        {
            this->fileoutput.close();
        }
    }
    void Log(std::string message)
    {
        if(this->fileoutput.is_open())
        {
            this->fileoutput << message << '\n';
        }
    }
};

auto deleter = [](Logger* logger){
    delete logger;
};

int main()
{
    std::string filepath = "";

    do
    {
        std::cout << "Enter filepath: ";
        std::getline(std::cin >> std::ws, filepath);
    } while (filepath.empty());
    

    std::unique_ptr<Logger, decltype(deleter)> file(new Logger(filepath), deleter);
    
    std::string message;

    do
    {
        std::cout << "Enter message: ";
        std::getline(std::cin >> std::ws, message);
    } while (message.empty());
    
    
    file->Log(message);

    return 0;
}
