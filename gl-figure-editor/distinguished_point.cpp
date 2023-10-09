#include "distinguished_point.h"

DistinguishedPoint::DistinguishedPoint(GLFWwindow* window, const point<int>& p) : point(p)
{
	this->window = window;
    int SCR_WIDTH, SCR_HEIGHT;
    glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    if (x < 0 || x > SCR_WIDTH || y < 0 || y > SCR_HEIGHT)
        throw std::invalid_argument("Invalid screen coordinates.\n");

    pointVertex = point<float>(
        2.0f * x / (float)SCR_WIDTH - 1.0f, 
        1.0f - 2.0f * y / (float)SCR_HEIGHT
    );

    pointVAO = pointVBO = 0; // ide hack

    glGenVertexArrays(1, &pointVAO);
    glGenBuffers(1, &pointVBO);
    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point<float>), &pointVertex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(point<float>), (void*)0);
    glBindVertexArray(0);
}

DistinguishedPoint::~DistinguishedPoint()
{
    glDeleteVertexArrays(1, &pointVAO);
    glDeleteBuffers(1, &pointVBO);
}

void DistinguishedPoint::draw() const
{
    glBindVertexArray(pointVAO);
    glPointSize(15);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void DistinguishedPoint::update(const point<int> mouse_pos)
{
    int SCR_WIDTH, SCR_HEIGHT;
    glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT); // might throw an error if called here id why

    pointVertex = point<float>(
        2.0f * mouse_pos.x / (float)SCR_WIDTH - 1.0f,
        1.0f - 2.0f * mouse_pos.y / (float)SCR_HEIGHT
    );

    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point<float>), &pointVertex, GL_STATIC_DRAW);
    glBindVertexArray(0);
}
