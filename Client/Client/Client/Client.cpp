#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#define PORT 5522
int main()
{

	#ifdef WIN32      // 10093 hatasının çözümü
	
	    int iResult;
	    WSADATA wsaData;
	    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	    if (iResult != 0) {
	        std::cout << "WSAStartup Baslatilamadi: " << iResult << std::endl;
	        return 1;
	    }
	#endif
    const char* sunucu_adres = "192.168.1.3";
    struct sockaddr_in sunucu_bilgileri;

    memset(&sunucu_bilgileri, 0, sizeof(sunucu_bilgileri));// sunucu_bilgileri sıfırlıyoruz.
    sunucu_bilgileri.sin_family = AF_INET;                 // Bağlantı türü 
    inet_pton(AF_INET, sunucu_adres, &sunucu_bilgileri.sin_addr);
    sunucu_bilgileri.sin_port = htons(PORT);

    int yol = socket(AF_INET, SOCK_STREAM, 0);
    int Control = connect(yol, (struct sockaddr*)&sunucu_bilgileri, sizeof(sunucu_bilgileri)) < 0;
    if (Control) {
        int a = WSAGetLastError();
        perror("Hata");
        cout << a;
        return 1;
    }
    char alinan_veri[1024];
    while (recv(yol, alinan_veri, 1024, 0) || Control) {
        cout << "Gelen Mesaj: " << alinan_veri << endl;
    }
    cout << "Program kapandi";
    closesocket(yol);
    return 1;

}
