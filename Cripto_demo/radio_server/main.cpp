#include "Criptofunction.h"
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

int main()
{
	unsigned char kSeltTestGost14OfbSV[32] =
	{
		0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xce, 0xf0, 0xa1, 0xb2, 0xc3, 0xd4, 0xe5, 0xf0, 0x01, 0x12,
		0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
	};
	const size_t svLen = sizeof(kSeltTestGost14OfbSV) / sizeof(kSeltTestGost14OfbSV[0]);
	unsigned char cstr[513];
	unsigned char outText[513];
	for (size_t i = 0; i < 512; i++)
	{
		cstr[i] = i+'0';
	}
	
	unsigned char ctx[kOfb14ContextLen];
	unsigned char ctx1[kOfb14ContextLen];
	using namespace Cripto;
	using namespace std;
	Criptofunction x;
	unsigned char kSeltTestGost14MasterKeyData[32] =
	{
		0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,0x77,
		0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
	};
	if (x.init_ofb_14(kSeltTestGost14MasterKeyData, ctx, kBlockLen14, kSeltTestGost14OfbSV, svLen, 0, 0));

	if (x.encrypt_ofb(ctx,cstr, outText, 512));
	x.free_ofb(ctx);
	cstr[512]='\0';
	outText[512] = '\0';
	cout << cstr << endl;
	cout << endl;
	for (size_t i = 0; i < 512; i++)
	{
		cstr[i] = 0;
	}
	cout << cstr << endl;
	if (x.init_ofb_14(kSeltTestGost14MasterKeyData, ctx1, kBlockLen14, kSeltTestGost14OfbSV, svLen, 0, 0));
	if (x.decrypt_ofb(ctx1,outText, cstr, 512));
	x.free_ofb(ctx1);
	cout << endl;
	cout << cstr << endl;
	char* cstr1=x.Hesh((char*)cstr,512);
	cout << endl;
	cout << cstr1 << endl;
	cin >> outText[0];
}