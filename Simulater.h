#pragma once

class Simulatable;

class Simulater
{
public:
	// Constructors and Destructors
	Simulater() = default;
	~Simulater() = default;

private:
	// Members
	std::vector<Simulatable*> PhysicsQueue;

public:
	// Methods
	void AddSimulatable(Simulatable* simulatable);
	void StepSimulatables();

public:
	// Type Methods
	std::vector<Simulatable*>* GetSimulatables();
};
