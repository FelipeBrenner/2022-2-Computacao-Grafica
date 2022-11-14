#include "Includes.h"

using namespace std;

class OBJWriter {
	private:
		const string FILENAME = "generated-files/curve.obj";
		ofstream objFile;
		vector<GLfloat>* internalCurvePoints;
		vector<GLfloat>* externalCurvePoints;

		void CreateOBJFile();
		void WriteInternalCurve();
		void WriteExternalCurve();
		void WriteTextureCoordinates();
		void WriteVertexNormals();
		void WriteFaces();
		void WriteMTL();

		int GetInternalPointsCount();
		int GetExternalPointsCount();
		int GetTotalPointsCount();

		void AddFaces(int index, int externalCurveLength, int faces, int n);
		void AddNormalizedExternalCurve(glm::vec3 normal_abac, glm::vec3 normal_dbdc);
		
	public:
		OBJWriter(vector<GLfloat>* internalCurvePoints, vector<GLfloat>* externalCurvePoints);

		void WriteOBJ();
};