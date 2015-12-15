#include <iostream>
#include <cstdio>
#include <cstddef>
#include "sha_256.cpp"
#include <string>
#include "registr.cpp"

using namespace std;

int main()
{
    SHA256* YourName = new SHA256();
    string name;
    string password;

    cout << "name" << endl;
    cin >> name;
    cout << "password" << endl;
    cin >> password;
    identification man;
    man.login = name;
    man.password = password;
    man.login = YourName->hash(name);
    man.password = YourName->hash(password);

    cout << "1 - registration" << endl;
    cout << "2 - autorization" << endl;
    cout << "other - exit" << endl;
    int number;
    cin >> number;
    //cout << man.autorization() << endl;
    switch (number)
    {
        case 1:
            {
            if (man.registration() != 0) cout << "write different login" << endl;
            else cout << "vnesen" << endl;
            main();
            break;
            }
        case 2:
            {
            if (man.autorization() == 1) cout << "error login or password" << endl;
            else
                cout << "Here" << endl;
            main();
            break;
            }
        case 3:
            return 0;
            break;
    }
    return 0;
}
//printf("%s\n", digest.c_str());
