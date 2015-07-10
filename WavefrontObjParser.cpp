#include "stdafx.h"
#include "WavefrontObjParser.h"
#include <iostream>
#include <fstream>
#include <memory>

const char lineDelimiter = ' ';
const std::string lineDelimiterStr = " ";
const std::string facePartDelimiterStr = "/";

WavefrontObjParser::WavefrontObjParser(const std::string& fileName)
	: fileName(fileName)
{
	faceTokens = std::make_shared<std::vector<std::string>>();
	lineTokens = std::make_shared<std::vector<std::string>>();
}

void WavefrontObjParser::objectStart(TokensPtr tokens)
{
	if (tokens->size() < 2) return;
	curObjectFaces = std::make_shared<std::vector<Face>>();
	faceses[tokens->at(1)] = curObjectFaces;
}

void WavefrontObjParser::parseFile()
{
	std::string line;
	std::ifstream myfile(fileName);
	curObjectFaces = std::make_shared<std::vector<Face>>();
	faceses[fileName.substr(fileName.find_last_of('/') + 1)] = curObjectFaces;

	int linecount = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			linecount++;
			tokenize(line, lineDelimiterStr, lineTokens);
			if (lineTokens->empty()) continue;
			std::string& key = lineTokens->at(0);
			if (key == "v")
			{
				parseVertex(lineTokens);
			}
			else if (key == "f")
			{
				parseFace(lineTokens);
			}
			else if (key == "vt")
			{
				parseTexCoord(lineTokens);
			}
			else if (key == "vn")
			{
				parseNormal(lineTokens);
			}
			else if (key == "o")
			{
				objectStart(lineTokens);
			}
			else if (key == "g")
			{
				objectStart(lineTokens);
			}
			else if (key == "mtllib")
			{
				parseMtlFile(fileName.substr(0, fileName.find_last_of('/') + 1) + lineTokens->at(1));
			}
			else if (key == "usemtl")
			{
				curMaterial = materials[lineTokens->at(1)];
			}
			if (linecount % 100000 == 0)
				std::cout << "processed lines: " << (linecount / 1000) << "k" << std::endl;
		}
		myfile.close();
	}
}

std::vector<PolyObjectPtr> WavefrontObjParser::generateGeneratePolyObejekts()
{
	std::vector<PolyObjectPtr> objects;
	std::vector<TrianglePtr> triangles;
	bool propInit;

	for (std::map<std::string, FaceListPtr>::iterator iterator = faceses.begin(); iterator != faceses.end(); ++iterator) {
		if (iterator->second->empty()) continue;
		propInit = false;
		for (auto& face : *iterator->second)
		{
			if (!points.empty()) {
				TrianglePtr triangle = std::make_shared<Triangle>(points[face.data[0][0] - 1], points[face.data[1][0] - 1], points[face.data[2][0] - 1]);
				/* TODO not implemented
				if (!texCoords.empty())
					triangle->setTextureCoords(texCoords[face.data[0][1] - 1], texCoords[face.data[1][1] - 1], texCoords[face.data[2][1] - 1]);
				if (!normals.empty())
					triangle->setNormals(normals[face.data[0][2] - 1], normals[face.data[1][2] - 1], normals[face.data[2][2] - 1]);
					*/
				if (face.material.get() != nullptr) {
					triangle->setProperty(face.material);
					propInit = true;
				}
				triangles.push_back(triangle);
			}
		}
		objects.push_back(std::make_shared<PolyObject>(iterator->first, triangles /*, propInit */)); // TODO propInit
		triangles.clear();
	}
	return objects;
}

void WavefrontObjParser::parseVertex(TokensPtr tokens)
{
	points.emplace_back(
		stof(tokens->at(1)),
		stof(tokens->at(2)),
		stof(tokens->at(3)));
}

void WavefrontObjParser::parseFace(TokensPtr tokens)
{
	dummyFace.reset();
	int j;
	for (int i = 1; i < tokens->size(); i++)
	{
		j = 0;
		tokenize(tokens->at(i), facePartDelimiterStr, faceTokens);
		for (std::string& subPart : *faceTokens)
		{
			dummyFace[i - 1][j++] = stoi(subPart);
		}
	}
	dummyFace.material = curMaterial;
	curObjectFaces->push_back(dummyFace);
}

void WavefrontObjParser::parseTexCoord(TokensPtr tokens)
{
	texCoords.emplace_back(
		stof(tokens->at(1)),
		stof(tokens->at(2)),
		tokens->size() > 3 ? stof(tokens->at(3)) : 0.0f);
}

void WavefrontObjParser::parseNormal(TokensPtr tokens)
{
	normals.emplace_back(
		stof(tokens->at(1)),
		stof(tokens->at(2)),
		stof(tokens->at(3)));
}

void WavefrontObjParser::parseMtlFile(std::string mtlFile)
{
	std::string line;
	std::ifstream mltFile(mtlFile);

	std::string curName;
	Color curAmbient, curDifuse;
	double curSpecular, curMirror;
	std::string curTextureDefuseFile;


	int linecount = 0;
	if (mltFile.is_open())
	{
		while (getline(mltFile, line))
		{
			linecount++;
			tokenize(line, lineDelimiterStr, lineTokens);
			if (lineTokens->empty()) continue;
			std::string& key = lineTokens->at(0);
			if (key == "newmtl")
			{
				if (!curName.empty())
				{
					materials[curName] = std::make_shared<Property>(curName.c_str(), 
																	curAmbient,
																	curDifuse,
																	curSpecular, 4, // shininess,
																	curMirror, 
																	0.0, 0, // refraction
																	0.0, 0, // glossy
																	0.0 // opacity
																	);
				}
				curName = lineTokens->at(1);
			}
			else if (key == "Ka")
			{
				curAmbient = Color(stod(lineTokens->at(1)), stod(lineTokens->at(2)), stod(lineTokens->at(3)));
			}
			else if (key == "Kd")
			{
				curDifuse = Color(stod(lineTokens->at(1)), stod(lineTokens->at(2)), stod(lineTokens->at(3)));
			}
			else if (key == "Ks")
			{
				curSpecular = stod(lineTokens->at(1));
			}
			else if (key == "map_Kd")
			{
				curTextureDefuseFile = lineTokens->at(1);
			}
		}

		if (!curName.empty())
		{
			materials[curName] = std::make_shared<Property>(curName.c_str(),
				curAmbient,
				curDifuse,
				curSpecular, 4, // shininess,
				curMirror,
				0.0, 0, // refraction
				0.0, 0, // glossy
				0.0 // opacity
				);
			// curTextureDefuseFile TODO

		}

		mltFile.close();
	}
}

void WavefrontObjParser::tokenize(const std::string& str, const std::string& delimiter, TokensPtr buffer)
{
	buffer->clear();
	size_t prevPos = 0;
	for (size_t curPos = str.find(delimiter, prevPos); curPos != std::string::npos; curPos = str.find(delimiter, prevPos))
	{
		buffer->push_back(str.substr(prevPos, curPos - prevPos));
		prevPos = curPos + delimiter.length();;
	}
	if (!str.empty())
		buffer->push_back(str.substr(prevPos, str.length() - prevPos));
}