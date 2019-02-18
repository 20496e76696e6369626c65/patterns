#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <string>


namespace object_pool
{
	struct unit
	{
		int x{ 0 };
		int y{ 0 };
		int health{ 0 };
		int type{ 0 };
	};

	class ObjectPool
	{
	public:
		static ObjectPool &instance()
		{
			static ObjectPool inst;
			return inst;
		}

		unit *get()
		{
			if (objects_.size() == in_use_)
			{
				objects_.push_back(std::make_pair(true, std::make_unique<unit>()));
				in_use_++;
				return objects_[objects_.size() - 1].second.get();
			}
			else
			{
				for (auto &ref : objects_)
				{
					if (ref.first == false)
					{
						ref.first = true;
						in_use_++;
						return ref.second.get();
					}
				}	
			}
			return nullptr;
		}

		void releaseObject(unit *aObject)
		{
			for(auto &ref: objects_)
			{
				if (ref.second.get() == aObject)
				{
					ref.first = false;
					in_use_--;
				}
			}

		}
	private:
		ObjectPool(const ObjectPool &) = delete;
		ObjectPool & operator=(const ObjectPool &) = delete;
		ObjectPool()
		{
			objects_.reserve(100);
		}
		unsigned in_use_{ 0 };
		std::vector<std::pair<bool, std::unique_ptr<unit> > > objects_;
	};

	void object_pool_main()
	{
		ObjectPool &pool = ObjectPool::instance();

		unit *unit_a;
		unit *unit_b;
		unit *unit_c;
		unit *unit_d;

		unit_a = pool.get();
		unit_b = pool.get();
		unit_c = pool.get();

		unit_a->x = 100;
		unit_a->y = 100;
		pool.releaseObject(unit_a);

		unit_d = pool.get();
		unit_d = pool.get();
		unit_d = pool.get();
		unit_d = pool.get();
	}
}