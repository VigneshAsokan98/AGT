#pragma once
#include <engine.h>
#include "platform/opengl/gl_shader.h"
#include "glm/gtx/rotate_vector.hpp"
class player
{

public:
	player();
	~player();
	void initialise(engine::ref<engine::game_object> object);
	void on_update(const engine::timestep& time_step);
	void on_render(const engine::ref<engine::shader>& shader);
	engine::ref<engine::game_object> object() const { return m_object; }
	void move(engine::timestep _ts);


private:
	float m_speed{ 0.f };
	float m_timer;
	engine::ref< engine::game_object>					m_object;

	engine::SpotLight									m_HeadLight;
	uint32_t											num_Spot_lights = 1;

	glm::vec3											m_Headlight_position;

	engine::ref<engine::material>						m_lightsource_material{};


};
