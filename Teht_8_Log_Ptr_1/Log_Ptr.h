#pragma once


template <class T>
class Log_Ptr
{
public:
	Log_Ptr(T* i);
	~Log_Ptr();

	T* operator-> ();
	T& operator* ();

private:
	T* _i;
	int* refs = 0;
};



