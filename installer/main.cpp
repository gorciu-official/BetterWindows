/**
 * ======================================= BW =======================================
 *   BetterWindows - a solution to make Windows better
 * 
 * (c) 2024 Gorciu
 */

// ACT 1: PREPROCESSOR

#ifdef __linux__
#error Building BetterWindows on Linux is kind of useless
#endif 

#ifndef _WIN32
#error Building BetterWindows on AurorOS/Linux/MacOS is kind of useless
#endif 

#include <iostream>
#include <fstream>
#include <windows.h>

// ACT 2: INTERNALS

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

void restartTerminal() {
    setConsoleColor();
    system("cls");
}

std::string read(std::string prefix) {
    std::cout << prefix;
    std::string result;
    std::getline(std::cin, result);
    return result;
}

// ACT 3: INSTALLER

bool downloadFile(const std::string &url, const std::string &path) {
    std::string command = "curl -s -L " + url + " -o " + path;
    return system(command.c_str()) == 0;
}

bool verifyChecksum(const std::string &filePath, const std::string &expectedChecksum) {
    std::string command = "certutil -hashfile " + filePath + " SHA256 | findstr " + expectedChecksum;
    return system(command.c_str()) == 0;
}

int installBetterWindows() {
    println("Adding BetterWindows to the PATH variable...");
    _putenv_s("Path", (std::getenv("Path") + std::string(";C:\\BetterWindows")).c_str());

    println("Downloading `winman` executable...");
    if (!downloadFile("https://raw.githubusercontent.com/TheBetterWindows/BetterWindows/refs/heads/main/online-content/winman.binary.exe", "C:\\BetterWindows\\temp\\winman.exe")) {
        MessageBoxA(NULL, "Failed to download winman executable.", "Error", MB_OK | MB_ICONERROR);
        return 6;
    }

    println("Checking checksum...");
    std::string expectedChecksum;
    if (downloadFile("https://raw.githubusercontent.com/TheBetterWindows/BetterWindows/refs/heads/main/online-content/winman.checksum-sha256.txt", "C:\\BetterWindows\\temp\\expected_checksum.txt")) {
        std::ifstream checksumFile("C:\\BetterWindows\\temp\\expected_checksum.txt");
        std::getline(checksumFile, expectedChecksum);
        checksumFile.close();
        if (!verifyChecksum("C:\\BetterWindows\\temp\\winman.exe", expectedChecksum)) {
            MessageBoxA(NULL, "Checksum is invalid. Installation aborted.", "Checksum Error", MB_OK | MB_ICONERROR);
            return 7;
        }
    } else {
        MessageBoxA(NULL, "Failed to download checksum.", "Error", MB_OK | MB_ICONERROR);
        return 8;
    }

    println("Copying `winman` to the correct location...");
    system("copy C:\\BetterWindows\\temp\\winman.exe C:\\BetterWindows\\winman.exe > nul");

    println("Installing required packages...");
    system("C:\\BetterWindows\\winman.exe -I base");

    println("Adding userinit binary...");
    if (!downloadFile("https://raw.githubusercontent.com/TheBetterWindows/BetterWindows/refs/heads/main/online-content/userinit.binary.exe", "C:\\BetterWindows\\userinit.exe")) {
        MessageBoxA(NULL, "Failed to download userinit binary.", "Error", MB_OK | MB_ICONERROR);
        return 9;
    }

    println("Registering userinit binary...");
    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\" /v \"Userinit\" /t REG_SZ /d \"C:\\\\BetterWindows\\userinit.exe,C:\\\\Windows\\system32\\userinit.exe,\" /f > nul");

    std::string restart = read("Do you want to restart to apply the changes? (y - restart now / n - restart later): ");
    if (restart == "y" || restart == "Y") {
        system("shutdown /r /t 0");
    } else {
        println("BetterWindows needs to restart later to apply changes.");
        Sleep(5000);
        return 0;
    }
    return 0;
}

// ACT 4: FRONT OF INSTALLER

int main() {
    while (true) {
        restartTerminal();
        setConsoleColor(0x0f, 1);
        println("BetterWindows - a solution to make Windows better, without need for reinstall");
        setConsoleColor();
        printnl();
        println("Windows sucks these days... There are actually people who will use it.");
        println("You probably don't want to switch to a different operating system, but you want");
        println("to make it a little better. If that describes you - go and use my project.");
        printnl();
        setConsoleColor(8);
        print("1) ");
        setConsoleColor();
        println("Install BetterWindows");
        setConsoleColor(8);
        print("2) ");
        setConsoleColor();
        println("Quit from this installer");

        std::string sel = read("# ");
        if (sel == "1") {
            system("md C:\\BetterWindows\\temp\\installer");
            system("curl -s -L https://raw.githubusercontent.com/TheBetterWindows/BetterWindows/refs/heads/main/online-content/RemoveBloatware.ps1 -o C:\\BetterWindows\\temp\\installer\\bloatwareremover.ps1");
            system("C:\\BetterWindows\\temp\\installer\\bloatwareremover.ps1");
            return installBetterWindows();
            break;
        } else if (sel == "2") {
            break;
        } else {
            MessageBoxExA(NULL, "The option that you selected is invalid.", "Invalid option", MB_OK | MB_ICONINFORMATION, 0);
        }
    }
    return 0;
}