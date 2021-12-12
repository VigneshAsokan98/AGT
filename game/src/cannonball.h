#pragma once
#include <engine.h>
#include "player.h"
#include "Billboard.h"

class cannonball
{
public:
	cannonball();
	~cannonball();

	void initialise(engine::ref<engine::game_object> object);
	void shoot(const glm::vec3& _position, const glm::vec3& _forward, float kick);
	void on_update(const engine::timestep& time_step);
	void on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera);
	glm::vec3 last_position() const { return m_last_position; }

	bool			m_exploded = false;
	engine::ref<engine::game_object> object() const { return m_object; }

private:
	bool _renderON = false;
	engine::ref<engine::game_object> m_object;

	glm::vec3 m_instantaneous_acceleration{ 0.f };
	glm::vec3 m_instantaneous_angular_acceleration{ 0.f };

	float m_contact_time = 0.0f;

	float m_rotational_inertia = 0.f;

	float m_phi, m_theta;

	glm::vec3 m_last_position{ 0.f };

	engine::ref<Billboard>							m_explosionFX{};

	void UpdatePhysics(const engine::timestep& time_step);
	// Methods to handle collisions with the ground
	bool collision_detection(float y_plane);
	void collision_response(float y_plane);
	void Explode();
};
