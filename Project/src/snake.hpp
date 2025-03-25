#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::hierarchy_mesh_drawable;
using cgp::mesh_drawable;
using cgp::vec3;
using cgp::opengl_shader_structure;
using std::vector;
using std::string;

// Structure representing a collection of snakes in the scene
struct snake_structure {
    // Define constants for snake head radius and number of snakes
    static constexpr float HEAD_RADIUS = 0.2f;
    static constexpr int N_SNAKE = 25;

    // Position vectors for snakes on different axes
    vector<vec3> snake_position_y;
    vector<vec3> snake_position_x;
    vector<vec3> snake_position_previous_y;
    vector<vec3> snake_position_previous_x;

    // Angle vectors for snake movement
    vector<float> snake_angle_y;
    vector<float> snake_angle_x;

    // Hierarchical drawable and mesh drawables for snakes
    hierarchy_mesh_drawable hierarchy_x;
    mesh_drawable body_x;
    mesh_drawable head_x;

    hierarchy_mesh_drawable hierarchy_y;
    mesh_drawable body_y;
    mesh_drawable head_y;

    // Initializes the snakes in the given scene with the specified terrain length
    void initialize(scene_structure& scene, float terrain_length);

    // Initializes a simple snake
    void initialize_snake(scene_structure& scene, mesh_drawable& head, mesh_drawable& body, hierarchy_mesh_drawable& hierarchy,
                          const string& texture_path, opengl_shader_structure& shader,
                          const vec3& rotation_axis, float rotation_angle, const vec3& body_translation);

    // Initializes snakes moving along the x-axis
    void initialize_snake_x(scene_structure& scene);

    // Initializes snakes moving along the y-axis
    void initialize_snake_y(scene_structure& scene);

    // Displays the snakes moving along the x-axis
    void display_snake_x(scene_structure& scene, float terrain_length);

    // Displays the snakes moving along the y-axis
    void display_snake_y(scene_structure& scene, float terrain_length);

    // Displays the snakes in the scene
    void display(scene_structure& scene, float terrain_length);
};
