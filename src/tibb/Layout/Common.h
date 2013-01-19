/*
 * Common.h
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#ifndef COMMON_H_
#define COMMON_H_

enum LayoutType {composite = 0, horizontal, vertical};
enum ElementAlignment {center = 0, end};

struct ComputedSize {
	double width;
	double height;
};

struct ThreeCoefficients {
	double x1;
	double x2;
	double x3;
};

struct FourCoefficients {
	double x1;
	double x2;
	double x3;
	double x4;
};

struct LayoutCoefficients {
	struct ThreeCoefficients width;
	struct ThreeCoefficients minWidth;
	struct ThreeCoefficients sandboxWidth;
	struct ThreeCoefficients height;
	struct ThreeCoefficients minHeight;
	struct ThreeCoefficients sandboxHeight;
	struct ThreeCoefficients left;
	struct FourCoefficients top;
};

bool isNaN(float);
ComputedSize layoutNode(struct Element*, double, double, bool, bool);

#endif /* COMMON_H_ */
