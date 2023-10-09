#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include <exception>

typedef unsigned int uint;


template<typename T = int>
struct point
{
public:
    T x = -1, y = -1;

    void reset()
    {
        x = y = -1;
    }
    bool operator == (const point<T>& p) const
    {
        if (x == p.x && y == p.y)
            return true;
        return false;
    }
    bool operator != (const point<T>& p) const
    {
        return !(*this == p);
    }

};

template<typename T>
using points_t = std::vector<point<T>>;

enum SceneMode
{
    None,
    View,
    Create,
    Edit,
    Move
};

