#pragma once

namespace ArkanoidGame
{
	class IDelayedAction
	{
	protected:
		bool isTimerStarted = false;
		float destroyTime = 0.f;
		float currentTime = 0.f;
		virtual void UpdateTimer(float deltaTime)
		{
			if (!isTimerStarted)
				return;

			currentTime -= deltaTime;
			EachTickAction(deltaTime); 

			if (currentTime <= 0.f)
			{
				FinalAction();
				isTimerStarted = false;
			}
		}

		virtual void FinalAction() = 0;
		virtual void EachTickAction(float deltaTime) = 0;

	public:
		void StartTimer(float destroyTime)
		{
			this->destroyTime = destroyTime;
			currentTime = destroyTime;
			isTimerStarted = true;
		}
	
	};

}