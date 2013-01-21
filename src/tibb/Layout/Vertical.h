/*
 * Composite.h
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#ifndef VERTICAL_H_
#define VERTICAL_H_

#include "Common.h"
#include "ParseProperty.h"

struct ComputedSize doVerticalLayout(std::vector<struct Element*>, double, double, bool, bool);
void measureNodeForVerticalLayout(struct LayoutProperties, struct Element*);

#endif /* VERTICAL_H_ */
