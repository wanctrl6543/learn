// ParamTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "..\include\IParamAPI.h"

int main()
{
	IPARAMAPI* pParm = IPARAMAPI::Create();
	if (pParm)
	{
		pParm->SetParam("123", 1, "aaa", 222.00);
	}
	//getchar();
	pParm->Close();
	getchar();
    return 0;
}

