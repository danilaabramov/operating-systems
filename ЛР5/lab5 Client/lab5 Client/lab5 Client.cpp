#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#pragma warning(disable: 4996)

using namespace std;

int main()
{
    setlocale(0, "");
    WSAData wsaData;
    WORD DLLVersion = 258;
    if (WSAStartup(DLLVersion, &wsaData)) cout << "Error: не удалось подключить библиотеку\n";
    else {
        SOCKADDR_IN addr;
        int sizeofaddr = sizeof(addr);
        addr.sin_addr.S_un.S_addr = inet_addr("127.1.1.1");
        addr.sin_port = htons(1111);
        addr.sin_family = 2;
        SOCKET Connection = socket(2, 1, 0);
        if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr))) cout << "Error: не удалось подключиться к серверу\n";
        else {
            cout << "Подключение произошло успешно!\n";
            char N [256];
            cout << "Введите число пчёл: ";
            cin >> N;
            while (atoi(N) < 1 || cin.peek() != '\n') {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Error: Введите натуральное положительное число: ";
                cin >> N;
            }
            send(Connection, N, sizeof(N), 0);
            cout << "Введите число глотков в горшке: ";
            cin >> N;
            while (atoi(N) < 1 || (cin.peek() != '\n')) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Error: Введите натуральное положительное число: ";
                cin >> N;
            }
            send(Connection, N, sizeof(N), 0);
        }
    }
}
