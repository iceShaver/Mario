#pragma once
#include "Timer.h"
#include "Texture.h"

class FPSGauge :
	public Timer, public Texture
{
public:
	FPSGauge();
	~FPSGauge();
	void DisplayFPS();
};

