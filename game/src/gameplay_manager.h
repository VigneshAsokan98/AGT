#pragma once
#include <engine.h>
#include "game_fsm.h"
#include "engine/entities/bounding_box.h"
#include "player.h"
#include "turret_enemy.h"
#include "car_enemy.h"
#include "hud_manager.h"
#include "cannonball.h"
#include "pickup_manager.h"


class gameplay_manager : public game_fsm
{
public :
	gameplay_manager(GameState state);
	~gameplay_manager();

	void init() override;
    void on_update(const engine::timestep& time_step) override;
    void on_render() override;
	void on_event(engine::event& event) override;
	int getScore() const { return glm::floor(m_score); }
	inline static float													m_score = 0.f;
	static bool CheckHealth() { return (_playerhealth <= 0); };
private:

	void Init_Spawnpoints();
	void Create_Effects();
	void Create_Environment_Objects();
	void Create_Player();
	void Create_Enemies();
	void Check_Player_Collision(glm::vec3 player_pos);
	void Check_Bullet_collision();
	void FireBullet();
	void checkCannonCollision();
	void Update3dCamera(const engine::timestep& time_step);
	engine::ref<engine::skybox>										m_skybox{};
	hud_manager														m_HUD{};
	player															m_player{};
	pickup_manager													m_pickup_manager{};
	std::vector<turret_enemy>										m_enemy_turrents{};
	std::vector<car_enemy>											m_enemy_cars{};
	engine::ref<engine::text_manager>								m_text_manager{};
	engine::ref<engine::bullet_manager>								m_physics_manager{};
	engine::DirectionalLight										m_directionalLight;
	uint32_t														num_Spot_lights = 4;

	engine::ref<engine::material>									m_material{};
	engine::ref<engine::material>									m_car_material;
	inline static int												_playerhealth = 100;

	engine::ref<engine::game_object>								m_terrain{};
	engine::ref<engine::game_object>								m_car{};
	std::vector<engine::ref<engine::game_object>>					m_enemy_objects{};
	std::vector<engine::ref<engine::game_object>>					m_huts{};
	engine::ref<engine::game_object>								m_bullet{};
	std::vector<engine::ref<engine::game_object>>					m_tree{};
	std::vector<engine::ref<engine::game_object>>					m_game_objects{};
	cannonball														m_cannonball;
	float															m_cannonTimer = 0.f;


	engine::bounding_box											m_Player_box;
	engine::bounding_box											m_Bullet_box;
	engine::bounding_box											m_cannonboll_box;
	std::vector<engine::bounding_box>								m_hut_boxes;
	std::vector<engine::bounding_box>								m_tree_boxes;
	std::vector<engine::bounding_box>								m_Turret_boxes;
	std::vector<engine::bounding_box>								m_Enemycar_boxes;

	engine::perspective_camera										m_3d_camera;
	engine::orthographic_camera										m_2d_camera;

	engine::ref<engine::audio_manager>								m_audio_manager{};

	std::vector<glm::vec3>											m_enemy_spawnpoints;

};
