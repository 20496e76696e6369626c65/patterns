#include <memory>
#include <iostream>

namespace singleton
{
	struct Singleton
	{
		static Singleton &instance()
		{
			static Singleton res;
			return res;
		}

	private:
		Singleton() = default;
		Singleton(const Singleton &) = delete;
		Singleton & operator=(const Singleton&) = delete;
	};

}