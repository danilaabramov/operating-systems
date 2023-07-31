#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#pragma warning(disable: 4996)
#include <mutex>
#include <chrono>
#include <thread>

using namespace std;

int barrel_fullness = 0;
bool WinnieThePooh_sleep = true;
bool Pyatochek_sleep = true;
bool WinnieThePooh_sleep_got_enough_sleep = false;
bool Pyatochek_sleep_got_enough_sleep = false;
mutex mtx;
void Extraction(int i, int H);
void Eating();
void EatingPig();

int main()
{
    srand(time(0));
    setlocale(0, "");
    WSAData wsaData; // ссылка на структуру wsaData
    WORD word = 258; // запрашиваемая версия библиотеки winsock
    if (WSAStartup(word, &wsaData)) { // если метод не вернёт 0 то библиотека загрузилась неудачно
        cout << "Error: не удалось подключить библиотеку\n";
        return 0;
    }
    SOCKADDR_IN sockAddr;
    int sizeofaddr = sizeof(sockAddr);
    // заполняем информацию об адресе сокета
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127.1.1.1"); // IP
    sockAddr.sin_port = htons(1111); // порт
    sockAddr.sin_family = 2; // семейство интернет протоколов
    SOCKET socketListen = socket(2, 1, 0); // создаем сокет sListen которому присваиваем результат выполнения функции socket
    bind(socketListen, (SOCKADDR*)&sockAddr, sizeof(sockAddr)); // привязываем адрес сокета; (SOCKADDR*)&addr - указатель на структуру sockaddr
    listen(socketListen, 0x7ffffff); // прослушивание порта в ожидании соединения со стороны клиента;
    SOCKET newConnection; // объявляем новый сокет для удерживания соединения с клиентом
    newConnection = accept(socketListen, (SOCKADDR*)&sockAddr, &sizeofaddr); // функция accept возращает указатель на новый сокет который можно использовать для общения с клиентом
    if (!newConnection) cout << "Error: не удалось подключиться\n";
    else {
        cout << "Пчёлы подключились!\n";
        char N[256];
        recv(newConnection, N, sizeof(N), 0);
        int n = atoi(N);
        recv(newConnection, N, sizeof(N), 0);
        int H = atoi(N);
        thread* bees = new thread[n];
        thread WinnieThePooh = thread(Eating);
        thread Pyatochek = thread(EatingPig);
        for (int i = 0; i - n; ++i) bees[i] = thread(Extraction, i, H);
        for (int i = 0; i - n; ++i) bees[i].join();
        WinnieThePooh.join();
        Pyatochek.join();
    }
    return 0;
}

void Extraction(int i, int H) {
    while (1) {
        this_thread::sleep_for(chrono::seconds(1));
        mtx.lock();
        if (barrel_fullness < H) {
            ++barrel_fullness;
            if (barrel_fullness == H) {
                cout << "Пчела " << i << " принесла каплю\n";
                while (!WinnieThePooh_sleep_got_enough_sleep && !Pyatochek_sleep_got_enough_sleep) {
                    this_thread::sleep_for(chrono::seconds(1));
                    if (WinnieThePooh_sleep_got_enough_sleep) {
                        WinnieThePooh_sleep = false;
                        WinnieThePooh_sleep_got_enough_sleep = false;
                        cout << "Пчела " << i << " разбудила Винни-Пуxа\n";
                        break;
                    }
                    if (Pyatochek_sleep_got_enough_sleep) {
                        Pyatochek_sleep = false;
                        Pyatochek_sleep_got_enough_sleep = false;
                        cout << "Пчела " << i << " разбудила Пятачка\n";
                        break;
                    }
                }
                if (WinnieThePooh_sleep_got_enough_sleep && Pyatochek_sleep_got_enough_sleep) {
                    int flag = rand();
                    if (flag & 1) { 
                        Pyatochek_sleep = false;
                        Pyatochek_sleep_got_enough_sleep = false;
                        cout << "Пчела " << i << " разбудила Пятачка\n";
                    }
                    else  {
                        WinnieThePooh_sleep = false;
                        WinnieThePooh_sleep_got_enough_sleep = false;
                        cout << "Пчела " << i << " разбудила Винни-Пуxа\n";
                    }
                }
                else if (WinnieThePooh_sleep_got_enough_sleep) {
                    WinnieThePooh_sleep = false;
                    WinnieThePooh_sleep_got_enough_sleep = false;
                    cout << "Пчела " << i << " разбудила Винни-Пуxа\n";
                }
                else if (Pyatochek_sleep_got_enough_sleep) {
                    Pyatochek_sleep = false;
                    Pyatochek_sleep_got_enough_sleep = false;
                    cout << "Пчела " << i << " разбудила Пятачка\n";
                }
            }
            else  cout << "Пчела " << i << " принесла каплю\n";
        }
        mtx.unlock();
    }
}

void Eating() {
    while (1) {
        if (!WinnieThePooh_sleep) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Винни-Пуx всё съел\n";
            barrel_fullness = 0;
            WinnieThePooh_sleep = true;
            WinnieThePooh_sleep_got_enough_sleep = false;
        }
        if (!WinnieThePooh_sleep_got_enough_sleep) {
            mtx.lock();
            cout << "Винни-Пуx лёг спать\n";
            mtx.unlock();
            this_thread::sleep_for(chrono::seconds(6));
            cout << "Винни-Пуx выспался\n";
            WinnieThePooh_sleep_got_enough_sleep = true;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void EatingPig() {
    while (1) {
        if (!Pyatochek_sleep) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Пятачёк съел 1/4 горшка\n";
            barrel_fullness = barrel_fullness * 0.75;
            Pyatochek_sleep = true;
            Pyatochek_sleep_got_enough_sleep = false;
        }
        if (!Pyatochek_sleep_got_enough_sleep) {
            mtx.lock();
            cout << "Пятачёк лёг спать\n";
            mtx.unlock();
            this_thread::sleep_for(chrono::seconds(3));
            cout << "Пятачёк выспался\n";
            Pyatochek_sleep_got_enough_sleep = true;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}
