#include "player.h"
#include<pch.h>
#include "engine/core/input.h"
#include "engine/key_codes.h"

using namespace engine;

player::player()
{
	m_speed = 1.0f;
	m_can_move = true;
}
player::~player()
{

}

void player::initialise(engine::ref<engine::game_object> object)
{
	m_object = object;
	m_object->set_forward(glm::vec3(0.f, 0.f, 1.f));
	m_object->set_right(glm::vec3(1.f, 0.f, 0.f));
	m_object->set_position(glm::vec3(0.f, .75f, 10.f));

	m_health_bar = Billboard::create("assets/textures/healthBar.png", 1, 1, 1);
	//headLights
	m_HeadLight.Color = glm::vec3(1.f, 1.f, 1.f);
	m_HeadLight.AmbientIntensity = 0.2f;
	m_HeadLight.DiffuseIntensity = 0.5f;
	m_HeadLight.Position = glm::vec3(0.0f, 2.0f, 0.0f);
	m_HeadLight.Direction = glm::vec3(1.0f, -1.0f, 0.0f);

	m_lightsource_material = engine::material::create(1.0f, m_HeadLight.Color,
		m_HeadLight.Color, m_HeadLight.Color, 1.0f);
}


void player::on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera)
{
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->
		set_uniform("gNumSpotLights", (int)num_Spot_lights);
	m_HeadLight.submit(shader, 0);
	//m_health_bar->on_render(camera, shader);
}
void player::on_update(const engine::timestep& time_step)
{
	/*m_object->set_position(m_object->position() += m_object->forward() * m_speed *
		(float)time_step);*/
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));

	if(m_can_move)
		move(time_step);

	//update PlayerHealth
	m_health_bar->activate(m_object->position() + m_object->up() * .75f, 2.f, .2f);
	m_health_bar->on_update(time_step);

	//update headlight position
	glm::vec3 Headlight_position = m_object->position() - m_object->forward() * 1.5f;
	m_HeadLight.Position = Headlight_position;
	m_HeadLight.Direction = -m_object->forward();
}
void player::move(timestep _ts)
{
	glm::vec3 position = m_object->position();
	if (input::key_pressed(key_codes::KEY_A)) // left
		m_object->set_forward(glm::rotate(m_object->forward(), m_speed * _ts * 5, glm::vec3(0.f, 1.f,0.f)));

	else if (input::key_pressed(key_codes::KEY_D)) // right
		m_object->set_forward(glm::rotate(m_object->forward(), -m_speed * _ts * 5, glm::vec3(0.f, 1.f, 0.f)));

	if (input::key_pressed(key_codes::KEY_S)) // down
		m_object->set_position(position + m_speed * 10 * _ts * m_object->forward());

	else if (input::key_pressed(key_codes::KEY_W)) // up
		m_object->set_position(position - m_speed * 10 * _ts * m_object->forward());
}

