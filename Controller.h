#pragma once

class Controllable;

class Controller
{
public:
	// Constructors and Destructors
	Controller() = default;
	~Controller() = default;

private:
	// Members
	std::vector<Controllable*> InputListeners;

public:
	// Methods
	void AddControllable(Controllable* controllable);
	void RemoveControllable(Controllable* controllable);
	void BroadcastKeyPressed(sf::Keyboard::Key input);
	void BroadcastKeyReleased(sf::Keyboard::Key input);

public:
	// Type Methods
	std::vector<Controllable*> GetControllables();
};

