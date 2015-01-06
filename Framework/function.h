#pragma once

template <typename T>
void Safe_Delete(T& p)
{
	if(p)
	{
		delete	p;
		p	= NULL;
	}
}

template <typename T>
void Safe_Delete_Array(T& p)
{
	if(p)
	{
		delete	[]	p;
		p	= NULL;
	}
}

template <typename T>
void Safe_Release(T& p)
{
	if(p)
	{
		if(p->Release() == 0)
			p	= NULL;
	}
}

template <typename T>
void Safe_Remove(T& p)
{
	if(p)
	{
		p->Remove();
		p	= NULL;
	}
}

template <typename T>
void Safe_Release_Map(T& p)
{
	T::iterator	iter = p.begin();

	while(iter != p.end())
	{
		Safe_Release(iter->second);
		++iter;
	}

	p.clear();
}

template <typename T>
void Safe_Delete_Array_Map(T& p)
{
	T::iterator	iter = p.begin();

	while(iter != p.end())
	{
		Safe_Delete_Array(iter->second);
		++iter;
	}

	p.clear();
}

template <typename T>
void Safe_Release_VecList(T& p)
{
	T::iterator	iter = p.begin();

	while(iter != p.end())
	{
		Safe_Release(*iter);
		++iter;
	}

	p.clear();
}

template <typename T>
void Safe_Release_VecList(T* p, const int& iSize)
{
	for(int i = 0; i < iSize; ++i)
	{
		T::iterator	iter = p[i].begin();

		while(iter != p[i].end())
		{
			Safe_Release(*iter);
			++iter;
		}

		p[i].clear();
	}
}