// GM_S_K.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GM_S_K.h"
#include "defs.h"
#include "CLASS2.H"
#include "GMLAN.H"
#include "GM_OTHER.h"
#include <stdio.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CLASS2 0x1100
#define Keyword2000 0x1200
#define GMLAN 0x1300
#define RGM_LAN_250KBd 0x1400
#define KWP2000_on_CAN 0x1500

// The one and only application object

CWinApp theApp;

using namespace std;
void SwapShort( unsigned short& val )
{
	unsigned short aTemp;

	aTemp  = (val << 8) & 0xFF00;
	aTemp |= (val >> 8) & 0x00FF;

	val = aTemp;
}


int  sub_10001073(int a1, int a2)
{
	unsigned short new_value;
	unsigned char highBYTE, lowBYTE;
	unsigned short temp1, temp2;
	highBYTE = *(BYTE *)a2;
	lowBYTE = *(BYTE *)(a2+1);

	temp1 = *(_WORD *)a1;
	temp2 = *(_WORD *)a1;
	temp1 = temp1 >> lowBYTE;
	temp2 = temp2 << ( 16 - lowBYTE );
	*(_WORD *)a1 = (temp1 | temp2);
	return 0;
}
int  sub_1000110C(int a1, int a2)
{
	unsigned short temp = *(unsigned short*)a2;
	*(_WORD *)a1 += temp;
	return 0;
}
int  sub_1000109C(int a1, int a2)
{
	unsigned __int8 v2; // dl@1
	unsigned __int8 v3; // cl@1
	__int16 v4; // si@1
	unsigned short v6; // cx@1
	int v7; // ecx@1

	v6 = *(_WORD *)a1;
	SwapShort(v6);
	v4 = v6;
	v7 = a2;
	*(_WORD *)a1 = v4;
	v2 = *(BYTE *)v7;
	v3 = *(BYTE *)(v7 + 1);
	if ( v2 >= v3 )
		*(_WORD *)a1 = v4 + v3 + (v2 << 8);
	else
		*(_WORD *)a1 = v4 + v2 + (v3 << 8);
	return 0;
}
int  sub_100010EC(int a1, int a2)
{
	unsigned short temp = *(unsigned short*)a2;
	SwapShort(temp);
	*(_WORD *)a1 -= temp;
	return 0;
}
int  sub_10001131(int a1, int a2)
{
	unsigned short temp = *(unsigned short*)a2;
	*(_WORD *)a1 = (*(_WORD *)a1-temp);
	return 0;
}
int  sub_10001183(int a1, int a2)
{
	*(_WORD *)a1 |= *(BYTE *)a2 + (*(BYTE *)(a2 + 1) << 8);
	return 0;
}
int  sub_10001151(int a1, int a2)
{
	*(_WORD *)a1 = (*(_WORD *)a1 << 8 & 0xff00) | (*(_WORD *)a1 >> 8 & 0xff);
	return 0;
}
int  add(int seed, int a2)
{
	unsigned short temp = *(unsigned short*)a2;
	SwapShort(temp);
	*(_WORD *)seed += temp;
	return 0;
}
int  sub_10001028(int a1, int a2)
{
	__int16 v2; // ax@1
	int v4; // esi@1
	unsigned char low, high;
	v4 = a2;
	low = *(unsigned char *)v4;
	high = *(unsigned char *)++v4;
	v2 = ~*(_WORD *)a1;
	*(_WORD *)a1 = v2;
	if ( low < high )
		*(_WORD *)a1 = v2 + 1;
	return 0;
}
int __stdcall sub_1000115E(int a1, int a2)
{
	*(_WORD *)a1 &= *(BYTE *)a2 + (*(BYTE *)(a2 + 1) << 8);
	return 0;
}
int __stdcall sub_1000104B(int a1, int a2)
{
	unsigned char highBYTE, lowBYTE;
	highBYTE = *(BYTE *)a2;
	lowBYTE = *(BYTE *)(a2+1);
	unsigned short temp1, temp2;
	temp1 = *(_WORD *)a1; 
	temp2 = *(_WORD *)a1;
	temp1 = temp1 << highBYTE;
	temp2 = temp2 >> ( 16 - highBYTE );
	*(_WORD *)a1 = ( temp1 | temp2 );

	return 0;
}

