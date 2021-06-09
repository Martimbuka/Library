#pragma once
#include <iostream>
#include "String.hpp"
#include "CommandLine.hpp"
#include "State.hpp"
#include "LibraryCommands.hpp"
#include "Administrator.hpp"
#include "Vector.hpp"
#include "vector_strings.hpp"

using namespace library;

class Menu {
private:
    library::String command;
    library::String file_name;
    bool logged;

    void choice();
 
public:
    Menu();
};