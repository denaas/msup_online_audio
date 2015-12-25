/*unsigned char ctx[kOfb14ContextLen];объявлние ctx*/

/* @brief Размер контекста для режима шифрования OFB алгоритма "кузнечик" */
#define kOfb14ContextLen 0x60
/* Размер блока алгоритма "кузнечик" */
#define kBlockLen14 16

/* Размер блока алгоритма 28147-89 */
#define kBlockLen89 8

/* Размер ключа алгоритма 28147-89 */
#define kKeyLen89 32

/* Инициализация контекста шифрования в режиме OFB для алгоритма "кузнечик"

key ключ
ctx контекст ofb
s параметр S
iv синхропосылка
ivLength длина синхропосылки
return 0 если все преобразование прошло успешно
return -1 если произошла ошибка
*/
int init_ofb_14(unsigned char *key, void *ctx, size_t s, unsigned char *iv, size_t ivLength);

/* Удаление контекста ecb
*
ctx контекст ecb
return 0 если все преобразование прошло успешно
return -1 если произошла ошибка
*/
void free_ecb(void* ctx);

/* @brief Выполнение шаговой шифрования информации в режиме гаммирования с обратной связью

ctx контекст OFB
indata входной блок
outdata результат преобразования
inlength длина текста
return 0 если все преобразование прошло успешно
return -1 если произошла ошибка
*/
int crypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

/* @brief Выполнение зашифрования информации в режиме гаммирования с обратной связью

ctx контекст OFB
indata открытый текст
outdata зашифрованный текст
inlength длина текста
return 0 если все преобразование прошло успешно
return -1 если произошла ошибка
*/
int encrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

/* @brief Выполнение расшифрования информации в режиме гаммирования с обратной связью

ctx контекст OFB
indata зашифрованный текст
outdata расшифрованный текст
inlength длина текста
return 0 если все преобразование прошло успешно
return -1 если произошла ошибка
*/
int decrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

