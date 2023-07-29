#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

int main(){
    int pid, fd1[2], fd2[2];
    while(1){
        cout << "~$ ";
        string cmd;
        cin >> cmd;
        if(cmd == "--help") cout << "Эта программа может вычислить первые 6 многочленов Лагерра.\nЧтобы начать, введите команду \"start\"\n\n";
        else if(cmd == "start") {
            if(pipe(fd1) == -1) cout << "ERROR pipe!\n";
            else if(pipe(fd2) == -1) cout << "ERROR pipe!\n";
            else if((pid = fork()) < 0) cout << "ERROR fork!\n";
            else {
                ifstream input("input.txt");
                ofstream output("output.txt");
                if(!pid) {
                    close(*(fd1 + 1));
                    double *x = new double;
                    read(*fd1, x, sizeof(double));
                    close(*fd1);
                    close(*fd2);
                    double *Lk = new double[6];
                    *Lk = 1;
                    *(Lk + 1) = 1 - *x;
                    for(int i = 2; i - 6; ++i) *(Lk + i) = 1. / i * ((2 * i - 1 - *x) * *(Lk + i - 1) - (i - 1) * *(Lk + i - 2));
                    write(*(fd2 + 1), Lk, 6 * sizeof(double));
                    delete[] Lk;
                    delete x;
                    close(*(fd2 + 1));
                    exit(0);
                }
                else {
                    close(*fd1);
                    double *x = new double;
                    if (!(input >> *x)) {
                        cout << "ERROR: Некорректное значение!\n";
                        main();
                    }
                    cout << "Успешно!\n\n";
                    write(*(fd1 + 1), x, sizeof(double));
                    delete x;
                    close(*(fd1 + 1));
                    close(*(fd2 + 1));
                    double *Lk = new double;
                    read(*fd2, Lk, 6 * sizeof(double));
                    for(int i = 0; i < 6; ++i) output << "L" << i << ": " << *(Lk + i) << endl;
                    delete[] Lk;
                    close(*fd2);
                    exit(0);
                }
                input.close();
                output.close();
            }
        }
        else if(cmd == "quit") return 0;
        else cout << "ERROR: Некорректная команда, введите команду \"--help\".\n\n";
    }
}