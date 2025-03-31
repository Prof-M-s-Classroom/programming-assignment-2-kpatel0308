#ifndef STORY_H
#define STORY_H

#include <string>
using namespace std;

class Story {
public:
    string description;
    int eventNumber;
    int leftEventNumber;
    int rightEventNumber;

    //  Default constructor (required for GameDecisionTree<T>)
    Story() : eventNumber(-1), description(""), leftEventNumber(-1), rightEventNumber(-1) {}

    // Existing parameterized constructor
    Story(int num, const string& desc, int left, int right)
        : eventNumber(num), description(desc), leftEventNumber(left), rightEventNumber(right) {}
};

#endif
