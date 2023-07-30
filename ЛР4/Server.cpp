#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <winsock2.h>
#include <iostream>

using namespace std;

int main() {
	// загружаем WSAStartup
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSAData wsaData; //создаем структуру для загрузки
	WORD word = MAKEWORD(2, 1);
	if (WSAStartup(word, &wsaData) != 0) { //проверка на подключение библиотеки
		cout << "Error: ошибка подключения библиотеки\n";
		WSACleanup();
		return 0;
	}
	SOCKADDR_IN sockAddr;//получаем информацию об адресе сокета
	int sizeOfSockAddr = sizeof(sockAddr); //размер
	sockAddr.sin_addr.s_addr = inet_addr("127.1.1.1"); //адрес
	sockAddr.sin_port = htons(1111); //порт
	sockAddr.sin_family = AF_INET; //семейство протоколов
	SOCKET soketListen = socket(AF_INET, SOCK_STREAM, 0);//сокет для прослушивания порта
	bind(soketListen, (SOCKADDR*)&sockAddr, sizeof(sockAddr));//функция для привязки сокета
	listen(soketListen, SOMAXCONN);//прослушивание, сколько запросов ожидается
	SOCKET Connection = accept(soketListen, (SOCKADDR*)&sockAddr, &sizeOfSockAddr); // подключается клиент
	if (Connection == 0)  cout << "Error: Ошибка подключения\n"; //не смогли подключиться
	else {
		cout << "Клиент подключен!\n";
		for (int i = 0; i < 15951; ++i) {
			char c;
			if (recv(Connection, &c, 1, 0) == -1) break;
			if (c == '\r') cout << endl;
			if (c == '\b') cout << "\b\ ";
			cout << c;	
		}
	}
	WSACleanup(); //деинициализируем библиотеки
	closesocket(Connection); //закрываем сокет
	closesocket(soketListen); //закрываем сокет
}