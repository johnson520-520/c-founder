#include <iostream>
#include "Executor.hpp"

int main()
{
    Executor executor;

    std::string commands = "FMRMLMF";

    executor.executeCommands(commands);

    std::cout << "Final Position: (" << executor.getX() << ", " << executor.getY() << ")\n";
    std::cout << "Final Heading: " << static_cast<char>(executor.getHeading()) << std::endl;

    return 0;
}
