#include "Node.h"

#include <string.h>

#include "Common.h"
#include "Composite.h"

#define FLAG_INVALID    0x01  // Node layout properties have been updated since last layout pass.
#define FLAG_REQ_LAYOUT 0x02  // Layout has been request for this node and its children.

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

    addChildElement(&parent->element, &child->element);
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

    removeChildElement(&parent->element, &child->element);
}

struct Node* nodeRequestLayout(struct Node* node) {
    node->flags |= FLAG_INVALID;

    while (true) {
        if ((node->flags & FLAG_REQ_LAYOUT) == FLAG_REQ_LAYOUT) {
            return NULL;
        }
        node->flags |= FLAG_REQ_LAYOUT;
        if (!node->parent) {
            break;
        }
        node = node->parent;
    }

    return node;
}

static void measureNode(struct Node* node) {
    // TODO(josh): move into layout pass?
    node->flags &= ~FLAG_REQ_LAYOUT;

    if ((node->flags & FLAG_INVALID) == FLAG_INVALID) {
        node->flags &= ~FLAG_INVALID;
        measureNodeForCompositeLayout(node->properties, &node->element); // TODO(josh): support other layout types
    }

    struct Node* child = node->firstChild;
    while (child) {
        measureNode(child);
        child = child->next;
    }
}

static void invokeLayoutCallback(struct Node* node) {
    if (node->onLayout) {
        node->onLayout(node);
    }

    struct Node* child = node->firstChild;
    while (child) {
        invokeLayoutCallback(child);
        child = child->next;
    }
}

void nodeLayout(struct Node* root) {
    struct Node* parent;

    // Pass 1 - measure any invalid nodes
    measureNode(root);

    // Pass 2 - layout nodes
    layoutNode(&root->element,
               root->element._measuredWidth,
               root->element._measuredHeight,
               false,
               false);

    // Pass 3 - Invoke layout callbacks
    invokeLayoutCallback(root);
}
