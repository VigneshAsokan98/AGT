#pragma once
#include <engine.h>
#include "game_fsm.h"
#include "cross_fade.h"

#include "player.h"


class quad;

class menu : public game_fsm
{

public:
	menu(GameState state);
	~menu();

	void init() override;
	void on_update(const engine::timestep& time_step) override;
	void on_render() override;
	void on_event(engine::event& event) override;

private:

	engine::PointLight								m_pointLight;

	engine::ref<engine::material>					m_material{};

	int												num_point_lights = 1;
	engine::orthographic_camera						m_2d_camera;

	engine::ref<cross_fade>							m_cross_fade{};

	engine::ref<engine::material>						m_lightsource_material{};

	engine::perspective_camera						m_3d_camera;
};
