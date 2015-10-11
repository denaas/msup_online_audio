/*использование CryptoAPI*/

#include "wincrypt.h"

struct Package {
	char *data;
};

/*на входе - номер пакета, на выходе - пакет с шифрованным блоком файла*/
Package Create_package(int num_of_packet) {
	/*запуск криптопровайдера с помощью функции*/
	BOOL CRYPTFUNC CryptAcquireContext(...);
	
	char *buf;
	buf = (n-тый блок файла);
	CryptEncrypt(buf...); //шифруем файл
	
	/*завершение работы с криптопровайдером*/
	CryptReleaseContext(...); 
} 

char *Dec_package(Package pack) {
	/*запуск криптопровайдера с помощью функции*/
	CryptAcquireContext(...);
	
	char *buf;
	buf = (n-тый блок файла);
	CryptDecrypt(buf...); //шифруем файл
	
	/*завершение работы с криптопровайдером*/
	CryptReleaseContext(...); 
}