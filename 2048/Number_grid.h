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
    //区块到位置（1，2）
    CCPoint position;
    //初始化函数 num格子里面到数字  row第几行   column第几列
    static Number_grid* initWithParams(int num,int row,int column);
    CC_SYNTHESIZE(int,number,Number);
    CC_SYNTHESIZE(int,row,Row);
    CC_SYNTHESIZE(int,column,Column);
    CREATE_FUNC(Number_grid);
    //移动  direction方向  actioncode 移动完执行什么处理
    bool move(const char* direction,int actionCode);
protected:
    //由格子的数字获取格子背景颜色
    ccColor4B getColorByNum();
    //由格子的数字获取数字的颜色
    ccColor3B getFontColorByNum();
    //设置新的位置
    void setNewPosition(const char* direction,int distance);
    //删除
    void disappear(CCNode* who);
    //数字加倍
    void doubled();
};


#endif
