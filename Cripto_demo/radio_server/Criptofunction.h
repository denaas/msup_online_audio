#ifdef CRIPTOFDLL_EXPORTS
#define CRIPTOFDLL_API _declspec(dllexport)
#else
#define CRIPTOFDLL_API _declspec(dllimport)
#endif

typedef void(*printout_byte_array)(const char* text, unsigned char* value, unsigned int valueSize);

typedef void(*printout_uint_array)(const char* text, unsigned int* value, unsigned int valueSize);

/*  ������ ��������� ��� ������ ���������� OFB ��������� "��������" */
#define kOfb14ContextLen 0x60
/* ������ ����� ��������� "��������" */
#define kBlockLen14 16

/* ������ ����� ��������� 28147-89 */
#define kBlockLen89 8

/* ������ ����� ��������� 28147-89 */
#define kKeyLen89 32

// const size_t svLen = sizeof(kSeltTestGost14OfbSV)/sizeof(kSeltTestGost14OfbSV[0]);

    // unsigned char ctx[kOfb14ContextLen];

	 // init_ofb_14(kSeltTestGost14MasterKeyData, ctx, kBlockLen14, kSeltTestGost14OfbSV, svLen, 0, 0)
namespace Cripto 
{
	class Criptofunction
	{/* ������������� ��������� ���������� � ������ OFB ��� ��������� "��������"

	key ����
	ctx �������� ofb
	s �������� S
	iv �������������
	ivLength ����� �������������
	return 0 ���� ��� �������������� ������ �������
	return -1 ���� ��������� ������
	*/
	public:
		static   int init_ofb_14(unsigned char *key, void *ctx, size_t s, unsigned char *iv, size_t ivLength, printout_byte_array print, printout_uint_array print_uint);


	/* �������� ��������� ofb
	*
	ctx �������� ofb
	return 0 ���� ��� �������������� ������ �������
	return -1 ���� ��������� ������
	*/
		static   void free_ofb(void* ctx);

	/*  ���������� ������� ���������� ���������� � ������ ������������ � �������� ������

	ctx �������� OFB
	indata ������� ����
	outdata ��������� ��������������
	inlength ����� ������
	return 0 ���� ��� �������������� ������ �������
	return -1 ���� ��������� ������
	*/
		static   int crypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

	/*  ���������� ������������ ���������� � ������ ������������ � �������� ������

	ctx �������� OFB
	indata �������� �����
	outdata ������������� �����
	inlength ����� ������
	return 0 ���� ��� �������������� ������ �������
	return -1 ���� ��������� ������
	*/
		static   int encrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

	/*  ���������� ������������� ���������� � ������ ������������ � �������� ������

	ctx �������� OFB
	indata ������������� �����
	outdata �������������� �����
	inlength ����� ������
	return 0 ���� ��� �������������� ������ �������
	return -1 ���� ��������� ������
	*/
		static  int decrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

	/*  ���������� ����������� HMAC

	string ������ ��� �����������
	hashtype==512
	return 0 ���� ��� �������������� ������ �������
	return -1 ���� ��������� ������
	*/

		static  char * Hesh(char *string, int hashtype);
};
}