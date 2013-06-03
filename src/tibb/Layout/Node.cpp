#include "Node.h"

#include <string.h>

#include "Common.h"

#define FLAG_INVALID    0x01  // Node layout properties have been updated since last layout pass.
#define FLAG_REQ_LAYOUT 0x02  // Layout has been request for this node and its children.

void nodeInitialize(struct Node* node) {
    memset(node, 0, sizeof(struct Node));
    node->flags = FLAG_INVALID;
    elementInitialize(&node->element, Composite);
    layoutPropertiesInitialize(&node->properties);
}

void nodeSetLayoutType(struct Node* node, const char* type) {
    if(!strcmp("composite", type)) {
        node->element._layoutType = Composite;
    } else if (!strcmp("horizontal", type)) {
        node->element._layoutType = Horizontal;
    } else if (!strcmp("vertical", type)) {
        node->element._layoutType = Vertical;
    }
}

void nodeAddChild(struct Node* parent, struct Node* child) {
    if (child->parent == parent) {
      return;
    }

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

static void measureNodes(enum LayoutType type, struct Node* node) {
    while(node) {
        // TODO(josh): Clear this flag during layout pass.
        node->flags &= ~FLAG_REQ_LAYOUT;

        if ((node->flags & FLAG_INVALID) == FLAG_INVALID) {
            node->flags &= ~FLAG_INVALID;
            measureNode(type, &node->properties, &node->element);
        }

        if (node->firstChild) {
            measureNodes(node->element._layoutType, node->firstChild);
        }

        node = node->next;
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
    // TODO(josh): remove once layout clears this flag.
    root->flags &= ~FLAG_REQ_LAYOUT;

    if (!root->firstChild) {
        return;
    }

    // Pass 1 - Measure any invalidated child nodes.
    measureNodes(root->element._layoutType, root->firstChild);

    // Pass 2 - Layout out children.
    layoutNode(&root->element,
               root->element._measuredWidth,
               root->element._measuredHeight,
               false,
               false);

    // Pass 3 - Invoke post layout callbacks.
    invokeLayoutCallback(root);
}
