#include "Food.h"

Food::Food()
{}

Food::Food(const std::string& texturePath)
{
    Init(texturePath);
}

void Food::Init(const std::string& texturePath)
{
    if (texturePath.empty()) SetFoodTexture("resources/images/FishSprite256.png");
    else SetFoodTexture(texturePath);

    SetVertices();

    m_VAO = VAO(1);
    m_VAO.Bind();
    m_VBO = VBO(1);
    m_VBO.Bind();

    m_ShaderProgram = ShaderProgram(
        "resources/shaders/foodVertex.shader",
        "resources/shaders/foodFragment.shader"
    );
    m_MvpLocation = glGetUniformLocation(m_ShaderProgram.getProgramId(), "modelViewProjection");

    m_VBO.PassBufferData(m_Vertices.size() * sizeof(float), m_Vertices);
    m_VBO.SpecifyDataLayout(0, 3, 5 * sizeof(float), 0); // positions
    m_VBO.SpecifyDataLayout(1, 2, 5 * sizeof(float), 3 * sizeof(float)); // texture

    m_VAO.UnBind();
    m_VBO.UnBind();
    m_ShaderProgram.UnBind();

    TempBoundingBoxTransform();
}

void Food::SetFoodTexture(const std::string& texturePath)
{
    m_FoodTextureID = generateTexture2DPNG(texturePath);
}

void Food::SetVertices()
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
}

void Food::UpdateBoundingBox(std::vector<glm::vec3>& boundingBox, Direction direction)
{
    for (auto& vertex : boundingBox)
    { // update precision
        if (direction == up) vertex.y += 0.1f;
        else if (direction == down) vertex.y -= 0.1f;
        else if (direction == left) vertex.x -= 0.1f;
        else if (direction == right) vertex.x += 0.1f;
    }
}

void Food::TempBoundingBoxTransform()
{ // scale and translate bounding box
    for (auto& vertex : m_BoundingBox)
    {
        vertex.x *= m_ScalingVector.x;
        vertex.y *= m_ScalingVector.y;
        vertex.z *= m_ScalingVector.z;
    }
    for (auto& vertex : m_BoundingBox)
    { // this is wrong
        vertex.x += m_TranslateVector.x;
        vertex.y += m_TranslateVector.y;
        vertex.z += m_TranslateVector.z;
    }
}

void Food::UpdateObject(glm::mat4& orthographicProjection)
{
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_ScalingVector);
// 	glm::mat4 rotation = glm::rotate(glm::radians(m_RotateDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_TranslateVector);
    glm::mat4 modelMatrix = translation * scale;
    m_ModelViewProjection = orthographicProjection * modelMatrix;
}

void Food::RenderObject()
{

	glBindTexture(GL_TEXTURE_2D, m_FoodTextureID);
	glBindVertexArray(m_VAO.GetID());

	glUseProgram(m_ShaderProgram.getProgramId());
	glUniformMatrix4fv(m_MvpLocation, 1, GL_FALSE, &m_ModelViewProjection[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

Food::~Food()
{}