#include "birch_tree.hpp"
#include "mesh_primitive.hpp"
#include "scene.hpp"
#include "mesh_object.hpp"


void birch_tree::initialize(scene_structure &scene) {
    // Birch foliage has one structure and one color. It is built using a separate function
    // that combines several spheres of different radii. The trunk is built separately due to its distinct structure.

    // Define texture paths for the trunk and foliage
    const std::string TRUNK_TEXTURE_PATH = project::path + "assets/trunk_birch.jpg";
    const std::string FOLIAGE_TEXTURE_PATH = project::path + "assets/foliage_birch.jpg";

    // Define trunk dimensions
    constexpr float TRUNK_RADIUS = 0.2f;
    constexpr float TRUNK_HEIGHT = 2.6f;

    // Initialize the trunk and foliage
    initialize_trunk(scene, trunk, TRUNK_RADIUS, TRUNK_HEIGHT, TRUNK_TEXTURE_PATH);
    initialize_foliage(scene, foliage, TRUNK_HEIGHT, FOLIAGE_TEXTURE_PATH);

    // Add the trunk and foliage to the hierarchy
    hierarchy.add(trunk, "trunk");
    hierarchy.add(foliage, "foliage", "trunk");
}

// Initializing the trunk of the birch tree
void birch_tree::initialize_trunk(scene_structure &scene, mesh_drawable &trunk, float radius, float height,
                                  const std::string &texture_path) {
    // Create and initialize a cylindrical mesh for the trunk
    mesh trunk_mesh = create_cylinder_mesh(radius, height);
    scene.initialize_mesh_with_texture(trunk, trunk_mesh, texture_path);
}


void birch_tree::initialize_foliage(scene_structure &scene, mesh_drawable &foliage, float trunk_height,
                                    const std::string &texture_path) {
    // Create, translate and initialize the foliage mesh
    mesh foliage_mesh = create_foliage_birch();
    foliage_mesh.translate({0, 0, trunk_height / 1.2f});
    scene.initialize_mesh_with_texture(foliage, foliage_mesh, texture_path);

    // Assign the birch shader to the foliage
    foliage.shader = scene.shader_birch;
}


void birch_tree::display(scene_structure &scene, int tree_index, vec3 position) {
    // Set the position of the birch tree's trunk
    hierarchy["trunk"].transform_local.translation = position;

    // Define different scaling factors for varying tree sizes
    constexpr std::array<float, 3> TREE_SCALING = {0.9f, 1.5f, 1.7f};
    hierarchy["trunk"].transform_local.scaling = TREE_SCALING[tree_index % 3];

    // Define rotation angles based on the tree index
    vec3 rotation_axis = {0, 0, 1};
    float rotation_angle = 0.0f;

    switch (tree_index % 4) {
        case 0:
            rotation_angle = position[2];
            break;
        case 1:
            rotation_angle = 4 * position[1] + position[0];
            break;
        case 2:
            rotation_angle = position[2] + 3 * position[0];
            break;
        case 3:
            rotation_angle = position[2] - 2 * position[1] + position[0];
            break;
    }

    // Apply rotation to the tree's trunk
    hierarchy["trunk"].transform_local.rotation = rotation_transform::from_axis_angle(rotation_axis, rotation_angle);

    // Update the hierarchy's global coordinates and draw the tree
    hierarchy.update_local_to_global_coordinates();
    draw(hierarchy, scene.environment);
}
