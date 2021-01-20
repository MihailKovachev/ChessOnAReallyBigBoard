#pragma once

#include <iostream>

template <typename T>
class Singleton
{
public:
	Singleton()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = static_cast<T*>(this);
		}
		else
		{
			std::cout << "\n Trying to create more than one Singleton instance";
		}
	}
	
	virtual ~Singleton()
	{
		s_Instance = nullptr;
	}
	
	static T& GetInstance()
	{
		return *s_Instance;
	}

	static void CreateInstance()
	{
		s_Instance = new T();
	}

	static void RemoveInstance()
	{
		delete s_Instance;
	}

private:
	static T* s_Instance;
};

template <typename T> T* Singleton<T>::s_Instance = nullptr;
