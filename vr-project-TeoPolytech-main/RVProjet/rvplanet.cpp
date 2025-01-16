#include "rvplanet.h"

RVPlanet::RVPlanet(double r)
    :RVSphere(r), nightTexture()
{
    VSFileName = ":/shaders/VS_lit_texture.vsh";
    FSFileName = ":/shaders/FS_lit_texture.fsh";
}

void RVPlanet::setNightTexture(QString filename, bool hMirror, bool vMirror)
{
    if (nightTexture)
        delete nightTexture;
    nightTexture = new QOpenGLTexture(QImage(filename).mirrored(hMirror, vMirror));
}

void RVPlanet::draw()
{
    time += 0.05f;

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

    if (nightTexture) {
        glEnable(GL_TEXTURE1);
        glActiveTexture(GL_TEXTURE1);
        nightTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        nightTexture->setMagnificationFilter(QOpenGLTexture::Linear);
        nightTexture->bind(GL_TEXTURE1);
    }

    program.bind();
    vao.bind();
/*
    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);
    program.setUniformValue("u_Daytime", time);*/

    //Variables uniformes pour le vertex shader
    program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    program.setUniformValue("u_ViewMatrix", camera->viewMatrix());
    program.setUniformValue("u_ProjectionMatrix", camera->projectionMatrix());
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);

    //Variables uniformes pour le fragment shader
    program.setUniformValue("texture0", 0);
    program.setUniformValue("light_ambient_color", light->getAmbient());
    program.setUniformValue("light_diffuse_color", light->getDiffuse());
    program.setUniformValue("light_specular_color", light->getSpecular());
    program.setUniformValue("light_specular_strength", specStrength);
    program.setUniformValue("light_position",light->getPositionLight());
    program.setUniformValue("eye_position", camera->getPosition());
    program.setUniformValue("eye_position", camera->getPosition());

    if (texture)
        program.setUniformValue("texture0", 0);
    if (nightTexture)
        program.setUniformValue("texture1", 1);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

    vao.release();
    program.release();

    if (nightTexture) {
        nightTexture->release();
        glDisable(GL_TEXTURE1);
    }

    if (texture) {
        texture->release();
        glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}


