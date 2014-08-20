#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Number_grid.h"
#include "Martrix.h"
using namespace cocos2d;
class Game2048 : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Game2048);
    
    void move(const char* direction);//移动指定方向
    
    void ccTouchesBegan (CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent); // 触摸事件响应函数
    
    ~Game2048();
protected:
    CCArray *grids;//格子的集合
    Martrix *martrix;//用于计算的矩阵
    CCPoint touchBeginPoint;//触摸开始点
    void addNumber(int num,int row,int column);//在指定位置增加一个格子
    void removeNumber(int row, int column);//删除指定位置的格子
    void addNumberInSpace();//在空白处随即增加一个格子
    Number_grid* getGridByPisition(int row,int column);//获取指定位置的格子对象
    void scheduleAdd(float dt);//调度函数的回调函数
    const char* getDirectionByTouchPoints(CCPoint start,CCPoint end);//通过触摸点计算出移动点方向
    bool checkIfMoved(vector<vector<int> >);//对比动作执行前后点矩阵，查看是否移动了
};

#endif
