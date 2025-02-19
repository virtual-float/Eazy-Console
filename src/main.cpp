#include <iostream>
#include "command.hxx"
#include "fileMan.hxx"


// For testing purposes
eazy::CommandResult print(const eazy::CommandArgs& arguments) {
    for (const auto& arg : arguments) {
        std::cout << "# " << arg << std::endl;
    }

    return eazy::NO_RESULT;
}

int main()
{
    // Command object
    eazy::Command cmd("print", print, {"A", "r", "e", "k"});
    
    // Invoking the object's handle
    cmd();

    // tests
    // eazy::fileManNode test = eazy::fileManNode("test.txt");
    // std::cout << std::endl << test.getPath() << std::endl;
    // std::cout << test.writeBlank("ahaw");
    // // std::cout << test.writeBlank("teswadauwut");

    // std::cout << std::endl << test.readWhole();
    // test.append("test");
    // test.append("test2");


    // test.append("-------");
    // test.append(";3");
    // test.keepAlive(true);
    // test.append("zoahazo");

    return 0;
}