#pragma once
#include "Object.h"


class Background : public Object
{
public:
	bool Render() override;
	bool LoadContent() override;
	Background();
	~Background();
};

