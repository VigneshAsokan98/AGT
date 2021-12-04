#include"turret_enemy.h"

turret_enemy::turret_enemy()
{

}
turret_enemy::~turret_enemy()
{

}
void turret_enemy::init(engine::ref<engine::game_object> object)
{
	m_object = object;
	m_object->set_forward(glm::vec3(0.f, 0.f, 1.f));
	m_object->set_right(glm::vec3(1.f, 0.f, 0.f));

	m_health_bar = Billboard::create("assets/textures/healthBar.png", 1, 1, 1);
}
void turret_enemy::on_update(const engine::timestep& time_step)
{
	m_health_bar->activate(m_object->position() + m_object->up() * .75f, 2.f, .2f);
	m_health_bar->on_update(time_step);
}
void turret_enemy::on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera)
{
	m_health_bar->on_render(camera, shader);
}
void turret_enemy::on_event(engine::event& event)
{

}

