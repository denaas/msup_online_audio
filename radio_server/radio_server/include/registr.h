#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class identification
{
public:
    string login;
    string password;

    bool registration()
    {
        bool flag = 0;
        ifstream client ("client.txt");
        string log;
        string pas;
        while (client >> log >> pas)
        {
            if (login == log)
            {
                flag = 1; // Ошибка - данный логин уже присутствует.
            }
        }
        if (flag == 0)
        {
            ofstream client ("client.txt", ios::app);
            client << endl << login << ' ' << password;
            client.close();
        }
        return flag;
    }

    bool autorization()
    {
        bool flag = 1;
        ifstream client ("client.txt");
        string log;
        string pas;
        while (client >> log >> pas)
        {
            if ((login == log) && (password == pas) )
            {
                flag = 0; // Логин и пароль совпали.
            }
        }
        client.close();
        return flag;
    }
};
