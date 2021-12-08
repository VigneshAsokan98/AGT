#include "player.h"
#include<pch.h>
#include "engine/core/input.h"
#include "engine/key_codes.h"

using namespace engine;

player::player()
{
	m_speed = 5.0f;
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

	//Load Shield mesh
	m_shield = Shield::create(glm::vec3(0.f,0.f,1.f));
	m_shield->activate(1.f, m_object->position());
	//headLights
	m_HeadLight.Color = glm::vec3(1.f, 1.f, 1.f);
	m_HeadLight.AmbientIntensity = 0.2f;
	m_HeadLight.DiffuseIntensity = 0.5f;
	m_HeadLight.Position = glm::vec3(0.0f, 2.0f, 0.0f);
	m_HeadLight.Direction = glm::vec3(1.0f, -1.0f, 0.0f);

	m_lightsource_material = engine::material::create(1.0f, m_HeadLight.Color,
		m_HeadLight.Color, m_HeadLight.Color, 1.0f);
}

void player::on_update(const engine::timestep& time_step)
{
	/*m_object->set_position(m_object->position() += m_object->forward() * m_speed *
		(float)time_step);*/
	update_acceleration(time_step);
	

	//update headlight position
	glm::vec3 Headlight_position = m_object->position() - m_object->forward() * 1.5f;
	m_HeadLight.Position = Headlight_position;
	m_HeadLight.Direction = -m_object->forward();

	//apply coefficient of restitution
	m_object->set_velocity(m_object->velocity() * m_object->restitution());

	m_shield->on_update(time_step, m_object->position());

	if (m_ShieldTimer > 10.f && _isShieldActive)
	{
		_isShieldActive = false;
		m_ShieldTimer = 0;
	}
	if (_isShieldActive)
		m_ShieldTimer += time_step;
}

void player::on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera)
{
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->
		set_uniform("gNumSpotLights", (int)num_Spot_lights);
	m_HeadLight.submit(shader, 0);

	if (_isShieldActive)
		m_shield->on_render(shader);
}

void player::update_acceleration(const engine::timestep& time_step)
{
	glm::vec3 acceleration = m_object->acceleration();
	glm::vec3 velocity = (m_object->velocity() + (m_object->acceleration() + m_instantaneous_acceleration) * (float)time_step);
	m_object->set_velocity(velocity);
	m_object->set_position(m_object->position() + m_object->velocity() * (float)time_step);

	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));

	if (m_can_move)
		move(time_step);

	if (glm::length(m_instantaneous_acceleration) > 0 && m_contact_time > 0.05) {
		m_instantaneous_acceleration = glm::vec3(0.f);
		m_contact_time = 0.f;
	}
	m_contact_time += time_step;
}
void player::move(timestep _ts)
{
	float Threshold = 1.f;
	float currentVelLength = glm::length(m_object->velocity());
	glm::vec3 position = m_object->position();
	if (input::key_pressed(key_codes::KEY_A) && currentVelLength > Threshold) // left
		m_object->set_forward(glm::rotate(m_object->forward(), m_speed * _ts, glm::vec3(0.f, 1.f,0.f)));

	else if (input::key_pressed(key_codes::KEY_D) && currentVelLength > Threshold) // right
		m_object->set_forward(glm::rotate(m_object->forward(), -m_speed * _ts, glm::vec3(0.f, 1.f, 0.f)));

	if (input::key_pressed(key_codes::KEY_S)) // down
	{
		accelerate(-100.f);
		//m_object->set_position(position + m_speed * 10 * _ts * m_object->forward());
	}

	else if (input::key_pressed(key_codes::KEY_W)) // up
	{
		accelerate(100.f);
		//m_object->set_position(position - m_speed * 10 * _ts * m_object->forward());
	}
}
void player::accelerate(float _force)
{
	/*m_object->set_velocity(glm::vec3(0.f));
	m_object->set_torque(glm::vec3(0.f));
	m_object->set_rotation_amount(0.f);
	m_object->set_rotation_axis(glm::vec3(0.f, 1.f, 0.f));
	m_object->set_angular_velocity(glm::vec3(0.f));*/

	//m_object->set_acceleration(glm::vec3(0.f, -9.8f, 0.f));
	m_contact_time = 0.0f;

	glm::vec3 front = m_object->forward();
	
	glm::vec3 force = -front * _force;
	m_instantaneous_acceleration = force / m_object->mass();
}

void player::SetHealth(int _newhealth)
{
	m_playerHealth = _newhealth;
}
void player::ResetAmmo()
{

}
void player::activatePickup(pickup_manager::Type _type)
{
	switch (_type)
	{
	case pickup_manager::Type::Health:
		SetHealth(100);
		break;
	case pickup_manager::Type::Ammo:
		ResetAmmo();
		break;
	case pickup_manager::Type::Shield:
		_isShieldActive = true;
		break;
	default:
		break;
	}
}


