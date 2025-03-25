#include "cgp/cgp.hpp"
#include "amanite_mushroom.hpp"
#include "mesh_primitive.hpp"
#include "scene.hpp"
#include "mesh_object.hpp"


void amanite_mushroom::initialize(scene_structure &scene) {
    // The mushroom stem and cap have different colors and structures.
    // The stem consists of a "trunk" and a "skirt", created with create_stem_amanite function.

    // Define constants for the mushroom dimensions
    constexpr float STEM_HEIGHT = 0.5f;
    constexpr float CAP_HEIGHT = 0.4f;
    constexpr float CAP_RADIUS = 0.6f;

    // Paths to texture files
    const std::string STEM_TEXTURE_PATH = project::path + "assets/stem.jpg";
    const std::string CAP_TEXTURE_PATH = project::path + "assets/cap_amanite.jpg";

    // Create the stem mesh and apply texture
    mesh stem_amanite_mesh = create_stem_amanite(STEM_HEIGHT);
    scene.initialize_mesh_with_texture(stem, stem_amanite_mesh, STEM_TEXTURE_PATH);

    // Create the cap mesh and apply texture
    mesh cap_amanite_mesh = create_cone_mesh(CAP_RADIUS, CAP_HEIGHT, STEM_HEIGHT);
    scene.initialize_mesh_with_texture(cap, cap_amanite_mesh, CAP_TEXTURE_PATH);

    // Add the stem and cap to the hierarchy
    hierarchy.add(stem, "stem");
    hierarchy.add(cap, "cap", "stem");
}


void amanite_mushroom::display(scene_structure &scene, const vec3 &position) {
    // Set the translation for the stem position
    hierarchy["stem"].transform_local.translation = position;

    // Adjust the size of the mushroom for a dynamic visual effect
    const float SCALE_FACTOR = 1.0f + fabs(sin(scene.timer.t + position[2])) / 2.0f;
    hierarchy["stem"].transform_local.scaling = SCALE_FACTOR;

    // Update hierarchy to global coordinates and draw the mushroom
    hierarchy.update_local_to_global_coordinates();
    draw(hierarchy, scene.environment);
}
