#include<iostream>
using namespace std;

int main()
{
    char message[100], ch;
    int i, key;

    std::cout << "Geef een tekst:  ";
    std::cin.getline(message, 100);
    std::cout << "Geef rotatie:  ";
    std::cin >> key;

    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];

        if(ch >= 'a' && ch <= 'z'){
            ch = ch + key;

            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }

            message[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;

            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }

            message[i] = ch;
        }
    }

    std::cout << "Ceasarcode: " << message << "\n";

    return 0;
}