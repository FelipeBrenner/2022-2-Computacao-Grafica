#include "SplineWriter.h"

SplineWriter::SplineWriter(vector<GLfloat>* splineCurvePoints) {
	this -> splineCurvePoints = splineCurvePoints;
}

void SplineWriter::WriteSpline() {
	CreateSplineFile();
	WriteSplineCurve();
}

int SplineWriter::GetSplinePointsCount() {
	return this -> splineCurvePoints -> size();
}

void SplineWriter::CreateSplineFile() {
	this -> splineFile.open(FILENAME, ofstream::out | ofstream::trunc);

	this -> splineFile.close();
}

void SplineWriter::WriteSplineCurve() {
	this -> splineFile.open(FILENAME, ios_base::app);
		
	for (int i = 0; i < this -> GetSplinePointsCount(); i += 3) {
		this -> splineFile << "v " <<
			this -> splineCurvePoints -> at(i) << " " <<
			this -> splineCurvePoints -> at(i + 2) * 100 << " " <<
			this -> splineCurvePoints -> at(i + 1) << endl;
	}
	
	this -> splineFile.close();
}
