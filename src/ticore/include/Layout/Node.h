/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef LAYOUT_NODE_H
#define LAYOUT_NODE_H

#include "Headers.h"

namespace Ti
{
namespace Layout
{
class TiNode
{
public:

	static void nodeInitialize(struct Node* node);
	static void nodeSetLayoutType(struct Node* node, const char* type);
	static void nodeAddChild(struct Node* parent, struct Node* child);
	static void nodeRemoveChild(struct Node* parent, struct Node* child);
	static struct Node* nodeRequestLayout(struct Node* node);
	static void nodeLayout(struct Node* root);
};
}
}
#endif
