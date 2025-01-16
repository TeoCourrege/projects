#include "rvterrain.h"

RVTerrain::RVTerrain(double width): RVSurface()
{
    minS = -width/2;
    maxS = +width/2;
    minT = -width/2;
    maxT = +width/2;
    numSegS = 50;
    numSegT = 50;

    VSFileName = ":/shaders/VS_heightmap.vsh";
}

void RVTerrain::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (this->wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        texture->bind();
    }

    if (heightmap) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE1);
        glActiveTexture(GL_TEXTURE1);
        heightmap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        heightmap->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        heightmap->bind(GL_TEXTURE1);
    }

    program.bind();
    vao.bind();

    //Variables uniformes pour le vertex shader
    program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    program.setUniformValue("u_ViewMatrix", camera->viewMatrix());
    program.setUniformValue("u_ProjectionMatrix", camera->projectionMatrix());
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);
    program.setUniformValue("u_heightmap",1);
    program.setUniformValue("u_facteur",heightFactor);

    //Variables uniformes pour le fragment shader
    program.setUniformValue("texture0", 0);
    program.setUniformValue("light_ambient_color", light->getAmbient());
    program.setUniformValue("light_diffuse_color", light->getDiffuse());
    program.setUniformValue("light_specular_color", light->getSpecular());
    program.setUniformValue("light_specular_strength", specStrength);
    program.setUniformValue("light_position", light->getPositionLight());
    program.setUniformValue("eye_position", camera->getPosition());

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }

    if (heightmap) {
        heightmap->release();
        glDisable(GL_TEXTURE1);
        glDisable(GL_TEXTURE_2D);
    }
}


void RVTerrain::setHeightmap(QString textureFilename)
{
    heightmap = new QOpenGLTexture(QImage(textureFilename).mirrored());
}

float RVTerrain::getHeightFactor() const
{
    return heightFactor;
}

void RVTerrain::setHeightFactor(float newHeightFactor)
{
    heightFactor = newHeightFactor;
}

float RVTerrain::x(double s, double t)
{
    return s;
}

float RVTerrain::y(double s, double t)
{
    return 0;
}
float RVTerrain::z(double s, double t)
{
    return t;
}
