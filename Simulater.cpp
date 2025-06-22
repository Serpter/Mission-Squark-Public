#include <vector>
#include "Simulatable.h"
#include "Simulater.h"

void Simulater::AddSimulatable(Simulatable* simulatable)
{
	PhysicsQueue.push_back(simulatable);
}

std::vector<Simulatable*>* Simulater::GetSimulatables()
{
	return &PhysicsQueue;
}

void Simulater::StepSimulatables()
{
	std::vector<Simulatable*> _simulatables = *GetSimulatables();

	for (Simulatable* _simulatable : _simulatables)
	{
		_simulatable->Step();
	}
}
