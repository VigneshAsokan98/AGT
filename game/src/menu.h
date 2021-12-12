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
	void on_disable() override;

private:
	enum class Menu_selection {play, exit};

	Menu_selection										m_currentSelection = Menu_selection::play;
	engine::PointLight									m_pointLight;

	engine::ref<engine::material>						m_material{};

	engine::ref<engine::text_manager>					m_text_manager{};

	int													num_point_lights = 1;
	engine::orthographic_camera							m_2d_camera;

	engine::ref<cross_fade>								m_Title{};

	engine::ref<engine::material>						m_lightsource_material{};

	engine::perspective_camera							m_3d_camera;
};
