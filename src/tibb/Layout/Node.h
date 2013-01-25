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
    int flags;

    void(*onLayout)(struct Node*);
    void* data;
};

void nodeInitialize(struct Node* node);
void nodeSetLayoutType(struct Node* node, const char* type);
void nodeAddChild(struct Node* parent, struct Node* child);
void nodeRemoveChild(struct Node* parent, struct Node* child);
struct Node* nodeRequestLayout(struct Node* node);
void nodeLayout(struct Node* root);

#endif
