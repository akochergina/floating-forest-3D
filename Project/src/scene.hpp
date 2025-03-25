#pragma once

#include "cgp/cgp.hpp"
#include "environment.hpp"
#include "gui_parameters.h"
#include "scene_events.hpp"
#include "skull.hpp"
#include "mosquito.hpp"
#include "snake.hpp"
#include "earth_block.hpp"
#include "sky.hpp"
#include "grass.hpp"
#include "tree.hpp"
#include "mushroom.hpp"

// Using cgp structures without explicitly mentioning cgp::
using cgp::mesh;
using cgp::mesh_drawable;
using cgp::vec3;
using cgp::numarray;
using cgp::timer_basic;

// Main scene structure
struct scene_structure : cgp::scene_inputs_generic {
    camera_controller_orbit_euler camera_control;        // Controls for the camera
    camera_projection_perspective camera_projection;    // Projection for the camera
    window_structure window;                             // Window structure
    timer_basic timer;                                   // Basic timer

    // Shader structures for different elements
    opengl_shader_structure shader_grass;
    opengl_shader_structure shader_birch;
    opengl_shader_structure shader_snake_x;
    opengl_shader_structure shader_snake_y;
    opengl_shader_structure shader_earth;

    // Phong material parameters
    const phong_parameters MATERIAL_PHONG = {0.4f, 0.6f, 0.0f, 1.0f};

    static constexpr float TERRAIN_LENGTH = 200.0f;

    // Scene elements
    mesh_drawable global_frame;
    environment_structure environment;
    input_devices inputs;
    gui_parameters gui;
    skull skull;
    mosquito mosquito;
    snake_structure snake;
    earth_block earth_block;
    sky_structure sky;
    grass grass;
    tree_manager tree_manager;
    mushroom_manager mushroom_manager;

    // Function to initialize the scene
    void initialize();

    // Custom initialize functions
    void initialize_shader();

    void initialize_mesh_common(mesh_drawable &part, const mesh &part_mesh);

    void initialize_mesh_with_color(mesh_drawable &part, const mesh &part_mesh, const vec3 &color);

    void initialize_mesh_with_texture(mesh_drawable &part, const mesh &part_mesh, const std::string &texture_path);

    void
    initialize_mesh_with_texture_and_color(mesh_drawable &part, const mesh &part_mesh, const std::string &texture_path,
                                           const vec3 &color);

    // Display the scene frame
    void display_frame();

    // Display the GUI
    void display_gui();

    // Display semi-transparent objects
    void display_semiTransparent();

    void idle_frame();

    void display_info();
};
