#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>

using namespace std::chrono_literals;
#define sleep_for(x) std::this_thread::sleep_for(x) 

class Person
{
public:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string email;
};

class AddressBook
{
private:
    std::fstream file;
    std::string phonebookName;
    std::string filePath;
    int choice;
    int num_of_lines = 0;
public:
    bool Check(std::string filepath)
    {
        std::ifstream f(filepath);

        return f.good();
    }

    void AddressBookFirstMenu(std::string filepath)
    {
        phonebookName = filepath;
        filepath += ".ab";
        filePath = filepath;
        if(Check(filepath))
        {
            std::fstream _file(filepath);
            std::cout << "Logged in to a phone book of path: " << filepath << std::endl;
            _file.close();
        }
        else
        {
            std::ofstream _file(filepath);
            std::cout << "Created new phone book of path: " << filepath << std::endl;
            _file.close();
        }

        file.open(filepath);

        sleep_for(800ms);
        AddressBookMenu();
    }

    void AddressBookMenu()
    {
        system("clear");
        std::cout << "Hello from your phone book of name \"" << phonebookName << "\"!\n";
        std::cout << "1. Print data from my phone book.\n";
        std::cout << "2. Add data to my phone book.\n";
        std::cout << "3. Delete data from my phone book.\n";
        std::cout << "4. Exit.\nChoice: ";
        std::cin >> choice;
        num_of_lines = 0;
        std::string line;
        file.open(filePath);
        while(std::getline(file, line))
        {
            num_of_lines++;
        }
        file.close();

        switch(choice)
        {
        case 1:
            PrintData();
            break;
        case 2:
            AddData();
            break;
        case 3:
            DeleteData();
            break;
        case 4:
            return;
            break;
        default:
            AddressBookMenu();
            break;
        }
    }

    void DeleteData()
    {
        file.open(filePath);
        std::string line;
        std::vector<std::string> lines;
        std::cout << "First Name          Last Name          Number          E-mail\n";
        for(int i = 0; i < num_of_lines; i++)
        {
            std::getline(file, line);
            lines.push_back(line);
            std::cout << i+1 << ". " << line << "\n";
        }
        line = "";
        int lineDel;
        std::cout << "Enter Line Number: ";
        std::cin >> lineDel;
        
        std::cout << lines.size() << std::endl;

        std::remove(filePath.c_str());

        std::ofstream fileD(filePath);
        lineDel--;
        for(int i = 0; i < lines.size(); i++)
        {
            if(i != lineDel)
                fileD << lines[i] << std::endl;
        }

        fileD.close();

        AddressBookMenu();
    }

    void AddData()
    {
        file.open(filePath, std::fstream::app);
        Person person;
        std::cout << "Enter First Name: ";
        std::cin >> person.firstName;
        std::cout << "Enter Last Name: ";
        std::cin >> person.lastName;
        std::cout << "Enter Phone Number: ";
        std::cin >> person.phoneNumber;
        std::cout << "Enter E-mail: ";
        std::cin >> person.email;

        file << person.firstName << " " << person.lastName << " " << person.phoneNumber << " " << person.email << std::endl;
        sleep_for(2s);
        file.close();
        AddressBookMenu();
    }

    void PrintData()
    {
        file.close();
        file.open(filePath);
        std::string line;
        std::cout << "First Name | Last Name | Number | E-mail\n";
        for(int i = 0; i < num_of_lines; i++)
        {
            std::getline(file, line);
            std::cout << line << "\n";
        }
        std::cout << std::endl << "(PRESS ENTER TO CONTINUE)";
        std::cin.get();
        std::cin.get();
        file.close();
        AddressBookMenu();
    }
};
