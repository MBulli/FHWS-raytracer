#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Vector.h"
#include "PolyObject.h"
#include <map>

struct Face
{
	int data[3][3];

	PropertyPtr material;

	Face(PropertyPtr material = nullptr) : material(material) {}
	int* operator[](int idx)
	{
		return data[idx];
	}
	void reset()
	{
		memset(data, 0, sizeof(int) * 9);
	}

};

typedef std::shared_ptr<std::vector<std::string>> TokensPtr;
typedef std::shared_ptr<std::vector<Face>> FaceListPtr;

class WavefrontObjParser
{
	std::vector<Vector> points;
	std::vector<Vector> texCoords;
	std::vector<Vector> normals;
	std::map<std::string, PropertyPtr> materials;
	std::map<std::string, PropertyPtr> objMaterialBind;
	std::map<std::string, FaceListPtr> faceses;
	FaceListPtr curObjectFaces;
	PropertyPtr curMaterial;

public:
	WavefrontObjParser(const std::string& fileName);

	void objectStart(TokensPtr tokens);
	void parseFile();

	std::vector<PolyObjectPtr> generateGeneratePolyObejekts();
private:
	std::string fileName;
	TokensPtr lineTokens;
	TokensPtr faceTokens;
	Face dummyFace;

	void parseVertex(TokensPtr tokens);
	void parseFace(TokensPtr tokens);
	void parseTexCoord(TokensPtr tokens);
	void parseNormal(TokensPtr tokens);

	void parseMtlFile(std::string mtlFile);

	static void tokenize(const std::string& str, const std::string& delimiter, TokensPtr buffer);
};
