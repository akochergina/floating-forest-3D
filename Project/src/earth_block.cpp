#include "earth_block.hpp"
#include "mesh_primitive.hpp"
#include "terrain.hpp"
#include "scene.hpp"


void earth_block::initialize(scene_structure &scene, const int terrain_length) {
    // Define the number of samples for the terrain mesh
    constexpr int TERRAIN_SAMPLES_QUANTITY = 100;

    // Define paths to texture files
    const std::string GRASS_TEXTURE_PATH = project::path + "assets/grass.jpg";
    const std::string EARTH_TEXTURE_PATH = project::path + "assets/earth.jpeg";

    // Define the color of the terrain
    const vec3 TERRAIN_COLOR = {0.6f, 0.85f, 0.5f};

    // Initialize the terrain and base mesh with specified parameters
    initialize_terrain(scene, terrain_length, TERRAIN_SAMPLES_QUANTITY, GRASS_TEXTURE_PATH, TERRAIN_COLOR);
    initialize_base(scene, terrain_length, EARTH_TEXTURE_PATH);

    // Add the base and terrain to the hierarchy
    hierarchy.add(base, "base");
    hierarchy.add(terrain, "terrain", "base");
}


void
earth_block::initialize_terrain(scene_structure &scene, const int terrain_length, const int samples_quantity,
                                const std::string &texture_path, const vec3 &color) {
    // Create and initialize the terrain mesh
    mesh terrain_mesh = create_terrain_mesh(samples_quantity, terrain_length);
    scene.initialize_mesh_with_texture_and_color(terrain, terrain_mesh, texture_path, color);
}


void earth_block::initialize_base(scene_structure &scene, const int terrain_length,
                                  const std::string &texture_path) {
    // Create and initialize the base mesh
    mesh base_mesh = create_quadrilateral_pyramid(terrain_length, terrain_length);
    scene.initialize_mesh_with_texture(base, base_mesh, texture_path);
}


void earth_block::display(scene_structure &scene) {
    // Draw the hierarchy in the given scene environment
    draw(hierarchy, scene.environment);
}
