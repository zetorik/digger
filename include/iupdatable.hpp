#pragma once

#include <string>

class IUpdatable {
    public:
        virtual void update(float deltaTime) = 0;
        virtual ~IUpdatable() = default;
        bool isDestroying() { return destroying; };
        void planDestroy() { destroying = true; };
    protected:
        bool destroying = false;
};

