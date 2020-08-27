/*
 * SensorCalibration.h
 *
 * Copyright (C) 2016 Cyrille Potereau
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef SENSORCALIBRATION_H_
#define SENSORCALIBRATION_H_

//#include "YapiBotTypes.h"
#include "../../EigenProj/Eigen/Dense"
//#include "SensorFactory.h"

typedef struct {
	double x;
	double y;
	double z;
} avgAcc_t;

class CSensorCalibration {
public:
	static void runCalibration (float MagAvgs[][3], float AccelAvgs[][3], int rows);
private:
	static Eigen::MatrixXd solve(Eigen::MatrixXd & meas);
	static double partialDerivateOffset (double val, double offset, double scale);
	static double partialDerivateScale (double val, double offset, double scale);
//	static void flushSensors (void);
//	static void measureAndIntegrate (avgAcc_t * avgMagField, avgAcc_t * avgAngRate, avgAcc_t * avgAccel);


};

#endif /* SENSORCALIBRATION_H_ */
