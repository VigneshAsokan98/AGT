#pragma once
#pragma once

namespace engine
{
	class mesh;

	class Pentagon_prism
	{
	public:
		Pentagon_prism(std::vector<glm::vec3> vertices);
		~Pentagon_prism();

		std::vector<glm::vec3> vertices() const { return m_vertices; }
		ref<engine::mesh> mesh() const { return m_mesh; }

		static ref<Pentagon_prism> create(std::vector<glm::vec3> vertices);
	private:

		std::vector<glm::vec3> m_vertices;

		ref<engine::mesh> m_mesh;
	};
}

