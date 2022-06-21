#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <istream>
#include <iostream>
#include <string>
#define PORT 5522
using namespace std;

int main()
{
#ifdef WIN32     // 10093 hatasýnýn çözümü
    int iResult;
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup Baslatilamadi: " << iResult << std::endl;
        return 1;
    }
#endif

    int yol = (int)socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sunucu_bilgileri;
    memset(&sunucu_bilgileri, 0, sizeof(sunucu_bilgileri));
    sunucu_bilgileri.sin_family = AF_INET;
    sunucu_bilgileri.sin_addr.s_addr = INADDR_ANY;
    sunucu_bilgileri.sin_port = htons(PORT);

    if (bind(yol, (struct sockaddr*)&sunucu_bilgileri, sizeof(sunucu_bilgileri)) == SOCKET_ERROR) {
        int a = WSAGetLastError();
        perror("Hata");
        cout << a;
        return 1;
    }
    if (listen(yol, 5) < 0) {
        fprintf(stderr, "Dinleme sirasinda hata olustu.");
        return 1;
    }
    struct sockaddr_in istemci_bilgileri;
    socklen_t boyut = sizeof(istemci_bilgileri);
    int istemci_yol = accept(yol, (struct sockaddr*)&istemci_bilgileri, &boyut);
    if (istemci_yol < 0) {
        fprintf(stderr, "Ýsteklerin kabulu sirasinda hata olustu.");
        return 1;
    }
    cout << "'exit' Programý Sonlandirir"<<endl;
    string  Mesaj;
    while (Mesaj != "exit") {
        cout << "Mesaj: ";
        getline(cin, Mesaj);
        char* SentMessage = new char[Mesaj.length() + 1];
        copy(Mesaj.begin(), Mesaj.end(), SentMessage);
        SentMessage = (char*)SentMessage;
        if (send(istemci_yol, SentMessage, strlen(SentMessage) + 1, 0) < 0) {
        	cout<<"Hata Olustu"<<endl;
        }
        else {

        }
    }
    closesocket(istemci_yol);
    closesocket(yol);
    return 0;
}


