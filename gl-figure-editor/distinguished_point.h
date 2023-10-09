#pragma once
#include "config.h"

class DistinguishedPoint : public point<int>
{
public:
	DistinguishedPoint(GLFWwindow* window, const point<int>& p);
	~DistinguishedPoint();
	void draw() const;
	void update(const point<int> mouse_pos);

private:
	uint pointVAO, pointVBO;
	point<float> pointVertex;
	GLFWwindow* window;
};

