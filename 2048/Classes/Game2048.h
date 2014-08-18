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
    
    void move(const char* direction);
    
    void ccTouchesBegan (CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent); // 触摸事件响应函数
    
    ~Game2048();
protected:
    CCArray *grids;
    Martrix *martrix;
    CCPoint touchBeginPoint;
    void addNumber(int num,int row,int column);
    void removeNumber(int row, int column);
    void addNumberInSpace();
    Number_grid* getGridByPisition(int row,int column);
    void scheduleAdd(float dt);
    const char* getDirectionByTouchPoints(CCPoint start,CCPoint end);
    bool checkIfMoved(vector<vector<int> >);
};

#endif
