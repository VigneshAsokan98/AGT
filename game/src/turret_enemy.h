#pragma once
#include <engine.h>
#include "enemy.h"
#include "Billboard.h"

class turret_enemy : public enemy
{
public :
	turret_enemy();
	~turret_enemy();

	void on_update(const engine::timestep& time_step) override;
	void on_render() override;
	void on_event(engine::event& event) override;
private:
	engine::ref< engine::game_object>					m_object;
	engine::ref<Billboard>								m_health_bar;

};