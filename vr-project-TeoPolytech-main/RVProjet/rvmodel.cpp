#include "rvmodel.h"

RVModel::RVModel(QString fileName)
    :RVBody(), meshes(), directory(fileName)
{
    directory.makeAbsolute();
    QString filePath = directory.path();
    directory.cdUp();
    loadModel(filePath);
}

void RVModel::loadModel(QString fileName)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(fileName.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << import.GetErrorString() << Qt::endl;
        return;
    }
    // Lance le traitement de tous les noeuds de la scène
    processNode(scene->mRootNode, scene);
    // Stocke le nombre de maillages contenu dans la scène
    nbMeshes = meshes.size();
}

void RVModel::processNode(aiNode* node, const aiScene* scene)
{
    // On parcourt tous les maillages rattachés à ce noeud
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //on convertit mesh qui est une instance de aiMesh
        //en maillage qui est une instance de Mesh
        RVMesh* rvMesh = processMesh(mesh, scene);

        //on récupère l'information de placement de ce noeud
        //pour en faire la matrice world du maillage
        aiMatrix4x4t<float> mat =  node->mTransformation;
        aiVector3t<float> scal;
        aiQuaterniont<float> rot;
        aiVector3t<float> pos;
        mat.Decompose(scal, rot, pos);
        rvMesh->setPosition(QVector3D(pos.x, pos.y, pos.z));

        //on ajoute maillage au tableau des Mesh
        meshes.append(rvMesh);
    }
    //On appelle récursivement la fonction sur tous les fils du noeud
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
        numMaterial++;
    }
}

RVMesh* RVModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
    QVector<RVVertex>* vertices = new QVector<RVVertex>();
    QVector<GLuint>* indices = new QVector<GLuint>();

    //On travaille sur les sommets du aiMesh
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        //Le RVVertex qui va contenir les infos
        RVVertex vertex;

        //On copie les coordonnées
        QVector3D vector;
        vector.setX(mesh->mVertices[i].x);
        vector.setY(mesh->mVertices[i].y);
        vector.setZ(mesh->mVertices[i].z);
        vertex.position = vector;

        //on copie les normales
        QVector3D normal;
        normal.setX(mesh->mNormals[i].x);
        normal.setY(mesh->mNormals[i].y);
        normal.setZ(mesh->mNormals[i].z);
        vertex.normal = normal;

        //on copie les coordonnées textures
        QVector2D tex(0, 0);
        if(mesh->mTextureCoords[0]) // s'il y en a
        {
            tex.setX(mesh->mTextureCoords[0][i].x);
            tex.setY(mesh->mTextureCoords[0][i].y);
        }
        // sinon c'est (0, 0)
        vertex.texCoord = tex;

        //Notre vertex est pret on le met dans le tableau
        vertices->append(vertex);
    }
    //On travaille sur les indices
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices->append(face.mIndices[j]);
    }

    //On construit le Mesh
    RVMesh* rvMesh = new RVMesh();
    rvMesh->setVertices(vertices);
    rvMesh->setIndices(indices);

    //Récupération de la texture
    if(mesh->mMaterialIndex >= 0)
    {
        //On récupère le matériau de l'aiMesh
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex = numMaterial];
        //On en extrait le nom du fihier texture
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE,0, &str);
        //On l'utilise pour initialiser la texture de maillage
        //qDebug() << directory.filePath(str.C_Str());
        rvMesh->setTexture(directory.filePath(str.C_Str()), false, false);
    }
    return rvMesh;
}

void RVModel::draw()
{
    foreach (RVMesh* mesh, meshes) {
        mesh->draw();
    }
}

void RVModel::initializeBuffer()
{
    foreach (RVMesh* mesh, meshes) {
        mesh->initialize();
    }
}

void RVModel::setCamera(RVCamera *camera)
{
    this->camera = camera;
    foreach (RVMesh* mesh, meshes) {
        mesh->setCamera(camera);
    }
}

void RVModel::rotate(float angle, QVector3D axis)
{
    RVBody::rotate(angle, axis);
    foreach (RVMesh* mesh, meshes) {
        mesh->rotate(angle, axis);
    }
}

void RVModel::translate(QVector3D position)
{
    RVBody::translate(position);
    foreach (RVMesh* mesh, meshes) {
        mesh->translate(position);
    }
}

void RVModel::setOrientation(float yaw, float pitch, float roll)
{
    RVBody::setOrientation(yaw, pitch, roll);
    foreach (RVMesh* mesh, meshes) {
        mesh->setOrientation(yaw, pitch, roll);
    }
}

void RVModel::setScale(float newScale)
{
    RVBody::setScale(newScale);
    foreach (RVMesh* mesh, meshes) {
        mesh->setScale(newScale);
    }
}

void RVModel::setLight(RVLight *newLight)
{
    RVBody::setLight(newLight);
    foreach (RVMesh* mesh, meshes) {
        mesh->setLight(newLight);
    }
}

void RVModel::setPosition(const QVector3D &newPosition)
{
    RVBody::setPosition(newPosition);
    foreach (RVMesh* mesh, meshes) {
        mesh->setPosition(newPosition);
    }
}


QMatrix4x4 RVModel::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(position);
    model.rotate(orientation);
    model.scale(scale);
    model.translate(-origin);
    return model;
}

void RVModel::setOrigin(QVector3D pos)
{
    RVBody::setOrigin(pos);
    foreach (RVMesh* mesh, meshes) {
        mesh->setOrigin(pos);
    }
}
