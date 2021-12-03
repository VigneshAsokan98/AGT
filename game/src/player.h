#pragma once
#include <engine.h>
#include "platform/opengl/gl_shader.h"
#include "glm/gtx/rotate_vector.hpp"
#include "Billboard.h"


class player
{

public:
	player();
	~player();
	void initialise(engine::ref<engine::game_object> object);
	void on_update(const engine::timestep& time_step);
	void on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera);
	engine::ref<engine::game_object> object() const { return m_object; }
	void move(engine::timestep _ts);

	bool												m_can_move;

private:
	float m_speed{ 0.f };
	engine::ref< engine::game_object>					m_object;
	engine::SpotLight									m_HeadLight;
	uint32_t											num_Spot_lights = 1;

	engine::ref<engine::material>						m_lightsource_material{};

};
