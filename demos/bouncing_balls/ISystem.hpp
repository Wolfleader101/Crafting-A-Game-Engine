#pragma once

class ISystem
{
public:
    virtual ~ISystem() = default;
    virtual void PreInit() = 0;
    virtual void Init() = 0;
    virtual void PostInit() = 0;
    virtual void PreUpdate() = 0;
    virtual void Tick() = 0;
    virtual void Update() = 0;
    virtual void PostUpdate() = 0;
    virtual void Exit() = 0;
};