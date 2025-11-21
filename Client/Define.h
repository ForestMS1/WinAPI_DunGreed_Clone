#pragma once


#define SINGLE(T)			\
public:						\
	static T* GetInst()		\
	{						\
		static T instance;	\
							\
		return &instance;	\
	}						