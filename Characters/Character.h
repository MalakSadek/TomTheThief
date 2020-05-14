//
//  Character.h
//  TheProject
//
//  Created by Badr AlKhamissi on 5/6/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __Game__Character__
#define __Game__Character__

#include <stdio.h>
#include <vector>
using namespace std;

class Character{
public:
    bool collision(int);
    int getTileNumber(int,int,int);
    int getTileNumber2(int,int,int);
    void setThingsPos(vector<int>&);
private:
    vector<int>things;
};

#endif /* defined(__TheProject__Character__) */
