#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "IObserver.h"

namespace ArkanoidGame
{
    class IObservable : public std::enable_shared_from_this<IObservable>
    {
    public:
        virtual ~IObservable() = default;

        void AddObserver(std::weak_ptr<IObserver> observer)
        {
            observers.push_back(observer);
        }

    protected:
        void Emit()
        {
            auto self = shared_from_this();
            std::for_each(observers.begin(), observers.end(), [self](auto observer) {
                auto lockedObserver = observer.lock();
                if (lockedObserver) {
                    lockedObserver->Notify(self);
                }
                });
        }

    private:
        std::vector<std::weak_ptr<IObserver>> observers;
    };
}