int CalcKey(unsigned short  seed/*Seed*/, unsigned short  magicWord/*algo #*/, unsigned short  *ptr_Key/*ptr key*/)
{
	__int16 v4; // cx@1
	char v5; // bl@1
	int v6; // edi@1
	int v7; // esi@5
	char *v8; // eax@9
	int v9; // ecx@9
	int v10; // ecx@25
	int v11; // ecx@26
	int v12; // ecx@27
	int v13; // ecx@28
	char v15; // zf@35
	int v16; // [sp+8h] [bp-4h]@5

	v6 = 0;//this;
	v4 = (_WORD)magicWord >> 12;
	v5 = BYTE1(magicWord) & 0xF;
	BYTE3(magicWord) = (_WORD)magicWord >> 12;
	if ( ptr_Key )
	{
		if ( (BYTE)magicWord )
		{
			v7 = 0xD * (unsigned __int8)magicWord;
			v16 = 4;
			while ( 1 )
			{
				if ( v5 != 3 )
				{
					LOBYTE(v9) = Class2[v7];
					v8 = (char *)&Class2[v7 + 1];
				}
				else
				{
					if ( (BYTE)v4 != 1 )
					{
						LOBYTE(v9) = GM_LAN[v7];
						v8 = (char *)&GM_LAN[v7 + 1];
					}
					else
					{
						LOBYTE(v9) = GM_OTHER[v7];
						v8 = (char *)&GM_OTHER[v7 + 1];
					}
				}
				v9 = (unsigned __int8)v9;
				if ( (unsigned __int8)v9 > (signed int)0x52u )
				{
					v10 = v9 - 0x6B;
					if ( !v10 )
					{
						sub_10001073((int)&seed, (int)v8);
					}
					else
					{
						v11 = v10 - 0xA;
						if ( !v11 )
						{
							sub_1000110C((int)&seed, (int)v8);
						}
						else
						{
							v12 = v11 - 9;
							if ( !v12 )
							{
								sub_1000109C((int)&seed, (int)v8);
							}
							else
							{
								v13 = v12 - 0x1A;
								if ( !v13 )
								{
									sub_100010EC((int)&seed, (int)v8);
								}
								else
								{
									if ( v13 == 0x60 )
										sub_10001131((int)&seed, (int)v8);
								}
							}
						}
					}
				}
				else
				{
					if ( (unsigned __int8)v9 == 0x52 )
					{
						sub_10001183((int)&seed, (int)v8);
					}
					else
					{
						switch ( v9 )
						{
						case 5:
							sub_10001151((int)&seed, (int)v8);
							break;
						case 0x14:
							add((int)&seed, (int)v8);
							break;
						case 0x2A:
							sub_10001028((int)&seed, (int)v8);
							break;
						case 0x37:
							sub_1000115E((int)&seed, (int)v8);
							break;
						case 0x4C:
							sub_1000104B((int)&seed, (int)v8);
							break;
						}
					}
				}
				v7 += 3;
				v15 = v16-- == 1;
				if ( v15 )
					break;
				LOBYTE(v4) = BYTE3(magicWord);
			}
			*(_WORD *)ptr_Key = seed;
		}
		else
		{
			*(_WORD *)ptr_Key = ~seed;
		}
		v6 = 0;
	}
	else
	{
		v6 = 0x80004005u;
	}
	return v6;
}
int Menu (void)
{

	printf( "1: Enter a Seed and Algorithm\n" );
	printf( "2: Enter a Seed and sweep Algorithms\n" );
	printf( "3: Change Interpretor Type \n" );
	printf( "4: Enter a Seed and Key to find Algorithm\n" );
	printf( "5: Display Algorithm String\n" );
	printf( "6: Reegression Test\n" );
	printf( "7: Redisplay Menu\n" );
	printf( "8: Exit Program\n" );
	return 0;
}

