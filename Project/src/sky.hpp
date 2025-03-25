#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure
struct scene_structure;

using namespace cgp;

struct sky_structure{
    cgp::hierarchy_mesh_drawable hierarchy;

    void initialize(scene_structure& scene);
    void initialize_sky_cube(scene_structure& scene, mesh_drawable& sky_part, const float SKY_SCALE, const vec3& SKY_TRANSLATION);
    void display(scene_structure& scene);
};