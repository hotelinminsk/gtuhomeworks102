Node* addNode(Node* root, int data) {
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root->data = data;
        root->nextNode = NULL;
        root->prev = NULL;
        return root;
    }

    if (root->data > data) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->nextNode = root;
        newNode->prev = NULL;
        root->prev = newNode;
        root = newNode;
        return root;
    }

    Node* iter = root;
    while (iter->nextNode != NULL && iter->nextNode->data < data) {
        iter = iter->nextNode;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->nextNode = iter->nextNode;
    newNode->prev = iter;
    if (iter->nextNode != NULL) {
        iter->nextNode->prev = newNode;
    }
    iter->nextNode = newNode;

    if (newNode->nextNode == NULL) {
        // Set newNode as the new tail
        newNode->prev = iter;
    }

    return root;
}
