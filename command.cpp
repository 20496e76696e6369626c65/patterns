#include <iostream>

namespace command
{
	enum eButton
	{
		BUTTON_X,
		BUTTON_Y,
		BUTTON_A,
		BUTTON_B
	};

	static bool isPressed(eButton aBtn)
	{
		return true;
	}

	class GameActor
	{
	public:
		void jump() {}
		void fireGun() {}
	};

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(GameActor& actor) = 0;
	};

	class JumpCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor)
		{
			actor.jump();
		}
	};

	class FireCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor)
		{
			actor.fireGun();
		}
	};

	class InputHandler
	{
	public:
		Command* handleInput()
		{
			if (isPressed(BUTTON_X)) buttonX_;
		    if (isPressed(BUTTON_Y)) buttonY_;
			if (isPressed(BUTTON_A)) buttonA_;
			if (isPressed(BUTTON_B)) buttonB_;

			return NULL;
		}

	private:
		Command * buttonX_;
		Command * buttonY_;
		Command * buttonA_;
		Command * buttonB_;
	};

	void command_main()
	{
		GameActor	 actor;
		InputHandler inputHandler;
		Command		 *comm = inputHandler.handleInput();

		if (comm)
		{
			comm->execute(actor);
		}
	}

}