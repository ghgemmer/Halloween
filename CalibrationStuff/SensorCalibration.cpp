/*
 * SensorCalibration.cpp
 *
 * Copyright (C) 2016 Cyrille Potereau
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "SensorCalibration.h"
#include <math.h>
//#include <SensorFactory.h>
#include <cstdlib>

#define MAX_ITERATION 200
#define LIMIT_CONV_FUNCT 0.0
#define LIMIT_CONV_ROOT 0.0

#define NUM_SAMPLE_AVERAGE 500.0
#define NUM_MEASURE 500


using namespace Eigen;



void CSensorCalibration::runCalibration (float MagAvgs[][3], float AccelAvgs[][3], int rows)
{
	MatrixXd MeasAccel(6,3);
	MatrixXd MeasCompass(6,3);

        for (int i = 0; i< 6; i++)
        {
            for (int j = 0; j< 3; j++)
            {
                MeasAccel(i,j) = AccelAvgs[i][j];
                MeasCompass(i,j) = MagAvgs[i][j];
            }
        }
        
	MatrixXd compassAlign = solve (MeasCompass);
	MatrixXd accelAlign = solve (MeasAccel);
        
        printf("Calculated Biases as follows:\n");
        printf("Mag x offset bias: %f\n", compassAlign(0,0));
        printf("Mag y offset bias: %f\n", compassAlign(1,0));
        printf("Mag z offset bias: %f\n", compassAlign(2,0));
        printf("Mag x scale bias: %f\n", compassAlign(3,0));
        printf("Mag y scale bias: %f\n", compassAlign(4,0));
        printf("Mag z scale bias: %f\n", compassAlign(5,0));
        printf("Accel x offset bias: %f\n", accelAlign(0,0));
        printf("Accel y offset bias: %f\n", accelAlign(1,0));
        printf("Accel z offset bias: %f\n", accelAlign(2,0));
        printf("Accel x scale bias: %f\n", accelAlign(3,0));
        printf("Accel y scale bias: %f\n", accelAlign(4,0));
        printf("Accel z scale bias: %f\n", accelAlign(5,0));


}

#if 0
void CSensorCalibration::flushSensors (void)
{
	CCompass * compass = CSensorFactory::getInstance()->getCompass();
	CAccelerometer * accel = CSensorFactory::getInstance()->getAccelerometer();
	CGyroscope	* gyro = CSensorFactory::getInstance()->getGyroscope();

	if (compass != NULL)
	{
		while (compass->magFieldAvailable())
		{
			compass->getMagField();
		}
	}
	if (gyro != NULL)
	{
		while (gyro->angRateSamplesAvailable())
		{
			gyro->getAngularRate();
		}
	}
	if (accel != NULL)
	{
		while (accel->accelSamplesAvailable())
		{
			accel->getAccel();
		}
	}

}


void CSensorCalibration::measureAndIntegrate (avgAcc_t * avgMagField, avgAcc_t * avgAngRate, avgAcc_t * avgAccel)
{
	sMagField magField;
	sAccel acc;
	sAngularRate angRate;

	double magFieldAccX = 0, magFieldAccY = 0, magFieldAccZ = 0;
	double accelAccX = 0, accelAccY = 0, accelAccZ = 0;
	//double angRateAccX = 0, angRateAccY = 0, angRateAccZ = 0,

	CCompass * compass = CSensorFactory::getInstance()->getCompass();
	CAccelerometer * accel = CSensorFactory::getInstance()->getAccelerometer();
	CGyroscope	* gyro = CSensorFactory::getInstance()->getGyroscope();

	//Start measuring and integrating.
	for (int i = 0; i < NUM_MEASURE; i++)
	{
		if (compass != NULL)
		{
			//Wait for measurement to be available.
			while (!compass->magFieldAvailable());
			magField = compass->getMagField();
			magFieldAccX += (double)magField.x / NUM_SAMPLE_AVERAGE;
			magFieldAccY += (double)magField.y / NUM_SAMPLE_AVERAGE;
			magFieldAccZ += (double)magField.z / NUM_SAMPLE_AVERAGE;
		}
		if (gyro != NULL)
		{
			//Wait for measurement to be available.
			while (!gyro->angRateSamplesAvailable());
			angRate = gyro->getAngularRate();
			avgAngRate->x += (double)angRate.x / (NUM_SAMPLE_AVERAGE*6);
			avgAngRate->y += (double)angRate.y / (NUM_SAMPLE_AVERAGE*6);
			avgAngRate->z += (double)angRate.z / (NUM_SAMPLE_AVERAGE*6);
		}
		if (accel != NULL)
		{
			//Wait for measurement to be available.
			while (!accel->accelSamplesAvailable());
			acc = accel->getAccel();
			accelAccX += (double)acc.x / NUM_SAMPLE_AVERAGE;
			accelAccY += (double)acc.y / NUM_SAMPLE_AVERAGE;
			accelAccZ += (double)acc.z / NUM_SAMPLE_AVERAGE;
		}
	}
	avgMagField->x = magFieldAccX;
	avgMagField->y = magFieldAccY;
	avgMagField->z = magFieldAccZ;
	avgAccel->x = accelAccX;
	avgAccel->y = accelAccY;
	avgAccel->z = accelAccZ;


}
#endif

double CSensorCalibration::partialDerivateOffset (double val, double offset, double scale)
{
	double ret =  2.0 * (val * scale + offset);
	return ret;
}

double CSensorCalibration::partialDerivateScale (double val, double offset, double scale)
{
	double ret =  2.0 * (val * val * scale + val * offset);
	return ret;
}

MatrixXd CSensorCalibration::solve (MatrixXd & Meas)
{
	MatrixXd jacobian(6,6);
	MatrixXd X(6,1);
	MatrixXd F(6,1);
	int32_t iter;

	//Init solution
	X << 0.0, 0.0, 0.0, 1.0, 1.0, 1.0;

	for (iter = 0; iter < MAX_ITERATION; iter++)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				jacobian(i,k) = partialDerivateOffset(Meas(i,k),X(k,0),X(3+k,0));
				jacobian(i,3+k) = partialDerivateScale(Meas(i,k),X(k,0),X(3+k,0));
			}
		}
		//std::cout << "Jacobian:" << std::endl << jacobian << std::endl;
		for (int i = 0; i < 6; i++)
		{
			F(i,0) = pow(Meas(i,0)*X(3,0) + X(0,0), 2) + pow(Meas(i,1)*X(4,0) + X(1,0), 2) + pow(Meas(i,2)*X(5,0) + X(2,0), 2) - 1;
		}

		/*if (abs(F.sum()) <= LIMIT_CONV_FUNCT)
		{
			break;
		}*/
		//std::cout << "F:" << std::endl << F << std::endl;

		MatrixXd Xd = jacobian.lu().solve(-F);

		/*if (abs(Xd.sum()) <= LIMIT_CONV_ROOT)
		{
			break;
		}*/
		//std::cout << "Xd:" << std::endl << Xd << std::endl;

		X = X + Xd;

		//std::cout << "X:" << std::endl << X << std::endl;

	}
	return X;

}
