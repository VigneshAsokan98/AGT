#pragma once
#pragma once
#include <engine.h>
#include "engine/entities/bounding_box.h"
#include "Billboard.h"

class car_enemy
{
	enum class state
	{
		Wander,
		Chase,
		Shoot
	};
public:
	car_enemy();
	~car_enemy();

	void on_update(const engine::timestep& time_step, const glm::vec3& player_position);
	void init(engine::ref<engine::game_object> object);
	engine::ref<engine::game_object> object() const { return m_object; }
	void on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera);
	bool Check_Bullet_collision(const engine::bounding_box& playerbox);
	void TakeDamage(int damage);
private:
	glm::vec3													m_init_position;
	std::vector<glm::vec3>										m_wanderpoints;

	float														m_shootTimer = 0.f;
	engine::ref< engine::game_object>							m_object;
	engine::ref<Billboard>										m_health_bar;
	int															m_health = 100;
	engine::ref<Billboard>										m_explosionFX{};
	engine::ref<engine::game_object>							m_bullet{};
	engine::bounding_box										m_Bullet_box;
	float														m_radar_distance{ 10.f };
	float														m_Chase_distance{ 20.f };
	float														m_respawnTimer = 0;
	bool														m_respawn = false;
	float														m_default_time{ 2.f };
	float														m_switch_direction_timer = m_default_time;
	float														m_speed = 1.f;

	void face_Player(const engine::timestep& time_step, const glm::vec3& player_position);
	void Wander(const engine::timestep& time_step);
	void Shoot_player();
	void disableBullet();
	void DisableEnemy();
	void Chase(const engine::timestep& time_step, const glm::vec3& player_position);
	void Respawn();
	float random();

	//Current EnemyState
	state m_state = state::Wander;

};
