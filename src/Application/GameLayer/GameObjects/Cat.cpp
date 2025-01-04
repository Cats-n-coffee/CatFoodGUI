#include "Cat.h"

Cat::Cat() {}

Cat::Cat(const std::string& name, const std::string& texturePath)
	: m_Name(name), m_TexturePath(texturePath), m_TextureID(0)
{
    Init(name, texturePath);
};

void Cat::Init(const std::string& name, const std::string& texturePath)
{
	if (texturePath.empty()) SetCatTexture("resources/images/CatSprite256.png");
	else SetCatTexture(texturePath);

    SetCatVertices();

    // Set up VAO, VBO and Shader
    m_CatVAO = VAO(1);
    m_CatVAO.Bind();
    m_CatVBO = VBO(1);
    m_CatVBO.Bind();

    m_ShaderProgram = ShaderProgram(
        "resources/shaders/catVertex.shader",
        "resources/shaders/catFragment.shader"
    );
    m_MvpLocation = glGetUniformLocation(m_ShaderProgram.getProgramId(), "modelViewProjection");

    m_CatVBO.PassBufferData(m_Vertices.size() * sizeof(float), m_Vertices);
    m_CatVBO.SpecifyDataLayout(0, 3, 5 * sizeof(float), 0); // positions
    m_CatVBO.SpecifyDataLayout(1, 2, 5 * sizeof(float), 3 * sizeof(float)); // texture

    m_CatVAO.UnBind();
    m_CatVBO.UnBind();
    m_ShaderProgram.UnBind();
}

void Cat::SetCatTexture(const std::string& texture)
{
    m_TexturePath = texture;
    m_TextureID = generateTexture2DPNG(texture);
};

void const Cat::SetCatVertices() // TODO: This should come from a data file
{
    m_Vertices.insert(m_Vertices.end(), {
        //      positions               UV
        // front - triangle 1
        -0.25f, -0.25f, 0.25f,      0.5f, 0.0f, // front - bottom left
        0.25f, -0.25f, 0.25f,       1.0f, 0.0f, // front - bottom right
        0.25f, 0.25f, 0.25f,        1.0f, 0.5f, // front - top right
        // front - triangle 2
        -0.25f, -0.25f, 0.25f,      0.5f, 0.0f, // front - bottom left
        0.25f, 0.25f, 0.25f,        1.0f, 0.5f, // front - top right
        -0.25f, 0.25f, 0.25f,       0.5f, 0.5f, // front - top left
        // left - triangle 1
        -0.25f, -0.25f, -0.25f,     0.5f, 0.5f, // left - bottom back
        -0.25f, -0.25f, 0.25f,      1.0f, 0.5f, // left - bottom front
        -0.25f, 0.25f, 0.25f,       1.0f, 1.0f, // left - top front
        // left - triangle 2
        -0.25f, -0.25f, -0.25f,     0.5f, 0.5f, // left - bottom back
        -0.25f, 0.25f, -0.25f,      0.5f, 1.0f, // left - top back
        -0.25f, 0.25f, 0.25f,       1.0f, 1.0f, // left - top front
        // back - triangle 1
        -0.25f, -0.25f, -0.25f,     0.0f, 0.5f, // back - bottom left
        0.25f, -0.25f, -0.25f,      0.5f, 0.5f, // back - bottom right
        0.25f, 0.25f, -0.25f,       0.5f, 1.0f, // back - top right
        // back - triangle 2
        0.25f, 0.25f, -0.25f,       0.5f, 1.0f, // back - top right
        -0.25f, 0.25f, -0.25f,      0.0f, 1.0f, // back - top left
        -0.25f, -0.25f, -0.25f,     0.0f, 0.5f, // back - bottom left
        // right - triangle 1
        0.25f, -0.25f, -0.25f,      0.5f, 0.0f, // right - bottom back
        0.25f, 0.25f, -0.25f,       0.5f, 0.5f, // right - top back
        0.25f, 0.25f, 0.25f,        0.0f, 0.5f, // right - top front
        // right - triangle 2
        0.25f, 0.25f, 0.25f,        0.0f, 0.5f, // right - top front
        0.25f, -0.25f, 0.25f,       0.0f, 0.0f, // right - bottom front
        0.25f, -0.25f, -0.25f,      0.5f, 0.0f, // right - bottom back
        // top - triangle 1
        -0.25f, 0.25f, 0.25f,       0.0f, 0.0f, // front - top left
        0.25f, 0.25f, 0.25f,        1.0f, 0.0f, // front - top right
        0.25f, 0.25f, -0.25f,       1.0f, 1.0f, // back - top right
        // top - triangle 2
        0.25f, 0.25f, -0.25f,       1.0f, 1.0f, // back - top right
        -0.25f, 0.25f, -0.25f,      0.0f, 1.0f, // back - top left
        -0.25f, 0.25f, 0.25f,       0.0f, 0.0f, // front - top left
        // bottom - triangle 1
        -0.25f, -0.25f, 0.25f,      0.0f, 0.0f, // front - bottom left
        0.25f, -0.25f, 0.25f,       1.0f, 0.0f, // front - bottom right
        0.25f, -0.25f, -0.25f,      1.0f, 1.0f, // back - bottom right
        // bottom - triangle 2
        0.25f, -0.25f, -0.25f,      1.0f, 1.0f, // back - bottom right
        -0.25f, -0.25f, -0.25f,     0.0f, 1.0f, // back - bottom left
        -0.25f, -0.25f, 0.25f,      0.0f, 0.0f, // front - bottom left
    });
};

