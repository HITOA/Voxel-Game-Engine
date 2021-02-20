#pragma once
#include "shader.h"

class VgeInterface;

class VgeBehaviour
{
public:
	virtual void Init() {};
	virtual void Start() {};
	virtual void Update() {};
	VgeInterface* vgeInterface;
};

