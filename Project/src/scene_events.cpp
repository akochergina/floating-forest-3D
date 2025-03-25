#include "scene_events.hpp"
#include "scene.hpp"


void mouse_move_event(scene_structure& scene) {
    if (!scene.inputs.keyboard.shift)
        scene.camera_control.action_mouse_move(scene.environment.camera_view);
}

void mouse_click_event(scene_structure& scene) {
    scene.camera_control.action_mouse_click(scene.environment.camera_view);
}

void keyboard_event(scene_structure& scene) {
    scene.camera_control.action_keyboard(scene.environment.camera_view);
}
