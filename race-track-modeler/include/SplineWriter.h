#include "Includes.h"

using namespace std;

class SplineWriter {
	private:
		const string FILENAME = "generated-files/spline.txt";
		ofstream splineFile;
		vector<GLfloat>* splineCurvePoints;

		void CreateSplineFile();
		void WriteSplineCurve();

		int GetSplinePointsCount();

	public:
		SplineWriter(vector<GLfloat>* splineCurvePoints);

		void WriteSpline();
};