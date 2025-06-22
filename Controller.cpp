#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <unordered_set>
#include "Controllable.h"
#include "Controller.h"

void Controller::AddControllable(Controllable* controllable)
{
	InputListeners.push_back(controllable);
}

void Controller::RemoveControllable(Controllable* controllable)
{
	std::vector<Controllable*>::iterator _removedResult = std::remove(InputListeners.begin(), InputListeners.end(), controllable);
	InputListeners.erase(_removedResult, InputListeners.end());
}

std::vector<Controllable*> Controller::GetControllables()
{
	return InputListeners;
}

void Controller::BroadcastKeyPressed(sf::Keyboard::Key input)
{
	for (Controllable* _controllable : GetControllables())
	{
		switch (input)
		{
		case sf::Keyboard::Key::Unknown:
			break;
		case sf::Keyboard::Key::A:
			_controllable->KeyPressed_A();
			break;
		case sf::Keyboard::Key::D:
			_controllable->KeyPressed_D();
			break;
		case sf::Keyboard::Key::S:
			_controllable->KeyPressed_S();
			break;
		case sf::Keyboard::Key::W:
			_controllable->KeyPressed_W();
			break;
		case sf::Keyboard::Key::Space:
			_controllable->KeyPressed_Space();
			break;
		default:
			break;
		}
	}
}

void Controller::BroadcastKeyReleased(sf::Keyboard::Key input)
{
	for (Controllable* _controllable : GetControllables())
	{
		switch (input)
		{
		case sf::Keyboard::Key::Unknown:
			break;
		case sf::Keyboard::Key::A:
			_controllable->KeyReleased_A();
			break;
		case sf::Keyboard::Key::D:
			_controllable->KeyReleased_D();
			break;
		case sf::Keyboard::Key::S:
			_controllable->KeyReleased_S();
			break;
		case sf::Keyboard::Key::W:
			_controllable->KeyReleased_W();
			break;
		case sf::Keyboard::Key::Space:
			_controllable->KeyReleased_Space();
			break;
		default:
			break;
		}
	}
}
