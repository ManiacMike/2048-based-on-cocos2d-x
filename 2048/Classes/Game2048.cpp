#include "Game2048.h"
#include "SimpleAudioEngine.h"
#include "Number_grid.h"
#include "Martrix.h"
#include "vector.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* Game2048::scene()
{
    CCScene *scene = CCScene::create();
    
    Game2048 *layer = Game2048::create();
    scene->addChild(layer);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor *bg = CCLayerColor::create();
    bg->initWithColor(ccc4(255, 255, 255, 255));
    
    CCSprite *bgImg = CCSprite::create("2048bg.png");
    bgImg->setScale(0.5f);
    bgImg->setPosition( ccp(size.width/2, size.height/2) );
    bg->addChild(bgImg);
    
    CCLabelTTF* pLabel = CCLabelTTF::create("2048 By Mike", "Thonburi", 30);
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    pLabel->setColor(ccc3(0, 0, 0));
    bg->addChild(pLabel, 1);
    
    scene->addChild(bg,-1);
    
    return scene;
}

bool Game2048::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    martrix = new Martrix;
    martrix->initWithZero();
    grids = new CCArray;
    //随即添加两个数
    this->addNumberInSpace();
    this->addNumberInSpace();
    this->setTouchEnabled(true);
    touchBeginPoint = ccp(0,0);
    return true;
}

void Game2048::addNumber(int num, int row, int column){
    Number_grid *grid = Number_grid::initWithParams(num, row, column);
    //显示
    this->addChild(grid);
    grids->addObject(grid);
    
}
void Game2048::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    if(pTouches->count() == 1){
        CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
        CCPoint position = touch->getLocationInView();
        position = CCDirector::sharedDirector()->convertToGL(position);
        touchBeginPoint = position;
    }
}
void Game2048::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    if(pTouches->count() == 1 && (touchBeginPoint.x !=0 || touchBeginPoint.y !=0) ){
        CCTouch* touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
        CCPoint position = touch->getLocationInView();
        position = CCDirector::sharedDirector()->convertToGL(position);
        CCLOG("x:%f,y:%f",touchBeginPoint.x,touchBeginPoint.y);
        const char* direction = this->getDirectionByTouchPoints(touchBeginPoint, position);
        if(strcmp(direction, "invalid") != 0){
            this->move(direction);
        }        
    }
    touchBeginPoint = ccp(0,0);
}
const char* Game2048::getDirectionByTouchPoints(CCPoint start,CCPoint end){
    float x = end.x - start.x;
    float y = end.y - start.y;
    CCLOG("x:%f,y:%f",end.x,end.y);
    float abx = x<0?(x*-1):x;
    float aby = y<0?(y*-1):y;
    const char*direction = "invalid";
    if(abx >aby && abx>100){//right or left
        direction = x>0?"right":"left";
    }else if(abx<aby && aby>100){//up or down
        direction = y>0?"up":"down";
    }
    CCLOG("%s",direction);
    return direction;
}

void Game2048::removeNumber(int row, int column){
    Number_grid* grid = this->getGridByPisition(row, column);
    grid->removeFromParentAndCleanup(true);
    CCObject* igrid = (CCObject*) grid;
    grids->removeObject(igrid);
}

//up down left right
void Game2048::move(const char* direction){
    //move the martrix
    vector<vector<int> > actions = martrix->move(direction);
    if (this->checkIfMoved(actions) == false) {//没动
        return;
    }
    CCObject *igrid;
    CCArray *gridDelete = new CCArray;
    CCARRAY_FOREACH(grids, igrid){
        Number_grid* grid = (Number_grid*) igrid;
        int actionCode = actions[4-grid->getRow()][grid->getColumn()-1];
        bool res = grid->move(direction,actionCode);
        if(res == false){
            gridDelete->addObject(igrid);
        }
    }
    CCARRAY_FOREACH(gridDelete,igrid){
        grids->removeObject(igrid);
    }
    this->scheduleOnce(schedule_selector(Game2048::scheduleAdd), 0.45f);
}
void Game2048::scheduleAdd(float dt){
    this->addNumberInSpace();
}
void Game2048::addNumberInSpace(){
    vector<int> space = martrix->getSpace();
    if(space.size() == 0)
        return;
    int randNum = space.at(rand()%space.size());
    int column = randNum%10;
    int row = (randNum-column)/10;
    int showNum = (rand()%2+1)*2;
    martrix->addNumberToMartrix(showNum, row, column);
    this->addNumber(showNum, row, column);
}
Number_grid* Game2048::getGridByPisition(int row,int column){
    CCObject *igrid;
    CCARRAY_FOREACH(grids, igrid){
        Number_grid* grid = (Number_grid*) igrid;
        if (grid->getRow() == row && grid->getColumn() == column) {
            return grid;
            break;
        }
    }
}

Game2048::~ Game2048(){
    if(grids != NULL){
        grids->release();
    }
    if(martrix != NULL){
        martrix->release();
    }
}

bool Game2048::checkIfMoved(vector<vector<int> > actions){
    vector<int> vec(4);
    vector<vector<int> > vecs(4,vec);
    return (actions != vecs);
}