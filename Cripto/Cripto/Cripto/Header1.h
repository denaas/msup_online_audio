/*unsigned char ctx[kOfb14ContextLen];��������� ctx*/

/* @brief ������ ��������� ��� ������ ���������� OFB ��������� "��������" */
#define kOfb14ContextLen 0x60
/* ������ ����� ��������� "��������" */
#define kBlockLen14 16

/* ������ ����� ��������� 28147-89 */
#define kBlockLen89 8

/* ������ ����� ��������� 28147-89 */
#define kKeyLen89 32

/* ������������� ��������� ���������� � ������ OFB ��� ��������� "��������"

key ����
ctx �������� ofb
s �������� S
iv �������������
ivLength ����� �������������
return 0 ���� ��� �������������� ������ �������
return -1 ���� ��������� ������
*/
int init_ofb_14(unsigned char *key, void *ctx, size_t s, unsigned char *iv, size_t ivLength);

/* �������� ��������� ecb
*
ctx �������� ecb
return 0 ���� ��� �������������� ������ �������
return -1 ���� ��������� ������
*/
void free_ecb(void* ctx);

/* @brief ���������� ������� ���������� ���������� � ������ ������������ � �������� ������

ctx �������� OFB
indata ������� ����
outdata ��������� ��������������
inlength ����� ������
return 0 ���� ��� �������������� ������ �������
return -1 ���� ��������� ������
*/
int crypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

/* @brief ���������� ������������ ���������� � ������ ������������ � �������� ������

ctx �������� OFB
indata �������� �����
outdata ������������� �����
inlength ����� ������
return 0 ���� ��� �������������� ������ �������
return -1 ���� ��������� ������
*/
int encrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

/* @brief ���������� ������������� ���������� � ������ ������������ � �������� ������

ctx �������� OFB
indata ������������� �����
outdata �������������� �����
inlength ����� ������
return 0 ���� ��� �������������� ������ �������
return -1 ���� ��������� ������
*/
int decrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t inlength);

