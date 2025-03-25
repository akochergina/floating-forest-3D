#pragma once

#include "cgp/cgp.hpp"
#include "porcini_mushroom.hpp"
#include "mesh_primitive.hpp"
#include "scene.hpp"


using namespace cgp;

void porcini_mushroom::initialize(scene_structure& scene){
    // Its cap is a sphere and the stem is modeled with a cone.
    // The stem and cap mesh are built separately, as different textures and colors are used.

    // Constants for porcini mushroom
    constexpr float STEM_RADIUS = 0.12f;
    constexpr float STEM_HEIGHT = 0.5f;
    constexpr float CAP_RADIUS = 0.3f;

    // Define the translation vectors
    const vec3 TRANSLATION_CAP = {0.0, 0.0, STEM_HEIGHT / 1.2f};

    // Define paths to textures
    const std::string STEM_TEXTURE_PATH = project::path + "assets/stem.jpg";
    const std::string CAP_TEXTURE_PATH = project::path + "assets/cap_porcini.jpg";

    // Create and initialize_snake stem mesh
    mesh stem_porcini_mesh = create_cone_mesh(STEM_RADIUS, STEM_HEIGHT, 0);
    scene.initialize_mesh_with_texture(stem, stem_porcini_mesh, STEM_TEXTURE_PATH);

    // Create and initialize_snake cap mesh
    mesh cap_porcini_mesh = create_sphere_mesh(CAP_RADIUS, TRANSLATION_CAP);
    scene.initialize_mesh_with_texture(cap, cap_porcini_mesh, CAP_TEXTURE_PATH);

    // Add stem and cap to the hierarchy
    hierarchy.add(stem, "stem");
    hierarchy.add(cap, "cap", "stem");
}

void porcini_mushroom::display(scene_structure& scene, const vec3& position){
    // Set the position of the porcini stem
    hierarchy["stem"].transform_local.translation = position;

    // Varying the size of the mushroom for more gamification.
    // In the development project, mushroom collection by the player.
    float scale_factor = 1 + fabs(sin(scene.timer.t + position[2])) / 2.0f;
    hierarchy["stem"].transform_local.scaling = scale_factor;

    // Update the hierarchy and draw the porcini
    hierarchy.update_local_to_global_coordinates();
    draw(hierarchy, scene.environment);
}