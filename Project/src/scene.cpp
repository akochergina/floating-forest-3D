#pragma once

#include "scene.hpp"
#include "pine_tree.hpp"

using namespace cgp;

void scene_structure::initialize() {
    // Initialize camera controls
    camera_control.initialize(inputs, window);
    camera_control.set_rotation_axis_z();
    camera_control.look_at({15.0f, 6.0f, 6.0f}, {0, 0, 0});

    // Initialize general information
    display_info();
    initialize_shader();
    global_frame.initialize_data_on_gpu(mesh_primitive_frame());

    // Initialize scene objects
    earth_block.initialize(*this, TERRAIN_LENGTH);
    sky.initialize(*this);
    grass.initialize(*this, TERRAIN_LENGTH);
    tree_manager.initialize(*this, TERRAIN_LENGTH);
    mushroom_manager.initialize(*this, TERRAIN_LENGTH);
    mosquito.initialize(*this, TERRAIN_LENGTH);
    snake.initialize(*this, TERRAIN_LENGTH);
    skull.initialize(*this, TERRAIN_LENGTH);
}

void scene_structure::display_frame() {
    const vec3 BACKGROUND_COLOR = {175 / 256.0f, 238 / 256.0f, 238 / 256.0f};

    // Set the light to the current position of the camera
    environment.light = camera_control.camera_model.position();

    // Update the environment background color
    environment.background_color = BACKGROUND_COLOR;

    // Update time
    timer.update();
    environment.uniform_generic.uniform_float["time"] = timer.t;

    // Display objects
    earth_block.display(*this);
    tree_manager.display(*this);
    mushroom_manager.display(*this);
    mosquito.display(*this);
    snake.display(*this, TERRAIN_LENGTH);
    skull.display(*this);

    display_semiTransparent();
}


void scene_structure::display_gui() {
    ImGui::Checkbox("Frame", &gui.display_frame);
    ImGui::Checkbox("Wireframe", &gui.display_wireframe);
}

void scene_structure::idle_frame() {
    camera_control.idle_frame(environment.camera_view);
}

void scene_structure::display_info() {
    std::cout << "\nCAMERA CONTROL:" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << camera_control.doc_usage() << std::endl;
    std::cout << "-----------------------------------------------\n" << std::endl;
}


void scene_structure::display_semiTransparent() {
    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Disable depth buffer write
    glDepthMask(false);

    // Display objects
    sky.display(*this);
    grass.display(*this);

    // Don't forget to re-activate the depth-buffer write
    glDepthMask(true);
    glDisable(GL_BLEND);
}


void scene_structure::initialize_shader() {
    const std::string SHADER_PATH = project::path + "shaders/mesh_custom/";

    shader_snake_y.load(SHADER_PATH + "snake_y.vert.glsl", SHADER_PATH + "mesh_custom.frag.glsl");
    shader_snake_x.load(SHADER_PATH + "snake_x.vert.glsl", SHADER_PATH + "mesh_custom.frag.glsl");
    shader_birch.load(SHADER_PATH + "birch.vert.glsl", SHADER_PATH + "mesh_custom.frag.glsl");
    shader_grass.load(SHADER_PATH + "grass.vert.glsl", SHADER_PATH + "mesh_custom.frag.glsl");
    shader_earth.load(SHADER_PATH + "earth.vert.glsl", SHADER_PATH + "mesh_custom.frag.glsl");
}


void scene_structure::initialize_mesh_with_color(mesh_drawable &part, const mesh &part_mesh, const vec3 &color) {
    // Common initialization
    initialize_mesh_common(part, part_mesh);

    // Set color
    part.material.color = color;
}

void scene_structure::initialize_mesh_with_texture(mesh_drawable &part, const mesh &part_mesh,
                                                   const std::string &texture_path) {
    // Common initialization
    initialize_mesh_common(part, part_mesh);

    // Load texture
    part.texture.load_and_initialize_texture_2d_on_gpu(texture_path, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void scene_structure::initialize_mesh_with_texture_and_color(mesh_drawable &part, const mesh &part_mesh,
                                                             const std::string &texture_path, const vec3 &color) {
    // Common initialization
    initialize_mesh_common(part, part_mesh);

    // Set color
    part.material.color = color;

    // Load texture
    part.texture.load_and_initialize_texture_2d_on_gpu(texture_path, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
}

void scene_structure::initialize_mesh_common(mesh_drawable &part, const mesh &part_mesh) {
    // Initialize mesh part
    part.initialize_data_on_gpu(part_mesh);

    // Set material properties
    part.material.phong = MATERIAL_PHONG;
}
