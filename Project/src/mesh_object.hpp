#ifndef CGP_MODELING_MESH_OBJECT_HPP
#define CGP_MODELING_MESH_OBJECT_HPP

#include "cgp/cgp.hpp"
#include "mesh_primitive.hpp"


// Creates a mesh for the stem of an amanite mushroom.
cgp::mesh create_stem_amanite(float height_stem);

// Creates a mesh for the foliage of a birch tree.
cgp::mesh create_foliage_birch();

// Creates a mesh for a body of mosquito.
cgp::mesh create_mosquito();

// Creates a mesh for a mosquito wing.
cgp::mesh create_mosquito_wing(bool is_left_wing);

// Creates a mesh for the body of a snake.
cgp::mesh create_snake_body();


#endif // CGP_MODELING_MESH_OBJECT_HPP
