#include "Model.h"



Model::Model(std::string const& path, bool isSkyBox, bool gamma) : gammaCorrection(gamma)
{
    loadModel(path);
    if(isSkyBox)
		setLighted(false);
}

Model& Model::operator=(const Model& other) {
	if (this != &other) {

		textures_loaded = other.textures_loaded;
		meshes = other.meshes;
		directory = other.directory;
		gammaCorrection = other.gammaCorrection;
	}
	return *this;
}

void Model::Draw(Shader& shader) {
	shader.use(); // Activate the shader program
	GLuint isLightedLocation = glGetUniformLocation(shader.ID, "isLighted");
    GLuint isTexturedLocation = glGetUniformLocation(shader.ID, "isTextured");
    glUniform1i(isTexturedLocation, 1); // daca obiectul este texturat, atunci trimit 1, altfel 0
    glUniform1i(isLightedLocation, (int)isLighted); // daca obiectul este supus iluminarii, atunci trimit 1, altfel 0
	updateModelMatrix(); // Update the shader with the latest model matrix
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}


/// <summary>
/// Getter of all mesh vertices
/// </summary>
/// <returns></returns>
std::vector<std::vector<Vertex>> Model::GetVerticesOfEachMesh() const {
	std::vector<std::vector<Vertex>> allVertices;
	for (const auto& mesh : meshes) {
		allVertices.push_back(mesh.vertices);
	}
	return allVertices;
}

/// <summary>
/// Setter of all mesh vertices
/// </summary>
/// <param name="newMeshesVertices"></param>
void Model::setMeshesVertices(const std::vector<std::vector<Vertex>>& newMeshesVertices) {
	if (meshes.size() != newMeshesVertices.size()) {
		std::cerr << "Error: Mismatch in number of meshes and vertex sets provided." << std::endl;
		return;
	}

	for (size_t i = 0; i < meshes.size(); ++i) {
		meshes[i].setVertices(newMeshesVertices[i]);
	}
}

void Model::updateModelMatrix() {
	// Get the location of the 'model' uniform in the shader
	GLuint modelMatrixLocation = glGetUniformLocation(shaderProgram, "model");

	// Update the 'model' uniform in the shader with the current modelMatrix
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

/// <summary>
/// Translates model using the dir vector
/// </summary>
/// <param name="dir">direction vector</param>
void Model::translate(glm::vec3 dir) {
	/*glm::vec4 lastColumn = modelMatrix[3];
	modelMatrix = glm::mat4(1.0f);
	modelMatrix[3] = lastColumn;*/

	modelMatrix = glm::translate(modelMatrix, dir); 
	updateModelMatrix();
}


/// <summary>
/// Rotation method for a model using quaternions
/// </summary>
/// <param name="deg"> degrees (0-360) </param>
/// <param name="dir"> direction vector </param>
void Model::rotate(GLfloat deg, glm::vec3 axis) {
	//std::cerr << glm::to_string(modelMatrix) << '\n';
	//std::cerr << "cum rot: " << glm::to_string(cumulativeRotation) << '\n';
	glm::vec3 center = calculateModelCenter();

	float radians = glm::radians(deg);
	glm::quat quaternionRotation = glm::angleAxis(radians, glm::normalize(axis));
	//std::cerr << "quat rot: " << glm::to_string(quaternionRotation) << '\n';

	glm::mat4 translationToCenter = glm::translate(glm::mat4(1.0f), -center);
	glm::mat4 rotationMatrix = glm::toMat4(quaternionRotation);
	glm::mat4 translationBack = glm::translate(glm::mat4(1.0f), center);

	//std::cerr << glm::to_string(translationToCenter) << '\n';
	//std::cerr << glm::to_string(translationBack) << '\n';
	//std::cerr << '\n';

	modelMatrix = translationBack * rotationMatrix * translationToCenter * modelMatrix;

	updateModelMatrix();
}

void Model::scale(GLfloat scaleFactor) {
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFactor, scaleFactor, scaleFactor)); 
	updateModelMatrix();
}

