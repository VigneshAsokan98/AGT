#pragma once
#include <engine.h>
#include "cross_fade.h"

class hud_manager
{
public:
	hud_manager();
	~hud_manager();

	void init();
	void on_update(const engine::timestep& time_step, const engine::perspective_camera& camera);
	void on_render(const engine::ref<engine::shader>& shader, engine::camera& camera);
	void SetPlayerHealth(float health) { m_player_health = health; }
	void SetAmmo(int ammo) { m_ammoLeft = ammo; }
	void SetScore(int score) { m_Score = score; }
private:

	engine::ref<cross_fade>								m_crosshair;

	engine::ref<engine::text_manager>					m_text_manager{};


	int													m_ammoLeft = 0;
	int													m_player_health = 100;
	int													m_Score = 0;
};
