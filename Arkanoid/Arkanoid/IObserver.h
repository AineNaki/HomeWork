#pragma once
#include <memory>

namespace ArkanoidGame
{
	class IObservable;

	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(std::shared_ptr<IObservable> observable) = 0;
	};
}