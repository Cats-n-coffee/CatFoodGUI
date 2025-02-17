#include "Tilemap.h"

Tilemap::Tilemap() {}

Tilemap::Tilemap(const std::string& filePath)
    : m_TextureID(0)
{
    Init(filePath);
};

void Tilemap::Init(const std::string& filePath)
{
    m_TextureID = generateTexture2DPNG(filePath);

    // Generate array of vertices
    CreateTileMap();
    
    // Give the data to OpenGL
    m_TilemapVAO = VAO(1);
    m_TilemapVAO.Bind();
    m_TilemapVBO = VBO(1);
    m_TilemapVBO.Bind();

    m_ShaderProgram = ShaderProgram(
        "resources/shaders/foodVertex.shader",
        "resources/shaders/foodFragment.shader");
    m_MvpLocation = glGetUniformLocation(m_ShaderProgram.getProgramId(), "modelViewProjection");

    m_TilemapVBO.PassBufferData(sizeof(float) * 1920, m_VertexAndTexCoords);
    m_TilemapVBO.SpecifyDataLayout(0, 3, 5 * sizeof(float), 0);
    m_TilemapVBO.SpecifyDataLayout(1, 2, 5 * sizeof(float), 3 * sizeof(float));

    m_TilemapVAO.UnBind();
    m_TilemapVBO.UnBind();
    m_ShaderProgram.UnBind();
};

void Tilemap::CreateTileMap()
{
    // OpenGL coords
    float xTopLeft = -1.0f;
    float yTopLeft = 1.0f;

    float tileMapZCoord = -0.5f;
    short offset = 5;
    short coordsPerTile = 30;

    // 2.0 is the length of the range of OpenGL coords (-1, 1)
    float colWidth = 2.0f / m_Cols;
    float rowHeight = 2.0f / m_Rows;

    int i, j;

    for (i = 0; i < m_Rows; i++) {
        for (j = 0; j < m_Cols; j++) {
            // We prob need a third loop or some other way
            int currentIndex = (i * m_Cols) + j;
            std::cout << "current Index/tile number: " << currentIndex << " row: " << i << " col: " << j << std::endl;
            short textureID = tiles[currentIndex];
            std::cout << "texture ID " << textureID << std::endl;
            std::vector<glm::vec2> textureItem = m_TextureTileCoords[textureID];
            // determine vertices and texture coords from index
            // Each tile needs 6 vertices * 5 coords = 30 items
            // We start in the top left corner, at (-1, 1)
            short bottomLeftIdx = 0;
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx * offset) + 0] = xTopLeft + (j * colWidth); // x
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx * offset) + 1] = yTopLeft - ((i + 1) * rowHeight); // y
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx * offset) + 2] = tileMapZCoord; // z

            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx * offset) + 3] = textureItem[3].x; // u
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx * offset) + 4] = textureItem[3].y; // v
            
            // top left - need 5 items
            short topLeftIdx = 1;
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topLeftIdx * offset) + 0] = xTopLeft + (j * colWidth); // x
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topLeftIdx * offset) + 1] = yTopLeft - (i * rowHeight); // y
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topLeftIdx * offset) + 2] = tileMapZCoord; // z

            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topLeftIdx * offset) + 3] = textureItem[0].x; // u
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topLeftIdx * offset) + 4] = textureItem[0].y; // v
            
            // top right
            short topRightIdx = 2;
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx * offset) + 0] = xTopLeft + ((j + 1) * colWidth); // x
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx * offset) + 1] = yTopLeft - (i * rowHeight); // y
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx * offset) + 2] = tileMapZCoord; // z

            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx * offset) + 3] = textureItem[1].x; // u
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx * offset) + 4] = textureItem[1].y; // v
            
            // bottom left
            short bottomLeftIdx2 = 3;
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx2 * offset) + 0] = xTopLeft + (j * colWidth); // x
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx2 * offset) + 1] = yTopLeft - ((i + 1) * rowHeight); // y
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx2 * offset) + 2] = tileMapZCoord; // z

            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx2 * offset) + 3] = textureItem[3].x; // u
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomLeftIdx2 * offset) + 4] = textureItem[3].y; // v

            // bottom right
            short bottomRightIdx = 4;
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomRightIdx * offset) + 0] = xTopLeft + ((j + 1) * colWidth); // x
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomRightIdx * offset) + 1] = yTopLeft - ((i + 1) * rowHeight); // y
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomRightIdx * offset) + 2] = tileMapZCoord; // z

            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomRightIdx * offset) + 3] = textureItem[2].x; // u
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (bottomRightIdx * offset) + 4] = textureItem[2].y; // v
            
            // top right
            short topRightIdx2 = 5;
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx2 * offset) + 0] = xTopLeft + ((j + 1) * colWidth); // x
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx2 * offset) + 1] = yTopLeft - (i * rowHeight); // y
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx2 * offset) + 2] = tileMapZCoord; // z

            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx2 * offset) + 3] = textureItem[1].x; // u
            m_VertexAndTexCoords[(coordsPerTile * currentIndex) + (topRightIdx2 * offset) + 4] = textureItem[1].y; // v
        }
    }
}

void Tilemap::UpdateObject(glm::mat4& orthographicProjection)
{
    m_ModelViewProjection = orthographicProjection;
}

void Tilemap::RenderObject()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glBindVertexArray(m_TilemapVAO.GetID());

    glUseProgram(m_ShaderProgram.getProgramId());
    glUniformMatrix4fv(m_MvpLocation, 1, GL_FALSE, &m_ModelViewProjection[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 384); // 64 tiles * 6 vertices
}
