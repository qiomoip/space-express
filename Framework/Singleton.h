#pragma once
#include "define.h"
/*
싱글턴 클래스

사용법 : 싱글턴화 하려는 클래스에 
싱글턴 클래스를 상속 받아서 사용.
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

//프로그램이 시작하자마자 인스턴스를 생성하는 싱글턴
//Singleton* Singleton::pInstance = new Singleton();

//아니면  NULL로 초기화하고 GetInstance()를 처음
//호출할때 인스턴스를 생성하는 싱글턴.
template<typename T>
T* CSingleton<T>::pInstance = 0;