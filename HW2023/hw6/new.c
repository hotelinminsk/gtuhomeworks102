Product* strctFiller(Product* prdctPointer, int lnC, int featrC, FILE* filePtr) {
    int lineiC = 0;
    int indexCount = 0;
    while (!feof(filePtr)) {
        if (lineiC == 0) {
            char c;
            do {
                c = fgetc(filePtr);
            } while (c != '\n'); // skip the first line
        } else {
            prdctPointer[indexCount].brand = (char*)malloc(MAX_BRAND_NAME * sizeof(char));
            prdctPointer[indexCount].name = (char*)malloc(MAX_PRODUCT_NAME * sizeof(char));
            prdctPointer[indexCount].pid = (int*)malloc(sizeof(int));
            prdctPointer[indexCount].type = (char*)malloc(sizeof(char));
            prdctPointer[indexCount].featurePKey = NULL;
            
            if (featrC > 5) {
                prdctPointer[indexCount].featurePKey = (Feature**)malloc((featrC - 5) * sizeof(Feature*));
                for (int i = 0; i < featrC - 5; i++) {
                    prdctPointer[indexCount].featurePKey[i] = (Feature*)malloc(sizeof(Feature));
                    prdctPointer[indexCount].featurePKey[i]->new_feature_name = (char*)malloc(MAX_FEATURE_NAME * sizeof(char));
                    prdctPointer[indexCount].featurePKey[i]->string_value = (char*)malloc(MAX_FEATURE_VALUE * sizeof(char));
                }
            }
            
            // read the product data from the file
            int count = 0;
            char buffer[MAX_LINE_LENGTH];
            char c = fgetc(filePtr);
            while (c != '\n' && c != EOF) {
                buffer[count++] = c;
                c = fgetc(filePtr);
            }
            buffer[count] = '\0';
            int i = 0;
            count = 0;
            while (buffer[i] != '\0') {
                if (buffer[i] == ',') {
                    count++;
                } else {
                    switch (count) {
                        case 0:
                            prdctPointer[indexCount].pid = (int*)realloc(prdctPointer[indexCount].pid, sizeof(int));
                            *prdctPointer[indexCount].pid = *prdctPointer[indexCount].pid * 10 + buffer[i] - '0';
                            break;
                        case 1:
                            prdctPointer[indexCount].brand[count - 1] = buffer[i];
                            break;
                        case 2:
                            prdctPointer[indexCount].name[count - 1] = buffer[i];
                            break;
                        case 3:
                            *prdctPointer[indexCount].type = buffer[i];
                            break;
                        default:
                            break;
                    }
                    count += 1;
                }
                i += 1;
            }
            indexCount++;
        }
        lineiC++;
    }
    return prdctPointer;
}
