#include "pickup_manager.h"


pickup_manager::pickup_manager()
{

}
pickup_manager::~pickup_manager()
{

}
void pickup_manager::Init()
{
	//spawn points of Pickups
	m_Spawnpoints.push_back(glm::vec3(5.f, 0.5f, 0.f));
	m_Spawnpoints.push_back(glm::vec3(9.f, 0.5f, -5.f));
	m_Spawnpoints.push_back(glm::vec3(-12.f, 0.5f, 16.f));
	m_Spawnpoints.push_back(glm::vec3(-9.f, 0.5f, -14.f));
	m_Spawnpoints.push_back(glm::vec3(15.f, 0.5f, 7.f));

	//Load Health_Pickup (Primitive Shape 1)
	std::vector<glm::vec3> Health_Pickup_vertices;
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 3.f, 0.f));		//0
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 3.f, 0.f));		//1
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 3.f, 1.f));		//2
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 3.f, 1.f));		//3
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 2.f, 1.f));		//4
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 2.f, 0.f));		//5
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 2.f, 0.f));	//6
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 1.f, 0.f));	//7
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 1.f, 0.f));		//8
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 0.f, 0.f));		//9
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 0.f, 0.f));		//10
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 1.f, 0.f));		//11
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 1.f, 0.f));		//12
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 2.f, 0.f));		//13
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 2.f, 0.f));		//14
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 2.f, 1.f));		//15
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 2.f, 1.f));		//16
	Health_Pickup_vertices.push_back(glm::vec3(2.f, 1.f, 1.f));		//17
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 1.f, 1.f));		//18
	Health_Pickup_vertices.push_back(glm::vec3(1.f, 0.f, 1.f));		//19
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 0.f, 1.f));		//20
	Health_Pickup_vertices.push_back(glm::vec3(0.f, 1.f, 1.f));		//22
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 1.f, 1.f));	//23
	Health_Pickup_vertices.push_back(glm::vec3(-1.f, 2.f, 1.f));	//24

	engine::ref<engine::Plus_shape> Health_Pickup_shape = engine::Plus_shape::create(Health_Pickup_vertices);
	std::vector<engine::ref<engine::texture_2d>> Health_Pickup_textures =
	{ engine::texture_2d::create("assets/textures/Green.bmp", false) };
	engine::game_object_properties Health_Pickup_props;
	Health_Pickup_props.meshes = { Health_Pickup_shape->mesh() };
	Health_Pickup_props.textures = Health_Pickup_textures;
	Health_Pickup_props.scale = { .75f, .75f, .75f };
	Health_Pickup_props.position = { 2, .5f, -5 };
	m_Health_Pickup = engine::game_object::create(Health_Pickup_props);

	//Load Ammo_pickup
	engine::ref <engine::model> Ammo_model = engine::model::create("assets/models/static/box_obj.obj");
	engine::game_object_properties Ammo_props;
	Ammo_props.meshes = Ammo_model->meshes();
	std::vector<engine::ref<engine::texture_2d>> Ammo_Pickup_textures =
	{ engine::texture_2d::create("assets/textures/AmmoBoxDiffuse.png", false) };
	Ammo_props.textures = Ammo_Pickup_textures;
	float Ammo_scale = glm::max(Ammo_model->size().x, glm::max(Ammo_model->size().y, Ammo_model->size().z));
	Ammo_props.position = { 5.f, 4.f, 5.f };
	Ammo_props.scale = glm::vec3(Ammo_scale);
	m_Ammo_Pickup = engine::game_object::create(Ammo_props);

	//Load Shield_pickup
	engine::ref <engine::model> Shield_model = engine::model::create("assets/models/static/Shield.obj");
	engine::game_object_properties Shield_props;
	Shield_props.meshes = Shield_model->meshes();
	Shield_props.textures = Shield_model->textures();
	float Shield_scale = glm::max(Shield_model->size().x, glm::max(Shield_model->size().y, Shield_model->size().z));
	Shield_props.position = { 5.f, 4.f, 5.f };
	Shield_props.scale = glm::vec3(Shield_scale);
	m_Shield_Pickup = engine::game_object::create(Shield_props);

	//headLights
	m_pointLight.Color = glm::vec3(1.f, 1.f, 1.f);
	m_pointLight.AmbientIntensity = 0.2f;
	m_pointLight.DiffuseIntensity = 0.5f;
	m_pointLight.Position = glm::vec3(800.f);

	disablePickup();
}
void pickup_manager::on_update(const engine::timestep& time_step)
{
	m_timer += time_step;
	if (m_timer > 8.f && !m_pickup_active)
	{
		m_pickup_active = true;
		SpawnPickup();
		m_timer = 0.f;
	}
	if (m_timer > 10.f && m_pickup_active)
	{
		m_pickup_active = false;
		disablePickup();
		m_timer = 0.f;
	}

	
}
void pickup_manager::SpawnPickup()
{
	_type++;
	if (_type > 3)
		_type = 1;

	switch ((pickup_manager::Type)_type)
	{
	case pickup_manager::Type::None:
		break;
	case pickup_manager::Type::Health:
		m_Health_Pickup->set_position(m_Spawnpoints.at(m_spawn_idx));
		m_CurrentActive_Pickup = pickup_manager::Type::Health;
		break;
	case pickup_manager::Type::Ammo:
		m_Ammo_Pickup->set_position(m_Spawnpoints.at(m_spawn_idx));
		m_CurrentActive_Pickup = pickup_manager::Type::Ammo;
		break;                                                                                                                                                                                                                                                   
	case pickup_manager::Type::Shield:
		m_Shield_Pickup->set_position(m_Spawnpoints.at(m_spawn_idx));
		m_CurrentActive_Pickup = pickup_manager::Type::Shield;
		break;
	default:
		break;
	}
	m_CurrentPosition = m_Spawnpoints.at(m_spawn_idx);

	m_pointLight.Position = m_CurrentPosition;
	m_spawn_idx++;
	if (m_Spawnpoints.size() <= m_spawn_idx )
		m_spawn_idx = 0;
}
void pickup_manager::disablePickup()
{
	m_Health_Pickup->set_position(glm::vec3(5000.f));
	m_Ammo_Pickup->set_position(glm::vec3(5000.f));
	m_Shield_Pickup->set_position(glm::vec3(5000.f));
	m_pointLight.Position = glm::vec3(800.f);
	m_timer = 0.f;
	m_CurrentActive_Pickup = pickup_manager::Type::None;
}
pickup_manager::Type pickup_manager::checkCollision(glm::vec3 playerpos)
{
	float distance = glm::distance(m_CurrentPosition, playerpos);
	if (distance < 2.f)
	{
		return m_CurrentActive_Pickup;
	}
	return pickup_manager::Type::None;
}
void pickup_manager::on_render(const engine::ref<engine::shader>& shader)
{
	engine::renderer::submit(shader, m_Health_Pickup);
	engine::renderer::submit(shader, m_Ammo_Pickup);
	engine::renderer::submit(shader, m_Shield_Pickup);
	std::dynamic_pointer_cast<engine::gl_shader>(shader)->
		set_uniform("gNumPointLights", (int)num_point_lights);
	m_pointLight.submit(shader, 0);
}
