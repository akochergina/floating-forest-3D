#pragma once

#include "scene.hpp"

// Forward declaration of scene_structure
struct scene_structure;

void mouse_move_event(scene_structure& scene);
void mouse_click_event(scene_structure& scene);
void keyboard_event(scene_structure& scene);
