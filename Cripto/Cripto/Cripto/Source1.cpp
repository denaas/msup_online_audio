#include "stdafx.h"
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
#include "Criptofunction.h"
#include "kz.h"
/* определение внутреннего ассерта */
#define INFOTECS_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
/* определение внутреннего ассерта */
#define INFOTECS_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]

/* размер тестовых данных для алгоритма "кузнечик" */
#define textLen14 sizeof(kSeltTestGost14PlainText)/sizeof(kSeltTestGost14PlainText[0])

/* Признак алгоритма "Кузнечик" */
const unsigned char kAlg14 = 1;

/* указатель на функцию шифрования */
typedef int (*pEncrypt)(unsigned char* plainText, unsigned char* chipherText, unsigned char* keys, printout_byte_array print, printout_uint_array print_uint);

/* указатель на функцию расшифрования */
typedef int (*pDecrypt)(unsigned char* chipherText, unsigned char* plainText, unsigned char* keys, printout_byte_array print, printout_uint_array print_uint);

/* Контекст OFB */
typedef struct
{
	unsigned char Alg; /**< идентификатор алгоритма */
	unsigned char* IV; /**< синхропосылка */
	unsigned char* Keys;  /**< ключ */
	size_t M; /**< размер синхрпосылки */
	size_t S; /**< параметр S */
	size_t BlockLen; /**< размер блока */
	printout_byte_array PrintByteArray; /**< функция логирования */
	printout_uint_array PrintUIntArray; /**< функция логирования */
	pEncrypt EncryptFunc; /**< функция шифрования */
	pDecrypt DecryptFunc; /**< функция расшифрования */
	unsigned char *tmpblock;  /**< временный блок */
	unsigned char* nextIV; /**< синхропосылка для следующего блока */
} Context_ofb;



int ExpandKey(unsigned char* masterKey, unsigned char* keys, printout_byte_array print)
{
	unsigned char C[16];
	unsigned char temp1[16];
	unsigned char temp2[16];
	unsigned char j, i;

	using namespace std;
	if (!masterKey || !keys)
	{
		cout<<"ExpandKey: internal error!"<<endl;
		return -1;
	}


	memcpy(keys, masterKey, 16);
	memcpy(keys + 16, masterKey + 16, 16);

	if (print)
	{
		print("ExpandKey: master key: ", masterKey, 16);
		print("ExpandKey: output key: ", keys, 16);
		print("ExpandKey: output key: ", keys + 16, 16);
	}

	for (j = 0; j < 4; ++j)
	{
		memcpy(temp1, keys + j * 2 * 16, 16);
		memcpy(temp2, keys + (j * 2 + 1) * 16, 16);

		for (i = 1; i < 8; ++i)
		{
			funcC(j * 8 + i, C, print);
			funcF(temp1, temp2, C, temp1, temp2, print);
		}

		funcC(j * 8 + 8, C, print);
		funcF(temp1, temp2, C, temp1, temp2, print);

		memcpy(keys + (j * 2 + 2) * 16, temp1, 16);
		memcpy(keys + (j * 2 + 3) * 16, temp2, 16);

	
			cout << "ExpandKey: output key: "<< keys + (j * 2 + 2) * 16, 16 ;
			cout << "ExpandKey: output key: "<< keys + (j * 2 + 3) * 16, 16 ;
		
	}


	return 0;
}

int init_ofb_14(unsigned char *key, void *ctx, size_t s, unsigned char *iv, size_t ivLength, printout_byte_array print, printout_uint_array print_uint)
{
	Context_ofb* context;
	INFOTECS_ASSERT(sizeof(Context_ofb) <= kOfb14ContextLen);

	if (!ctx || !key || s > kBlockLen14 || (ivLength % kBlockLen14) || !ivLength || !s)
		return -1;

	context = (Context_ofb*)ctx;

	context->Alg = kAlg14;

	context->PrintByteArray = print;
	context->PrintUIntArray = print_uint;

	context->EncryptFunc = Encrypt_14;
	context->DecryptFunc = Decrypt_14;

	context->BlockLen = kBlockLen14;

	context->IV = (unsigned char*)malloc(ivLength);
	context->tmpblock = (unsigned char*)malloc(kBlockLen14);
	context->nextIV = (unsigned char*)malloc(ivLength);
	context->Keys = (unsigned char*)malloc(10 * kBlockLen14);

	if (!context->IV || !context->tmpblock || !context->nextIV || !context->Keys)
		return -1;

	memcpy(context->IV, iv, ivLength);

	context->M = ivLength;

	context->S = s;

	memset(context->Keys, 0, 10 * kBlockLen14);
	ExpandKey(key, context->Keys, print);

	return 0;
}

static void PackBlock(unsigned char* a, size_t aLen, unsigned char* b, unsigned char* r, size_t rLen)
{
	memcpy(r, a, aLen);
	memcpy(r + aLen, b, rLen - aLen);
}

int crypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t length)
{
	Context_ofb* context;
	size_t i, j;

	if (!indata || !outdata || !ctx || !length)
		return -1;

	context = (Context_ofb*)ctx;

	for (i = 0; i < (length / context->BlockLen); ++i)
	{
		context->EncryptFunc(context->IV, context->tmpblock, context->Keys,context->PrintByteArray, context->PrintUIntArray);

		PackBlock(context->IV + context->BlockLen, context->M - context->BlockLen, context->tmpblock, context->nextIV, context->M);
		memcpy(context->IV, context->nextIV, context->M);

		for (j = 0; j < context->S; ++j)
		{
			*outdata++ = *indata++ ^ context->tmpblock[j];
		}
	}
	return 0;
}

int encrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t length)
{
	return crypt_ofb(ctx, indata, outdata, length);
}

int decrypt_ofb(void *ctx, unsigned char *indata, unsigned char *outdata, size_t length)
{
	return crypt_ofb(ctx, indata, outdata, length);
}
void free_ofb(void* ctx)
{
	Context_ofb* context;

	if (!ctx)
		return;

	context = (Context_ofb*)ctx;

	if (context->Keys)
	{
		free(context->Keys);
		context->Keys = 0;
	}

	if (context->IV)
	{
		free(context->IV);
		context->IV = 0;
	}

	if (context->tmpblock)
	{
		free(context->tmpblock);
		context->tmpblock = 0;
	}

	if (context->nextIV)
	{
		free(context->nextIV);
		context->nextIV = 0;
	}

}


unsigned char kSeltTestGost14PlainText[64] =
{
	0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xee, 0xff, 0x0a,
	0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xee, 0xff, 0x0a, 0x00,
	0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xee, 0xff, 0x0a, 0x00, 0x11
};
