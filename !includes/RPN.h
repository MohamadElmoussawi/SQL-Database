#pragma once
#include "Token.h"
#include <vector>
#include <algorithm>
#include "../../!includes/Stack And Queue/Stack And Queue/Queue.h"
#include "../../!includes/Stack And Queue/Stack And Queue/Stack.h"
#include "../../B+Tree/B+Tree/Multimap.h"
#include "../../B+Tree/B+Tree/Map.h"
template <typename T>
vector<T> getIntersection(vector<T> v1, vector<T> v2){
    vector<T> v3;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    return v3;
}
template <typename T>
vector<T> getUnion(vector<T> v1, vector<T> v2){
    vector<T> v3;
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
    return v3;
}
class RPN{
public:
	RPN(Queue<Token*> postfix);
    vector<long> get_records(Map<string, int>& fields, vector<MMap<string, long>>& indices);
private:
	Queue<Token*> _postfix;
};

