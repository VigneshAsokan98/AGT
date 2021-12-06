#pragma once
#include <engine.h>
#include "game_fsm.h"
#include "engine/entities/bounding_box.h"
#include "player.h"
#include "enemy.h"
#include "turret_enemy.h"
#include "hud_manager.h"
#include "cannonball.h"


class gameplay_manager : public game_fsm
{
public :
	gameplay_manager(GameState state);
	~gameplay_manager();

	void init() override;
    void on_update(const engine::timestep& time_step) override;
    void on_render() override;
	void on_event(engine::event& event) override;

private:

	void Init_Spawnpoints();
	void Create_Effects();
	void Create_Environment_Objects();
	void Create_Player();
	void Create_Enemies();
	void Check_Player_Collision(glm::vec3 player_pos);

	engine::ref<engine::skybox>										m_skybox{};
	hud_manager														m_HUD{};
	player															m_player{};
	turret_enemy													m_enemy_player{};
	std::vector <enemy>												m_enemies{};
	engine::ref<engine::text_manager>								m_text_manager{};
	engine::ref<engine::bullet_manager>								m_physics_manager{};
	engine::DirectionalLight										m_directionalLight;

	engine::ref<engine::material>									m_material{};
	engine::ref<engine::material>									m_car_material;


	engine::ref<engine::game_object>								m_terrain{};
	engine::ref<engine::game_object>								m_car{};
	std::vector<engine::ref<engine::game_object>>					m_enemy_objects{};
	std::vector<engine::ref<engine::game_object>>					m_huts{};
	engine::ref<engine::game_object>								m_Health_Pickup{};
	engine::ref<engine::game_object>								m_bullets{};
	std::vector<engine::ref<engine::game_object>>					m_tree{};
	std::vector<engine::ref<engine::game_object>>					m_game_objects{};
	cannonball														m_cannonball;

	engine::bounding_box											m_car_box;
	std::vector<engine::bounding_box>								m_hut_boxes;
	std::vector<engine::bounding_box>								m_tree_boxes;

	engine::perspective_camera										m_3d_camera;

	std::vector<glm::vec3>											m_pickups_Spawnpoints;
	std::vector<glm::vec3>											m_enemy_spawnpoints;

};
