#include <iostream>

namespace observer
{
	#define MAX_OBSERVERS 10

	enum class eEvent 
	{
		EntityFell
	};

	struct EventData
	{
		bool isHero{ false };
		virtual ~EventData() = default;
	};

	struct PhysicsBody : EventData
	{
		int gravity		{ 1 };
		bool isFalling	{ false };
		
		void accelerate_gravity()
		{
			gravity = 10;
		}

		void update()
		{
			if (gravity > 2)
			{
				isFalling = true;
			}
			else
			{
				isFalling = false;
			}
		}
	};

	enum class eAchievement
	{
		FellFromHeight
	};

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void onNotify(const EventData&, eEvent) = 0;
	};

	class Achievements : public Observer
	{
	public:
		void onNotify(const EventData& aData, eEvent aEvent) override
		{
			switch (aEvent)
			{
				case observer::eEvent::EntityFell:
				{
					if (aData.isHero)
					{
						const PhysicsBody &r_pb = dynamic_cast<const PhysicsBody&>(aData);
						if (r_pb.isFalling)
						{
						unlock(eAchievement::FellFromHeight);
						}
					}
				break;
				}
			}
		}
	private:
		void unlock(eAchievement achievement)
		{
			switch (achievement)
			{
				case observer::eAchievement::FellFromHeight:
				{
					if (!hero_fell_from_bridge_)
					{
						hero_fell_from_bridge_ = true;
					}
					break;
				}
			}
		}

		bool hero_fell_from_bridge_ { false };
	};

	class Subject
	{
	public:
		void addObserver(Observer* aObserver)
		{
			observers_[numObservers_] = aObserver;
			numObservers_++;
		}
		void removeObserver(Observer* aObserver)
		{
			
		}
	protected:
		void notify(const EventData& aData, eEvent aEvent)
		{
			for (int i = 0; i < numObservers_; i++)
			{
				observers_[i]->onNotify(aData, aEvent);
			}
		}
	private:
		Observer * observers_[MAX_OBSERVERS];
		int numObservers_{ 0 };
	};

	class Physics : public Subject
	{
	public:
		void updateBody(PhysicsBody& aBody)
		{
			aBody.update();
			if (aBody.isFalling)
			{
				notify(aBody, eEvent::EntityFell);
			}
		}
	};

	class Hero
	{
	public:
		Hero()
		{
			physics_.addObserver(&achievements_);
			ph_body_.isHero = true;
		}

		void move()
		{
			ph_body_.accelerate_gravity();

			physics_.updateBody(ph_body_);
		}
	private:
		Achievements achievements_;
		PhysicsBody ph_body_;
		Physics physics_;
	};

	void observer_main()
	{
		Hero h;
		h.move();
	}
}