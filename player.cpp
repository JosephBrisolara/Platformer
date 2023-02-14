#include "player.h"

#include "world.h"

constexpr double walk_acceleration = 800;
constexpr double terminal_velocity = 200;
constexpr double jump_velocity = 150;
constexpr double gravity = 100;
constexpr double damping = 0.9;

Player::Player(const Vec<double>& position, const Vec<int>& size)
    : position{position}, size{size} {
    acceleration.y = gravity;
}

void Player::handle_input(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        if (key == SDLK_RIGHT) {
            acceleration.x = walk_acceleration;
            // velocity.x = terminal_velocity;
        } else if (key == SDLK_LEFT) {
            acceleration.x = -walk_acceleration;
            // velocity.x = -terminal_velocity;
        } else if (key == SDLK_SPACE) {
            velocity.y = -jump_velocity;
            acceleration.y = gravity;
        }
    }
    if (event.type == SDL_KEYUP) {
        SDL_Keycode key = event.key.keysym.sym;
        if (key == SDLK_RIGHT) {
            acceleration.x = 0;
            // velocity.x = 0;
        } else if (key == SDLK_LEFT) {
            acceleration.x = 0;
            // velocity.x = 0;
        } else if (key == SDLK_SPACE) {
        }
    }
}

void Player::update(World& world, double dt) {
    // Make copy of physics components
    Vec<double> vel = velocity;
    Vec<double> acc = acceleration;
    Vec<double> pos = position;

    // Semi-implicit euler
    vel += acc * dt;
    vel.x *= damping;

    // Terminal Velocity Check
    vel.x = std::clamp(vel.x, -terminal_velocity, terminal_velocity);
    vel.y = std::clamp(vel.y, -terminal_velocity, terminal_velocity);

    pos += vel * dt;

    // Test x intersection first
    SDL_Rect future{static_cast<int>(pos.x), static_cast<int>(position.y),
                    size.x, size.y};

    if (world.has_any_intersections(future)) {
        // Collided: stop velocity and acceleration
        velocity.x = 0;
        acceleration.x = 0;
    } else {
        position.x = pos.x;
        velocity.x = vel.x;
        acceleration.x = acc.x;
    }

    // Test y intersection first
    future.x = static_cast<int>(position.x);
    future.y = static_cast<int>(pos.y);
    if (world.has_any_intersections(future)) {
        acceleration.y = 0;
        velocity.y = 0;
    } else {
        acceleration.y = acc.y;
        velocity.y = vel.y;
        position.y = pos.y;
    }
}

std::pair<SDL_Rect, Color> Player::get_sprite() const {
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);
    SDL_Rect bounding_box{x, y, size.x, size.y};
    return {bounding_box, {255, 0, 0, 255}};
}
