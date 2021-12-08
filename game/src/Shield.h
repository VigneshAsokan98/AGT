#pragma once
#include <engine.h>

class Shield
{
public:
	Shield(glm::vec3 _color);
	~Shield();

	void on_update(const engine::timestep& time_step, glm::vec3 position);
	void on_render(engine::ref<engine::shader> shader);
	void activate(float radius, glm::vec3 position);

	static engine::ref<Shield> create(glm::vec3 _colour);

private:
	glm::vec3 m_position;

	float m_scale;

	glm::vec3								m_colour;
	engine::ref<engine::material>			m_material;
	engine::ref<engine::sphere>				m_sphere;
};
