//busca binária
int size(User* list) { // retorna o tamanho da lista
    int count = 0;
    User* aux = list;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

User* getUserAtIndex(User* list, int index) {
    User* aux = list;
    int count = 0;
    while (aux != NULL && count < index) {
        aux = aux->next;
        count++; 
    }
    return aux; 
}

User* binarySearchUser (User* list, const char* targetName) {
    int left = 0;
    int right = size(list) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        User* midNode = getUserAtIndex(list, mid);

        if (midNode == NULL) {
            return NULL; 
        }

        int comparison = strcmp(midNode->name, targetName);

        if (comparison == 0) {
            return midNode; 
        } else if (comparison < 0) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }

    return NULL; 
}