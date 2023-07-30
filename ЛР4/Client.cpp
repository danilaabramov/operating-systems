#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <winsock2.h>
#include <iostream>
#include "conio.h"

using namespace std;

int main() {
	// загружаем WSAStartup
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSAData wsaData; // создаем структуру для загрузки
	WORD word = MAKEWORD(2, 1);
	if (WSAStartup(word, &wsaData) != 0) { // проверка на подключение библиотеки
		cout << "Error: ошибка подключения библиотеки\n";
		WSACleanup();
		return 0;
	}
	SOCKADDR_IN sockAddr; // получаем информацию об адресе сокета
	sockAddr.sin_addr.s_addr = inet_addr("127.1.1.1"); // адрес
	sockAddr.sin_port = htons(1111); // порт
	sockAddr.sin_family = AF_INET; // семейство протоколов
	SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0); // создаем сокет для соединения с сервером
	if (connect(Connection, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0) cout << "Error: Ошибка подключения\n";
	else {
		cout << "Подключение произошло успешно!\n";
		char str[15951];
	
		for (int i = 0; i < 15951; ++i) {
			char c;
			str[i] = getch();
			if (str[i] == '\r') cout << endl;
			if (str[i] == '\b') cout << "\b\ ";
			c = str[i];
			send(Connection, &c, 1, 0);
			cout << str[i];
		}
	}
	WSACleanup(); // деинициализируем библиотеки
	closesocket(Connection); // закрываем сокет
}