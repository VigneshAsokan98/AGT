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
	void on_update(const engine::timestep& time_step, const engine::perspective_camera& camera);
	void on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera);
	engine::ref<engine::game_object> object() const { return m_object; }
	void move(engine::timestep _ts);
	int GetHealth() const { return  m_playerHealth; }
	int getAmmo() const { return  m_ammo; }
	bool GameOver() const { return _isGameOver; };
	void activatePickup(pickup_manager::Type _type);
	void impact(float damage);
	void updateAmmo();
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
	int													m_ammo = 15;
	bool												_isShieldActive = false;
	float												m_ShieldTimer = 0.f;
	bool												_isGameOver = false;

	void accelerate(float _force);
	void update_acceleration(const engine::timestep& time_step, const engine::perspective_camera& camera);

	//powerup Properties
	void SetHealth(int _newhealth);
	void ResetAmmo();
};
