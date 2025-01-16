#include "rvmesh.h"


RVMesh::RVMesh()
    :RVBody()
{
    VSFileName = ":/shaders/VS_lit_texture.vsh";
    FSFileName = ":/shaders/FS_lit_texture.fsh";
}

RVMesh::~RVMesh()
{
    delete vertices;
    delete indices;
}


void RVMesh::setVertices(QVector<RVVertex> *vertices)
{
    this->vertices = vertices;
    this->numVertices = this->vertices->length();
}

void RVMesh::setIndices(QVector<uint> *indices)
{
    this->indices = indices;
    numIndices = this->indices->length();
}


void RVMesh::initializeBuffer()
{
    vbo.bind();
    vbo.allocate(&vertices->at(0), numVertices * sizeof(RVVertex));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.release();

    ibo.bind();
    ibo.allocate(&indices->at(0), numIndices*sizeof (uint));
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.release();
}


void RVMesh::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_CULL_FACE);

    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        //m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        texture->bind();
    }

    program.bind();
    vao.bind();

    program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    program.setUniformValue("u_ViewMatrix", camera->viewMatrix());
    program.setUniformValue("u_ProjectionMatrix", camera->projectionMatrix());
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);
    program.setUniformValue("texture0", 0);

    program.setUniformValue("light_ambient_color", light->getAmbient());
    program.setUniformValue("light_diffuse_color", light->getDiffuse());
    program.setUniformValue("light_specular_color", light->getSpecular());
    program.setUniformValue("light_position", light->getPositionLight());
    program.setUniformValue("light_specular_strength", this->getSpecStrength());

    program.setUniformValue("eye_position", camera->getPosition());

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}
