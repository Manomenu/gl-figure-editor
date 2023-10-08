#include "line.h"

Line::Line(GLFWwindow* window, const point<int>& start, const point<int>& end)
{
    glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);

	this->start = start;
	this->end = end;
    line_points = points_t<float>();
    bresenham_line_alg();

    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);
    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point<float>) * line_points.size(), &line_points[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(point<float>), (void*)0);
    glBindVertexArray(0);
}

Line::~Line()
{
    glDeleteBuffers(1, &lineVBO);
    glDeleteVertexArrays(1, &lineVAO);
}

void Line::draw() const
{
    glBindVertexArray(lineVAO);
    glPointSize(5);
    glDrawArrays(GL_POINTS, 0, line_points.size());
    glBindVertexArray(0);
}

void Line::bresenham_line_alg()
{
    int y1 = SCR_HEIGHT - start.y, y2 = SCR_HEIGHT - end.y;
    int x1 = start.x, x2 = end.x;
    int stepX = 1, stepY;
    float delta;
    float dx = float(x2 - x1);
    float dy = float(y2 - y1);
    float error = 0.5f;
    points_t<int> line = points_t<int>();
    int len;

    if (x2 > x1)
    {
        if (y2 > y1)
        {
            stepY = 1;
            delta = dy / dx;
        }
        else
        {
            delta = -dy / dx;
            stepY = -1;
        }
    }
    else
    {
        if (y2 > y1)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
            delta = -dy / dx;
            stepY = -1;
        }
        else
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
            delta = dy / dx;
            stepY = 1;
        }
    }

    if (abs(dx) > abs(dy))
    {
        len = abs(x2 - x1);
        line.resize(len);
        line[0] = { x1, y1 };
        for (int i = 1; i < len; ++i)
        {
            line[i].x = line[i - 1].x + stepX;
            error += delta;
            if (error > 0.5f)
            {
                error -= 1.0f;
                line[i].y = line[i - 1].y + stepY;
            }
            else
                line[i].y = line[i - 1].y;
        }
    }
    else
    {
        delta = 1.0f / delta;
        len = abs(y2 - y1);
        line.resize(len);
        line[0] = { x1, y1 };
        for (int i = 1; i < len; ++i)
        {
            line[i].y = line[i - 1].y + stepY;
            error += delta;
            if (error > 0.5f)
            {
                error -= 1.0f;
                line[i].x = line[i - 1].x + stepX;
            }
            else
                line[i].x = line[i - 1].x;
        }
    }

    for (int i = 0; i < len; ++i)
        line_points.push_back(point<float>(2.0f * line[i].x / (float)SCR_WIDTH - 1.0f, 2.0f * line[i].y / (float)SCR_HEIGHT - 1.0f));
}
