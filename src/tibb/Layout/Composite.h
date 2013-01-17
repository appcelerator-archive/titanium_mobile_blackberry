/*
 * Composite.h
 *
 *  Created on: Dec 3, 2012
 *      Author: rmcmahon
 */

#ifndef COMPOSITE_H_
#define COMPOSITE_H_

#include "Common.h"
#include "ParseProperty.h"

struct ComputedSize doCompositeLayout(struct Element*, double, double, bool, bool);
void measureNodeForCompositeLayout(struct LayoutProperties, struct Element*);

#endif /* COMPOSITE_H_ */