void Model::rotateThenTranslate(GLfloat deg, glm::vec3 axis, glm::vec3 dir)
{
	float radians = glm::radians(deg);
	glm::quat quaternionRotation = glm::angleAxis(radians, glm::normalize(axis));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), dir);

	glm::vec3 center = calculateModelCenter();
	//std::cerr << glm::to_string(center) << '\n';

	glm::mat4 translationToCenter = glm::translate(glm::mat4(1.0f), -center);
	//std::cerr << glm::to_string(translationToCenter) << '\n';
	glm::mat4 translationBack = glm::translate(glm::mat4(1.0f), center);
	//std::cerr << glm::to_string(translationBack) << '\n';
	glm::mat4 rotationMatrix = glm::toMat4(quaternionRotation);
	std::cerr << glm::to_string(rotationMatrix) << '\n';

	modelMatrix = translationMatrix * modelMatrix; // Apply translation
	//std::cerr << glm::to_string(modelMatrix) << '\n';
	modelMatrix = translationBack * rotationMatrix * translationToCenter * modelMatrix; // Apply rotation 

	std::cerr << glm::to_string(modelMatrix) << '\n';
	updateModelMatrix();
}


/// <summary>
/// Computes the center point of a model
/// </summary>
/// <returns></returns>
glm::vec3 Model::calculateModelCenter() const {
	glm::vec3 sum(0.0f, 0.0f, 0.0f);
	int totalVertices = 0;

	for (const auto& mesh : meshes) {
		for (const auto& vertex : mesh.vertices) {
			glm::vec4 transformedPosition = modelMatrix * glm::vec4(vertex.Position, 1.0f);
			sum += glm::vec3(transformedPosition);
		}
		totalVertices += mesh.vertices.size();
	}

	if (totalVertices > 0) {
		sum /= static_cast<float>(totalVertices);
	}

	return sum;
}

void Model::loadModel(std::string const& path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// declaram vectorii care vor tine datele
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// iteram prin fiecare vertex (care are pozitie, normala si coordonate de texturare)
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex{};
		glm::vec3 vector{}; // vector folosit pentru preluarea pozitiilor si a normalelor per vertex
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// normala
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		// coordonate de texturare
		if (mesh->mTextureCoords[0]) // daca mesh-ul din scena contine coordonate de texturare
		{
			glm::vec2 vec{};
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	std::cout << "Loaded " << vertices.size() << " vertices" << std::endl;

	// iteram prin toaete fetele mesh-ului si preluam indicii acestora
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// parcurgem indicii fetei si ii adaugam la vectorul de indici
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	std::cout << "Loaded " << indices.size() << " indices" << std::endl;

	//procesam materialele
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// se incarca texturile diffuse
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// se incarca texturile speculare
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// se incarca normal maps (pentru bump mapping)
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// se incarca height maps (unde este cazul)
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


	// returnam un obiect de tip Mesh format cu datele extrase din scena ASSIMP
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // daca textura a fost incarcata in trecut doar o adaugam in vectorul de texturi
				break;
			}
		}
		if (!skip)
		{   // daca textura nu a mai fost incarcata pana acum, o incarcam
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			std::cout << str.C_Str() << '\n';
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // adaugam textura in vectorul de texturi incarcate pentru a evita incarcarea repetata a aceleiasi texturi
		}
	}
	return textures;
}

void Model::setLighted(bool lightedState)
{
    isLighted = lightedState;
}

unsigned int TextureFromFile(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	std::cout << "Se incarca textura de la path-ul " << path << " si filename " << filename << std::endl;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format{};
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else if (path == nullptr) {
		std::cout << "Pointer null pentru textura data" << std::endl;
		stbi_image_free(data);
	}
	else if (strcmp("*0", path) == 0) {
		std::cout << "Path este *0" << std::endl;
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Textura nu a putut fi incarcata din path-ul: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}