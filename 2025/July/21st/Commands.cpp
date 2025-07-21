#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>
#include <algorithm>

class Command {
public:
    Command() {}
    inline virtual void execute() = 0;
};

class MoveCommand : public Command {
public:
    inline void execute() override {
        std::cout << "Moved!\n";
    }
};

class AttackCommand : public Command {
public:
    inline void execute() override {
        std::cout << "Attacked!\n";
    }
};

class DefendCommand : public Command {
public:
    inline void execute() override {
        std::cout << "Defended!\n";
    }
};

int main()
{
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;
    std::vector<std::string> loc = {"move", "attack", "defend", "move"};
    std::map<std::string, short> stats;

    commands["move"] = std::make_unique<MoveCommand>();
    commands["attack"] = std::make_unique<AttackCommand>();
    commands["defend"] = std::make_unique<DefendCommand>();

    for(std::string& cmd : loc)
    {
        if(commands.count(cmd))
        {
            commands[cmd]->execute();
            stats[cmd]++;
        }
    }

    std::for_each(stats.begin(), stats.end(), [](auto& pair){
        std::cout << "Command: \"" << pair.first << "\" executed " << pair.second << " times!\n";
    });

    return 0;
}
