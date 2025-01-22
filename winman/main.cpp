/**
 * ======================================= BW =======================================
 *   BetterWindows - a solution to make Windows better
 * 
 * (c) 2024 Gorciu
 */

#ifdef __linux__
#error Building BetterWindows on Linux is kind of useless
#endif 

#ifndef _WIN32
#error Building BetterWindows on AurorOS/Linux/MacOS is kind of useless
#endif 

#include <iostream>
#include <windows.h>
#include <vector>

void print(std::string something) {
    std::cout << something;
}

void println(std::string something) {
    std::cout << something << std::endl;
}

void printnl() {
    println("\n");
}

void setConsoleColor(int fg = 0x0F, int bg = 0) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | fg)); 
}

std::string read(std::string prefix) {
    std::cout << prefix;
    std::string result;
    std::getline(std::cin, result);
    return result;
}

void viewHelp() {
    println("Usage: winman [args]");
    printnl();
    println(" -I <package>     Install package");
    println(" -U               Update and upgrade all packages");
    println(" -R <package>     Remove package");
    println(" -S <package>     Search for package");
    println(" -V               View installed packages");
    println(" -H               View this help");
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    std::vector<std::string> packagesToInstall;
    std::vector<std::string> packagesToRemove;
    std::vector<std::string> packagesToSearch;
    bool shouldUpdate = false;
    bool shouldViewHelp = false;
    if (args.size() == 1) {
        viewHelp();
        return 0;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "-I" && i + 1 < args.size()) {
            packagesToInstall.push_back(args[++i]);
        } else if (args[i] == "-U") {
            shouldUpdate = true;
        } else if (args[i] == "-R" && i + 1 < args.size()) {
            packagesToRemove.push_back(args[++i]);
        } else if (args[i] == "-S" && i + 1 < args.size()) {
            packagesToSearch.push_back(args[++i]);
        } else if (args[i] == "-V") {
            setConsoleColor(1);
            println("winman: this feature is not implemented yet.");
            setConsoleColor(7);
        } else if (args[i] == "-H") {
            shouldViewHelp = true;
        } else {
            println("winman: unknown argument: " + args[i]);
            viewHelp();
            return 1;
        }
    }

    if (shouldViewHelp) {
        viewHelp();
    }

    return 0; // by default
}