#pragma once
#include "define.h"
/*
�̱��� Ŭ����

���� : �̱���ȭ �Ϸ��� Ŭ������ 
�̱��� Ŭ������ ��� �޾Ƽ� ���.
*/
template<typename T>
class CSingleton
{
private:
	
	static T* pInstance;

protected:
	
	CSingleton(void){};
	~CSingleton(void){};

public:

	static T* GetInstance()		{
		if(!pInstance)
		{
			pInstance = new T;
		}
		atexit(KillInstance);
		return pInstance;
	};

	static void KillInstance(){
		if(pInstance)
			delete pInstance;
		pInstance = NULL;
	};
};

//���α׷��� �������ڸ��� �ν��Ͻ��� �����ϴ� �̱���
//Singleton* Singleton::pInstance = new Singleton();

//�ƴϸ�  NULL�� �ʱ�ȭ�ϰ� GetInstance()�� ó��
//ȣ���Ҷ� �ν��Ͻ��� �����ϴ� �̱���.
template<typename T>
T* CSingleton<T>::pInstance = 0;