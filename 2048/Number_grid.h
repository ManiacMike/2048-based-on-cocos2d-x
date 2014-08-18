//
//  Number_grid.h
//  2048
//
//  Created by 张 帆 on 14-4-27.
//
//

#ifndef _048_Number_grid_h
#define _048_Number_grid_h
#include "cocos2d.h"
using namespace cocos2d;

class Number_grid : public CCSprite
{
public:
    CCPoint position;
    static Number_grid* initWithParams(int num,int row,int column);
    CC_SYNTHESIZE(int,number,Number);
    CC_SYNTHESIZE(int,row,Row);
    CC_SYNTHESIZE(int,column,Column);
    CREATE_FUNC(Number_grid);
    bool move(const char* direction,int actionCode);
protected:
    ccColor4B getColorByNum();
    ccColor3B getFontColorByNum();
    void setNewPosition(const char* direction,int distance);
    void disappear(CCNode* who);
    void doubled();
};


#endif
