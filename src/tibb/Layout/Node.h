#ifndef LAYOUT_NODE_H
#define LAYOUT_NODE_H

#include "Element.h"
#include "ParseProperty.h"

struct Node {
    struct Node *parent;
    struct Node *prev, *next;
    struct Node *firstChild, *lastChild;
    struct Element element;
    struct LayoutProperties properties;
};

void nodeInitialize(struct Node* node);
void nodeAddChild(struct Node* parent, struct Node* child);
void nodeRemoveChild(struct Node* parent, struct Node* child);
void nodeRequestLayout(struct Node* node);

#endif
