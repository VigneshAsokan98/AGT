#include "pch.h"
#include "Shield.h"

Shield::Shield(glm::vec3 _color)
{
	m_sphere = engine::sphere::create(15, 30, 1.0f);
	m_material = engine::material::create(0.0f, _color, glm::vec3(0.0f), glm::vec3(0.0f), 0.25f);

}

Shield::~Shield()
{}

void Shield::on_update(const engine::timestep& time_step, glm::vec3 position)
{
	// Program the object to the get larger and change colour over time
	m_scale = 1.f;

	m_position = position;
}

void Shield::on_render(engine::ref<engine::shader> shader)
{
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("lighting_on", false);

	m_material->submit(shader);
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, m_position);
	transform = glm::scale(transform, glm::vec3(m_scale));

	engine::renderer::submit(shader, m_sphere->mesh(), transform);

	std::dynamic_pointer_cast<engine::gl_shader>(shader)->set_uniform("lighting_on", true);

}

void Shield::activate(float radius, glm::vec3 position)
{
	m_position = position;
	m_scale = radius;
}

engine::ref<Shield> Shield::create(glm::vec3 _colour)
{
	return std::make_shared<Shield>(_colour);
}

