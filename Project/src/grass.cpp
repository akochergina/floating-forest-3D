#include "grass.hpp"
#include "scene.hpp"
#include "terrain.hpp"


void grass::initialize(scene_structure& scene, int terrain_length) {
    // Generate positions for grass elements
    grass_position = generate_positions_on_terrain(GRASS_QUANTITY, terrain_length * 0.95f, false, false);

    // Define vertices for the grass mesh
    const vec3 BOTTOM_LEFT = {-0.5f, 0.0f, 0.0f};
    const vec3 BOTTOM_RIGHT = {0.5f, 0.0f, 0.0f};
    const vec3 TOP_RIGHT = {0.5f, 0.0f, 1.0f};
    const vec3 TOP_LEFT = {-0.5f, 0.0f, 1.0f};

    // Path to grass texture file
    const std::string TEXTURE_PATH = project::path + "assets/grass.png";

    // Create the grass mesh
    mesh grass_mesh = mesh_primitive_quadrangle(BOTTOM_LEFT, BOTTOM_RIGHT, TOP_RIGHT, TOP_LEFT);
    scene.initialize_mesh_with_texture(grass, grass_mesh, TEXTURE_PATH);

    // Set the initial position of the grass on the terrain
    const float X = 0.0f, Y = 0.0f;
    grass.model.translation = {X, Y, evaluate_terrain_height(X, Y)};

    // Assign the grass shader
    grass.shader = scene.shader_grass;
}

// Get the scaling factor for a grass element based on its index
float grass::get_grass_scaling(int index) const {
    // Define an array of scaling values for the grass
    constexpr std::array<float, 7> SCALING_VALUES = {5.0f, 4.7f, 4.5f, 2.5f, 3.0f, 3.5f, 4.0f};

    // Return the scaling value corresponding to the index
    return SCALING_VALUES[index % SCALING_VALUES.size()];
}


void grass::display(scene_structure &scene) {
    // Retrieve the camera model to compute the right vector
    auto const& camera = scene.camera_control.camera_model;

    // Compute the right vector of the camera to orient the grass
    vec3 const right = camera.right();

    // Compute the rotation transform to align the grass with the camera's right vector
    rotation_transform R = rotation_transform::from_frame_transform(
            {1, 0, 0},  // Original right vector
            {0, 0, 1},  // Original up vector
            right,      // New right vector
            {0, 0, 1}   // New up vector
    );

    // Display each grass element in the scene
    int grass_index = 0;
    for (const vec3& position : grass_position) {
        grass.model.rotation = R;
        grass.model.translation = position;
        grass.model.scaling = get_grass_scaling(grass_index);

        draw(grass, scene.environment);
        ++grass_index;
    }
}
