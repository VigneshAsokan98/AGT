#pragma once
#include <engine.h>
#include "platform/opengl/gl_shader.h"
#include "glm/gtx/rotate_vector.hpp"
#include "pickup_manager.h"
#include "Shield.h"

class player
{

public:
	player();
	~player();
	void initialise(engine::ref<engine::game_object> object);
	void on_update(const engine::timestep& time_step);
	void on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera);
	engine::ref<engine::game_object> object() const { return m_object; }
	void move(engine::timestep _ts);
	int GetHealth() const { return  m_playerHealth; }
	bool												m_can_move;
	void activatePickup(pickup_manager::Type _type);

private:
	float m_speed{ 0.f };
	engine::ref< engine::game_object>					m_object;
	engine::SpotLight									m_HeadLight;
	uint32_t											num_Spot_lights = 1;

	engine::ref<engine::material>						m_lightsource_material{};
	glm::vec3											m_instantaneous_acceleration{ 0.f };
	float												m_contact_time;
	int													m_playerHealth = 100;
	engine::ref<Shield>									m_shield{};

	bool												_isShieldActive = false;
	float												m_ShieldTimer = 0.f;

	void accelerate(float _force);
	void update_acceleration(const engine::timestep& time_step);

	//powerup Properties
	void SetHealth(int _newhealth);
	void ResetAmmo();
};
