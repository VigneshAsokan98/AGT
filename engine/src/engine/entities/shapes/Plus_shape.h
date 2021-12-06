#pragma once
#pragma once

namespace engine
{
	class mesh;

	class Plus_shape
	{
	public:
		Plus_shape(std::vector<glm::vec3> vertices);
		~Plus_shape();

		std::vector<glm::vec3> vertices() const { return m_vertices; }
		ref<engine::mesh> mesh() const { return m_mesh; }

		static ref<Plus_shape> create(std::vector<glm::vec3> vertices);
	private:

		std::vector<glm::vec3> m_vertices;

		ref<engine::mesh> m_mesh;
	};
}

