#include "OBJWriter.h"

OBJWriter::OBJWriter(vector<GLfloat>* internalCurvePoints, vector<GLfloat>* externalCurvePoints) {
	this->internalCurvePoints = internalCurvePoints;
	this->externalCurvePoints = externalCurvePoints;
}

void OBJWriter::WriteOBJ() {
	CreateOBJFile();
	
	WriteInternalCurve();
	WriteExternalCurve();
	
	WriteTextureCoordinates();
	WriteVertexNormals();

	WriteFaces();

	WriteMTL();
}

int OBJWriter::GetInternalPointsCount() {
	return this->internalCurvePoints->size();
}

int OBJWriter::GetExternalPointsCount() {
	return this->externalCurvePoints->size();
}

int OBJWriter::GetTotalPointsCount() {
	return (
		this->GetInternalPointsCount() + this->GetExternalPointsCount()
	);
}

void OBJWriter::CreateOBJFile() {
	this->objFile.open(FILENAME, ofstream::out | ofstream::trunc);

	this->objFile << "mtllib " << "mtls/pista.mtl" << "\n" << endl;

	this->objFile.close();
}

void OBJWriter::WriteInternalCurve() {
	this->objFile.open(FILENAME, ios_base::app);

	cout << GetInternalPointsCount() << endl;
	
	for (int i = 0; i < this->GetInternalPointsCount(); i += 3) {
		this->objFile << "v " <<
			this->internalCurvePoints->at(i) << " " <<
			this->internalCurvePoints->at(i + 2) * 100 << " " <<
			this->internalCurvePoints->at(i + 1) << endl;
	}
	
	this->objFile.close();
}

void OBJWriter::WriteExternalCurve() {
	this->objFile.open(FILENAME, ios_base::app);

	cout << GetExternalPointsCount() << endl;

	for (int i = 0; i < this->GetExternalPointsCount(); i += 3) {
		this->objFile << "v " <<
			this->externalCurvePoints->at(i) << " " <<
			this->externalCurvePoints->at(i + 2) * 100 << " " <<
			this->externalCurvePoints->at(i + 1) << endl;
	}
	
	this->objFile.close();
}

void OBJWriter::WriteTextureCoordinates() {
	this->objFile.open(FILENAME, ios_base::app);
	
	this->objFile << endl;
	this->objFile << "vt " << "0.0" << " " << "0.0" << endl;
	this->objFile << "vt " << "1.0" << " " << "0.0" << endl;
	this->objFile << "vt " << "0.0" << " " << "1.0" << endl;
	this->objFile << "vt " << "1.0" << " " << "1.0" << endl;
	this->objFile << endl;
	
	this->objFile.close();
}

void OBJWriter::WriteVertexNormals() {
	this->objFile.open(FILENAME, ios_base::app);

	this->objFile << "vn " << "0.0" << " " << "1.0" << " " << "0.0" << endl;

	this->objFile.close();
}

void OBJWriter::WriteFaces() {
	this->objFile.open(FILENAME, ios_base::app);

	this->objFile << "g " << "pista" << "\n" << endl;
	this->objFile << "usemtl pista" << "\n" << endl;

	for (int i = 1; i <= this->GetInternalPointsCount() / 3 - 1; i++) {
		this->objFile <<
			"f " <<
			i << "/" << 2 << "/" << 1 << " " <<
			i + 1 << "/" << 4 << "/" << 1 << " " <<
			i + (this->GetInternalPointsCount() / 3) << "/" << 3 << "/" << 1 << 
			endl;

		this->objFile <<
			"f " <<
			i + (this->GetInternalPointsCount() / 3) << "/" << 3 << "/" << 1 << " " <<
			i + 1 << "/" << 1 << "/" << 1 << " " <<
			i + 1 + (this->GetInternalPointsCount() / 3) << "/" << 2 << "/" << 1 <<
			endl;
	}

	this->objFile.close();
}

void OBJWriter::WriteMTL() {
	ofstream mtlFile;
	
	mtlFile.open("generated-files/pista.mtl", ofstream::out | ofstream::trunc);

	mtlFile << "newmtl pista" << endl;
	mtlFile << "map_Kd textures/pista.png" << endl;
	mtlFile << "Ka 0.5 0.5 0.5" << endl;
	mtlFile << "Kd 1.0 1.0 1.0" << endl;
	mtlFile << "Ks 1.0 1.0 1.0" << endl;
	mtlFile << "Ns 10" << endl;

	mtlFile.close();
}