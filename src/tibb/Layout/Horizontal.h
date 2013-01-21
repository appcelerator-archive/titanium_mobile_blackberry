/*
 * Composite.h
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#ifndef HORIZONTAL_H_
#define HORIZONTAL_H_

#include "Common.h"
#include "ParseProperty.h"

struct ComputedSize doHorizontalLayout(std::vector<struct Element*>, double, double, bool, bool);
void measureNodeForHorizontalLayout(struct LayoutProperties, struct Element*);

#endif /* HORIZONTAL_H_ */
