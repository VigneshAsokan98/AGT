#pragma once
#include <engine.h>

class pickup_manager
{
public:
	pickup_manager();
	~pickup_manager();
	enum class Type { None, Health, Ammo, Shield};
	void Init();
	void on_update(const engine::timestep& time_step);
	void on_render(const engine::ref<engine::shader>& shader);
	pickup_manager::Type checkCollision(glm::vec3 playerpos);
	void disablePickup();
private:
	void SpawnPickup();
	int																m_spawn_idx = 0;
	engine::ref<engine::game_object>								m_Health_Pickup{};
	engine::ref<engine::game_object>								m_Ammo_Pickup{};
	engine::ref<engine::game_object>								m_Shield_Pickup{};
	engine::PointLight												m_pointLight;
	uint32_t														num_point_lights = 1;

	Type															m_CurrentActive_Pickup = Type::None;
	bool															m_pickup_active = false;
	float															m_timer = 0.f;
	std::vector<glm::vec3>											m_Spawnpoints;
	glm::vec3														m_CurrentPosition;
	int _type = 1;
};
