#include<vector>
#include "SingleField.h"
using std::reference_wrapper;
using std::vector;

struct Dominant {
    int strike;
    char sign;
    vector<reference_wrapper<SingleField>> fields;
};

#pragma once
class VirtualRow {
    vector<reference_wrapper<SingleField>> rowFields;
    int fieldsToPoint;
public:
    VirtualRow(vector<reference_wrapper<SingleField>> rowFields);
    VirtualRow(vector<reference_wrapper<SingleField>> rowFields, int fieldsToPoint);
    Dominant checkRow();
    void setSigns(char sign);
    void resetSigns();
};