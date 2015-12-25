#ifdef CRIPTOFDLL_EXPORTS
#define CRIPTOFDLL_API _declspec(dllexport)
#else
#define CRIPTOFDLL_API _declspec(dllimport)
#endif

typedef void(*printout_byte_array)(const char* text, unsigned char* value, unsigned int valueSize);

typedef void(*printout_uint_array)(const char* text, unsigned int* value, unsigned int valueSize);

/*  Размер контекста для режима шифрования OFB алгоритма "кузнечик" */
#define kOfb14ContextLen 0x60
/* Размер блока алгоритма "кузнечик" */
#define kBlockLen14 16

/* Размер блока алгоритма 28147-89 */
#define kBlockLen89 8

/* Размер ключа алгоритма 28147-89 */
#define kKeyLen89 32

// const size_t svLen = sizeof(kSeltTestGost14OfbSV)/sizeof(kSeltTestGost14OfbSV[0]);

    // unsigned char ctx[kOfb14ContextLen];

	 // init_ofb_14(kSeltTestGost14MasterKeyData, ctx, kBlockLen14, kSeltTestGost14OfbSV, svLen, 0, 0)
namespace Cripto 
{
	class Criptofunction
	{/* Инициализация контекста шифрования в режиме OFB для алгоритма "кузнечик"

	key ключ
	ctx контекст ofb
	s параметр S
	iv синхропосылка
	ivLength длина синхропосылки
	return 0 если все преобразование прошло успешно
	return -1 если произошла ошибка
	*/
	public:
		static   int init_ofb_14(unsigned char *key, void *ctx, size_t s, unsigned char *iv, size_t ivLength, printout_byte_array print, printout_uint_array print_uint);


	/* Удаление контекста ofb
	*
	ctx контекст ofb
	return 0 если все преобразование прошло успешно
	return -1 если произошла ошибка
	*/
		static   void free_ofb(void* ctx);

	/*  Выполнение шаговой шифрования информации в режиме гаммирования с обратной связью

	ctx контекст OFB
	indata входной блок
	outdata результат преобразования
	inlength длина текста
	return 0 если все преобразование прошло успешно
	return -1 если произошла ошибка
	*/
		static   int crypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

	/*  Выполнение зашифрования информации в режиме гаммирования с обратной связью

	ctx контекст OFB
	indata открытый текст
	outdata зашифрованный текст
	inlength длина текста
	return 0 если все преобразование прошло успешно
	return -1 если произошла ошибка
	*/
		static   int encrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

	/*  Выполнение расшифрования информации в режиме гаммирования с обратной связью

	ctx контекст OFB
	indata зашифрованный текст
	outdata расшифрованный текст
	inlength длина текста
	return 0 если все преобразование прошло успешно
	return -1 если произошла ошибка
	*/
		static  int decrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

	/*  Выполнение хеширования HMAC

	string строка для хеширования
	hashtype==512
	return 0 если все преобразование прошло успешно
	return -1 если произошла ошибка
	*/

		static  char * Hesh(char *string, int hashtype);
};
}