#pragma once
class Controllable
{
public:
	// Constructors and Destructors
	Controllable() = default;
	~Controllable() = default;

public:
	// Pressed actions as Virtual Methods w/ Default Implementation
	virtual void KeyPressed_W() {};
	virtual void KeyPressed_A() {};
	virtual void KeyPressed_S() {};
	virtual void KeyPressed_D() {};
	virtual void KeyPressed_Space() {};

public:
	// Released actions as Virtual Methods w/ Default Implementation
	virtual void KeyReleased_W() {};
	virtual void KeyReleased_A() {};
	virtual void KeyReleased_S() {};
	virtual void KeyReleased_D() {};
	virtual void KeyReleased_Space() {};
};
