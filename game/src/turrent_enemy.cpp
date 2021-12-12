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
	m_init_position = m_object->position();
	m_health_bar = Billboard::create("assets/textures/healthBar.png", 1, 1, 1);
	m_explosionFX = Billboard::create("assets/textures/Explosion.png", 8, 6, 12);

	////Load Bullet//Load Bullets(Primitive Shape 2)
	std::vector<glm::vec3> Bullet_vertices;
	Bullet_vertices.push_back(glm::vec3(.5f, .5f, 1.f));	//0
	Bullet_vertices.push_back(glm::vec3(.75f, 0.f, 1.f));	//1
	Bullet_vertices.push_back(glm::vec3(.25f, 0.f, 1.f));	//2
	Bullet_vertices.push_back(glm::vec3(0.f, .5f, 1.f));	//3
	Bullet_vertices.push_back(glm::vec3(.5f, 1.f, 1.f));	//4
	Bullet_vertices.push_back(glm::vec3(1.f, .5f, 1.f));	//5
	Bullet_vertices.push_back(glm::vec3(1.f, .5f, -1.f));	//6
	Bullet_vertices.push_back(glm::vec3(.75f, 0.f, -1.f));	//7
	Bullet_vertices.push_back(glm::vec3(.25f, 0.f, -1.f));	//8
	Bullet_vertices.push_back(glm::vec3(0.f, .5f, -1.f));	//9
	Bullet_vertices.push_back(glm::vec3(.5f, 1.f, -1.f));	//10
	Bullet_vertices.push_back(glm::vec3(.5f, .5f, -1.f));	//11

	engine::ref<engine::Pentagon_prism> Bullet_shape = engine::Pentagon_prism::create(Bullet_vertices);
	std::vector<engine::ref<engine::texture_2d>> Bullet_textures =
	{ engine::texture_2d::create("assets/textures/bullet.bmp", false) };
	engine::game_object_properties Bullet_props;
	Bullet_props.meshes = { Bullet_shape->mesh() };
	Bullet_props.textures = Bullet_textures;
	Bullet_props.scale = { .25f, .25f, .25f };
	Bullet_props.position = { 5.f, 600.f, 6.f };
	m_Bullet_box.set_box(.25f, .25f, .5f, Bullet_props.position);
	m_bullet = engine::game_object::create(Bullet_props);

}
void turret_enemy::on_update(const engine::timestep& time_step, const glm::vec3& player_position)
{
	if (m_respawn)
	{
		m_respawnTimer += time_step;
		if (m_respawnTimer > 20)
			Respawn();
		return;
	}
	float distance_to_player = glm::distance(m_object->position(), player_position);
	m_health_bar->activate(m_object->position() + m_object->up() * 2.f, 2.f * m_health/100, .2f);
	m_health_bar->on_update(time_step);

	m_explosionFX->on_update(time_step);

	m_Bullet_box.on_update(m_bullet->position());

	m_bullet->set_position(m_bullet->position() + m_bullet->velocity() * (float)time_step);

	if (distance_to_player < m_radar_distance)
		m_state = state::Shoot;
	else
		m_state = state::idle;

	switch (m_state)
	{
	case turret_enemy::state::idle:
		face_Player(time_step, player_position);
		break;
	case turret_enemy::state::Shoot:
		face_Player(time_step, player_position);
		m_shootTimer += time_step;
		if (m_shootTimer > 1.f)
		{
			Shoot_player();
		}
		break;
	default:
		break;
	}

}

bool turret_enemy::Check_Bullet_collision(const engine::bounding_box& playerbox)
{
	if (m_respawn)
		return false;
	if (m_Bullet_box.collision(playerbox))
	{
		m_explosionFX->activate(m_bullet->position(), .5f, .5f);
		disableBullet();
		return true;
	}

	return false;
}

void turret_enemy::TakeDamage(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
		DisableEnemy();
}
void turret_enemy::disableBullet()
{
	m_bullet->set_position(glm::vec3(900.f));
	m_bullet->set_velocity(glm::vec3(0.f));
}
void turret_enemy::face_Player(const engine::timestep& time_step, const glm::vec3& player_position)
{
	m_object->set_forward(player_position - m_object->position());
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));
}
void turret_enemy::Shoot_player()
{
	m_bullet->set_position(m_object->position() + glm::vec3(0.f,.5f,0.f));
	m_bullet->set_forward(m_object->forward());
	m_bullet->set_rotation_amount(atan2(m_bullet->forward().x, m_bullet->forward().z));
	m_bullet->set_velocity(m_bullet->forward() * 5.f);
	m_shootTimer = 0;
}
void turret_enemy::on_render(const engine::ref<engine::shader>& shader, const engine::perspective_camera& camera)
{
	if (m_respawn)
		return;
	m_explosionFX->on_render(camera, shader);
	m_health_bar->on_render(camera, shader);
	engine::renderer::submit(shader, m_bullet);
	//m_Bullet_box.on_render(2.5f, 0.f, 0.f, shader);
}
void turret_enemy::Respawn()
{
	m_object->set_position(m_init_position);
	m_respawn = false;
	m_respawnTimer = 0;
	m_health = 100;
}
void turret_enemy::DisableEnemy()
{
	m_respawn = true;
	m_object->set_position(glm::vec3(800.f));
}

