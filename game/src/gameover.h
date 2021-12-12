#pragma once
#include <engine.h>
#include "game_fsm.h"
#include "cross_fade.h"

class quad;

class gameover : public game_fsm
{

public:
	gameover(GameState state);
	~gameover();

	void init() override;
	void on_update(const engine::timestep& time_step) override;
	void on_render() override;
	void on_event(engine::event& event) override;
	void on_disable() override;

private:
	engine::PointLight									m_pointLight;

	engine::ref<engine::material>						m_material{};

	engine::ref<engine::text_manager>					m_text_manager{};

	int													num_point_lights = 1;
	engine::orthographic_camera							m_2d_camera;

	engine::ref<cross_fade>								m_Title{};

	engine::perspective_camera							m_3d_camera;
};
