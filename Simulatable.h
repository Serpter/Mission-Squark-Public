#pragma once

class Simulatable
{
public:
	// Constructors and Destructors
	Simulatable() = default;
	~Simulatable() = default;

public:
	// Virtual Pure Methods
	virtual void Step() = 0;
};
