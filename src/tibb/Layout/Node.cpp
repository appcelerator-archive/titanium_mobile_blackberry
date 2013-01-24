#include "Node.h"

#include <string.h>

#include "Common.h"
#include "Composite.h"

void nodeInitialize(struct Node* node) {
    memset(node, 0, sizeof(struct Node));
    elementInitialize(&node->element, Composite);  // TODO(josh): expose layout type
    layoutPropertiesInitialize(&node->properties);
}

void nodeAddChild(struct Node* parent, struct Node* child) {
    child->parent = parent;
    if (parent->lastChild) {
        child->prev = parent->lastChild;
        parent->lastChild->next = child;
    } else {
        parent->firstChild = child;
    }
    parent->lastChild = child;

    parent->element._children.push_back(&child->element);
}

void nodeRemoveChild(struct Node* parent, struct Node* child) {
    child->parent = 0;
    if (child->prev) {
        child->prev->next = child->next;
    } else {
        parent->firstChild = child->next;
    }
    if (child->next) {
        child->next->prev = child->prev;
    } else {
        parent->lastChild = child->prev;
    }

    // TODO(josh): remove element from parent
}

void nodeRequestLayout(struct Node* node) {
    measureNodeForCompositeLayout(node->properties, &node->element);

    while (node->parent) {
      node = (Node*) node->parent;
    }

    layoutNode(&node->element,
               node->element._measuredWidth,
               node->element._measuredHeight,
               false,
               false);
}

