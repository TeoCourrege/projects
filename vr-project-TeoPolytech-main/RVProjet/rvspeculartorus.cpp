#include "rvspeculartorus.h"

RVSpecularTorus::RVSpecularTorus()
    :RVTorus()
{
    FSFileName = ":/shaders/FS_lit_specular_cube.fsh";
}



void RVSpecularTorus::setCubeTexture(QString leftImage, QString rightImage, QString frontImage, QString backImage, QString topImage, QString bottomImage)
{
    texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    texture->create();

    // enregistrer les images au bon format
    QImage posX = QImage(rightImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negX = QImage(leftImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posY = QImage(topImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negY = QImage(bottomImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posZ = QImage(frontImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negZ = QImage(backImage).convertToFormat(QImage::Format_RGBA8888);

    // définir la taille de la texture
    texture->setSize(posX.width(),posX.height(),posX.depth());

    // définir le format
    texture->setFormat(QOpenGLTexture::RGBA8_UNorm);

    // allouer en mémoire un espace suffisant
    texture->allocateStorage();

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           posX.constBits(),
                           Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           negX.constBits(),
                           Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           posY.constBits(),
                           Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           negY.constBits(),
                           Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           posZ.constBits(),
                           Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           negZ.constBits(),
                           Q_NULLPTR);

    // générer les niveaux de mipmap
    texture->generateMipMaps();

    // réglages de l'échantillonage
    texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->generateMipMaps();
}


void RVSpecularTorus::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (texture) {
        glEnable(GL_TEXTURE_CUBE_MAP);
        glEnable(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        texture->bind();
    }

    program.bind();
    vao.bind();

    //Variables uniformes pour le vertex shader
    program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    program.setUniformValue("u_ViewMatrix", camera->viewMatrix());
    program.setUniformValue("u_ProjectionMatrix", camera->projectionMatrix());
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);

    //Variables uniformes pour le fragment shader
    program.setUniformValue("texture0", 0);
    program.setUniformValue("skybox", 0);
    program.setUniformValue("light_ambient_color", light->getAmbient());
    program.setUniformValue("light_diffuse_color", light->getDiffuse());
    program.setUniformValue("light_specular_color", light->getSpecular());
    program.setUniformValue("light_specular_strength", specStrength);
    program.setUniformValue("light_position",light->getPositionLight());
    program.setUniformValue("eye_position", camera->getPosition());

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_CUBE_MAP);
    }

}

/*    glEnable(GL_BLEND);
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

    program.bind();
    vao.bind();

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


    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }*/