void Cat::UpdateObject(glm::mat4& orthographicProjection)
{
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.7f, 0.7f, 0.7f));
	glm::mat4 rotation = glm::rotate(glm::radians(m_RotateDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_TranslateVector);
	glm::mat4 modelMatrix = translation * rotation * scale;
	m_ModelViewProjection = orthographicProjection * modelMatrix;
}

void Cat::RenderObject()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glBindVertexArray(m_CatVAO.GetID()); // this is needed here - why? 

	glUseProgram(m_ShaderProgram.getProgramId());
	glUniformMatrix4fv(m_MvpLocation, 1, GL_FALSE, &m_ModelViewProjection[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cat::UpdateBoundingBox(std::vector<glm::vec3>& boundingBox, Direction direction)
{
    for (auto& vertex : boundingBox)
    {
        if (direction == up) vertex.y += 0.1f;
        else if (direction == down) vertex.y -= 0.1f;
        else if (direction == left) vertex.x -= 0.1f;
        else if (direction == right) vertex.x += 0.1f;
    }
}

void Cat::MoveUp()
{
    if (m_BoundingBox[0].y >= 1.0f) return;

	if (m_CatDirection != Direction::up)
	{
		m_RotateDegrees = FACE_UP;
		m_CatDirection = Direction::up;
	}
	m_TranslateVector.y += 0.1f;

    UpdateBoundingBox(m_BoundingBox, Direction::up);
    std::cout << "box " << m_BoundingBox[0].y << std::endl;
}

void Cat::MoveDown()
{
    if (m_BoundingBox[2].y <= -1.0f) return; // might need to revise

	if (m_CatDirection != Direction::down)
	{
		m_RotateDegrees = FACE_DOWN;
		m_CatDirection = Direction::down;
	}
	m_TranslateVector.y -= 0.1f;
    UpdateBoundingBox(m_BoundingBox, Direction::down);
    std::cout << "box " << m_BoundingBox[2].y << std::endl;
}

void Cat::MoveLeft()
{
    if (m_BoundingBox[0].x <= -1.0f) return;

	if (m_CatDirection != Direction::left)
	{
		m_RotateDegrees = FACE_LEFT;
		m_CatDirection = Direction::left;
	}
	m_TranslateVector.x -= 0.1f;
    UpdateBoundingBox(m_BoundingBox, Direction::left);
    std::cout << "box " << m_BoundingBox[0].x << std::endl;
}

void Cat::MoveRight()
{
    if (m_BoundingBox[2].x >= 1.0f) return;

	if (m_CatDirection != Direction::right)
	{
		m_RotateDegrees = FACE_RIGHT;
		m_CatDirection = Direction::right;
	}
	m_TranslateVector.x += 0.1f;
    UpdateBoundingBox(m_BoundingBox, Direction::right);
    std::cout << "box " << m_BoundingBox[2].x << std::endl;
}
