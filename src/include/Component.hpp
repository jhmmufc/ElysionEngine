#pragma once

namespace ElysionEngine
{
    class Entity;

    class Component
    {
    public:
        Entity * entity = nullptr;

        virtual void update(float dt);
        virtual void draw();

        virtual ~Component();
    };
}