void regressionTest()
{
	int key = 0;
	unsigned short usKey1;
	unsigned short  usKey2;

	typedef short (CALLBACK* SetSeedAndGetKey)(unsigned short a2, unsigned short a3, unsigned short *a4);

	BOOL freeResult, runTimeLinkSuccess = FALSE; 
	HINSTANCE dllHandle = NULL;              
	SetSeedAndGetKey S_KPtr = NULL;

	//Load the dll and keep the handle to it
	//dllHandle = LoadLibrary("sale.dll");
	dllHandle = LoadLibrary("dllsecurity.dll");

	// If the handle is valid, try to get the function address. 
	if (NULL != dllHandle) 
	{ 
		//Get pointer to our function using GetProcAddress:
		S_KPtr = (SetSeedAndGetKey)GetProcAddress(dllHandle,
			"?SetSeedAndGetKey@CSecurity@@QAEJGGPAG@Z");

		// If the function address is valid, call the function.
		//CSecurity__SetSeedAndGetKey<eax>(int a1<ebp>, int a2, int a3, int a4)

		if (runTimeLinkSuccess = (NULL != S_KPtr))
		{
			FILE * File;			
			unsigned short magic = 0;
			unsigned char type = 0;
			unsigned short algo = 0;
			char kbuff[0x80];
			printf("Silent? Y/N:\n");
			gets_s(kbuff, 128);
			char silent = 0;
			if(kbuff[0] == 'Y' || kbuff[0] == 'y')
				silent = 1;
			printf("Log to file? Y/N\tWARNING File will be > 2gb\n");
			gets_s(kbuff, 128);
			char log = 0;
			if(kbuff[0] == 'Y' || kbuff[0] == 'y')
				log = 1;

			if(log)
				File = fopen("regression_test.txt","at");

			for(type = 0; type<0x05; type++)
			{
				switch(type)
				{
				case(0):
					magic = CLASS2;
					break;
				case(1):
					magic = Keyword2000;
					break;
				case(2):
					magic = GMLAN;
					break;
				case(3):
					magic = RGM_LAN_250KBd;
					break;
				case(4):
					magic = KWP2000_on_CAN;
					break;
				default:
					magic = CLASS2;
					break;
				}


				for(algo = 0; algo <= 0xFF; algo++)
				{
					unsigned short magicShort = (magic | (algo & 0xFF));

					for(int seed = 0x0000; seed<=0xFFFF; seed++)//test all keys for furrent algo
					{
						usKey1 = 0xA5A5;
						usKey2 = 0x5A5A;
						unsigned short retVal = S_KPtr(seed, magicShort, &usKey1);
						CalcKey(seed, magicShort, &usKey2);
						if(usKey1 != usKey2)
							printf("**********FAILURE********\nMagic Word 0x%X, Seed 0x%X, Calc'd key 0x%X, Key from dll 0x%X\n", magicShort, seed, usKey2, usKey1);

						if(log)
						{
							int a = 0;
							
							if (File != NULL)
							{
								fprintf( File,"Magic Word 0x%X, Seed 0x%X, Calc'd key 0x%X, Key from dll 0x%X\n", magicShort, seed, usKey2, usKey1);
							}
						}
						else
						{
							if(!silent)
								printf("Magic Word 0x%X, Seed 0x%X, Calc'd key 0x%X, Key from dll 0x%X\n", magicShort, seed, usKey2, usKey1);
						}
					}
				}
			}
			if(log)
			{
				fclose(File);
				fprintf(File, "\n\n");
				printf("Log saved to regression_test.txt");
			}
		}

		Menu();
		//Free the library:
		freeResult = FreeLibrary(dllHandle);       
	}

	//If unable to call the DLL function, use an alternative. 
	if(!runTimeLinkSuccess)
		printf("message via alternative method\n"); 
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = -1;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			unsigned short seed, key, keytmp, magic;
			int a, type, keyin, success, i;
			char kbuff[0x80];
			const unsigned char (*dtemp);
			key = 0xffff;
			keytmp = 0;
			FILE * File;
			type = 0;
			magic = CLASS2;
			printf( "\n\nGM Seed/Key Tester v2.62\nCopyright 2009-2019 Tim Milliken.\n\n" );
			Menu();

			while(1)
			{
				printf( "\nCommand:  ");
				gets_s(kbuff, 128);
				printf( "\n");

				keyin = strtol( kbuff , NULL , 10 );

				switch (keyin)
				{

				case 1:
					{
						printf( "Seed: ");
						gets_s(kbuff, 128);
						seed = strtol( kbuff , NULL , 16 );
						printf( "Algorithm: ");
						gets_s(kbuff, 128);
						a = strtol( kbuff , NULL , 16 );
						magic = (magic | a);
						CalcKey ( seed, magic, &key); 
						printf( "Seed: 0x%X  Key: 0x%X  Algorithm: 0x%X\n" , seed,key,a );
						break;
					}

				case 2:
					{
						printf( "Seed: ");
						gets_s(kbuff, 128);
						seed = strtol( kbuff , NULL , 16 );
						File = fopen("sweep.txt","at");
						if (File != NULL)
						{
							for (a = 0;a<=256;a++)
							{
								//generate_key ( &seed, &key, a, type); 
								fprintf( File,"Seed: 0x%X  Key: 0x%X  Algorithm: 0x%X\n" , seed,key,a );
							}
							fprintf(File, "\n\n");
							printf("Log saved to sweep.txt");
						}
						fclose(File);
						break;
					}

				case 3:
					{
						printf("0 = CLASS2, 1 = Keyword2000, 2 = GMLAN, 3 = RGM_LAN_250KBd, 4 = KWP2000_on_CAN\n");
						printf( "Type [0/1/2/3/4]: ");
						gets_s(kbuff, 128);
						type = strtol( kbuff , NULL , 16 );
						switch(type)
						{
						case(0):
							magic = CLASS2;
							break;
						case(1):
							magic = Keyword2000;
							break;
						case(2):
							magic = GMLAN;
							break;
						case(3):
							magic = RGM_LAN_250KBd;
							break;
						case(4):
							magic = KWP2000_on_CAN;
							break;
						default:
							magic = CLASS2;
							break;
						}

						break;
					}

				case 4:						// needs to be fixed, will stop on 1st match when there could be multiple matches
					{
						a=0;
						success = 0;
						printf( "Seed: ");
						gets_s(kbuff, 128);
						seed = strtol( kbuff , NULL , 16 );
						printf( "Key: ");
						gets_s(kbuff, 128);
						keytmp = strtol( kbuff , NULL , 16 );
						printf("Searching... ");
						while( success != 1 && a<=256)
						{
							//		printf("\b-\b\\\b|\b/"); should spin cursor.. but way too damn fast on my machine
							//generate_key ( &seed, &key, a, type); 
							a++;
							if (keytmp == key)
								success = 1;
						}
						if (!success)
							printf("\nDid not find Seed/Key pair using all Algorithms and Class 2 Interpreter\n");

						else
						{
							printf( "\nSeed: 0x%X  Key: 0x%X\n" , seed,key);
							printf("Algorithm 0x%X: ",a-1);
							for (i = 0; i<=11; i++)
							{
								//dtemp = &old_array[a-1][i];
								printf("0x%X ", (*dtemp));
							}
						}
						if (!success)
						{
							printf("\nSwitching Interpreter type..\n");
							printf("Searching... ");
							type = 1;
							a = 0;
							while( success != 1 && a<=256)
							{
								//		printf("\b-\b\\\b|\b/"); should spin cursor.. but way too damn fast on my machine
								//generate_key ( &seed, &key, a, type); 
								a++;
								if (keytmp == key)
									success = 1;
							}
							if (!success)
								printf("\nDid not find Seed/Key pair using all Algorithms and GMLAN Interpreter\n");

							else
							{
								printf( "\nSeed: 0x%X  Key: 0x%X\n" , seed,key);
								printf("Algorithm 0x%X: ",a-1);

								for (i = 0; i<=11; i++)
								{
									//dtemp = &new_array[a-1][i];
									printf("0x%X ", (*dtemp));
								}
							}
						}
						if (!success)
						{
							printf("\nSwitching Interpreter type..\n");
							printf("Searching... ");
							type = 2;
							a = 0;
							while( success != 1 && a<=256)
							{
								//		printf("\b-\b\\\b|\b/"); should spin cursor.. but way too damn fast on my machine
								//generate_key ( &seed, &key, a, type); 
								a++;
								if (keytmp == key)
									success = 1;
							}
							if (!success)
								printf("\nDid not find Seed/Key pair using all Algorithms and GM_BOSCH Interpreter\n");

							else
							{
								printf( "\nSeed: 0x%X  Key: 0x%X\n" , seed,key);
								printf("Algorithm 0x%X: ",a-1);

								for (i = 0; i<=11; i++)
								{
									//dtemp = &GM_BOSCH[a-1][i];
									printf("0x%X ", (*dtemp));
								}
							}
						}
						type = 0; // go back to default interpreter

						break;
					} 

				case 5:
					{
						printf( "Algorithm: ");
						gets_s(kbuff, 128);
						a = strtol( kbuff , NULL , 16 );
						printf("Algorithm 0x%X: ",a);
						if (type != 0)
						{
							for (i = 0; i<=11; i++)
							{
								//dtemp = &new_array[a][i];
								printf("0x%X ", (*dtemp));
							}
						}
						else
						{
							for (i = 0; i<=11; i++)
							{
								//dtemp = &old_array[a][i];
								printf("0x%X ", (*dtemp));
							}

						}
						//Menu();
					}
					break;
				case 6:
					regressionTest();
					break;

				case 7:
					Menu();
					break;

				case 8:
					exit(1);
					break;
				default: 
					break;
				}

			}
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return 1;
}
