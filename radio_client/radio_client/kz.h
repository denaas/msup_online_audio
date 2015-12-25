typedef void (*printout_byte_array)(const char* text, unsigned char* value, unsigned int valueSize);

typedef void (*printout_uint_array)(const char* text, unsigned int* value, unsigned int valueSize);
/* Выполнение зашифрования блока
*
 plainText Исходный блок
 chipherText Зашифрованный блок
 keys Развернутые ключи
 print функция логирования
 print_uint функция логирования
 0 если все преобразование прошло успешно
 -1 если произошла ошибка
*/
int  Encrypt_14(unsigned char* plainText, unsigned char* chipherText, unsigned char* keys, printout_byte_array print, printout_uint_array print_uint);

/* Выполение расшифрования блока
*
 chipherText Зашифрованный блок
 plainText Расшифрованный блок
 keys Развернутые ключи
 print функция логирования
 print_uint функция логирования
 0 если все преобразование прошло успешно
 -1 если произошла ошибка
*/
int  Decrypt_14(unsigned char* chipherText, unsigned char* plainText, unsigned char* keys, printout_byte_array print, printout_uint_array print_uint);

int  funcF(unsigned char* inputKey, unsigned char* inputKeySecond, unsigned char* iterationConst, unsigned char* outputKey, unsigned char* outputKeySecond, printout_byte_array print);


int  funcC(unsigned char number, unsigned char* output, printout_byte_array print);
