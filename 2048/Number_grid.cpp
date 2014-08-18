//
//  Number_grid.cpp
//  2048
//
//  Created by 张 帆 on 14-4-27.
//
//

#include "Number_grid.h"
//#include "cocos2d.h"

using namespace cocos2d;

Number_grid* Number_grid::initWithParams(int num, int row, int column){
//    CCLOG("%d,%d",row,column);
    Number_grid *one = Number_grid::create();
    one->setNumber(num);
    one->setRow(row);
    one->setColumn(column);
    //500 107 15 14
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float gridWidth = 107;
    float gridHeight = 107;
    float x = (size.width/2 - 500.0/4) + (15 + (gridWidth+14)*(column-1))/2;

    float y = (size.height/2 - 500.0/4) + (15 + (gridHeight+14)*(row-1))/2;
    CCLayerColor *grid = CCLayerColor::create();
    grid->initWithColor(one->getColorByNum());
    one->setPosition(ccp(x, y));
    grid->setContentSize(CCSize(gridWidth/2, gridHeight/2));
    grid->setTag(1);
    one->position = ccp(x, y);
    one->addChild(grid,0);
    
    CCString *numS = CCString::createWithFormat("%d",num);
    const char *s = numS->getCString();
    CCLabelTTF* pLabel = CCLabelTTF::create(s, "Clear Sans", 40);
    CCSize pSize = pLabel->getContentSize();
    pLabel->setPosition(ccp(gridWidth/4, gridHeight/4));
    pLabel->setColor(one->getFontColorByNum());
    pLabel->setTag(2);
    one->addChild(pLabel, 1);
    return one;
};

ccColor4B Number_grid::getColorByNum(){
    switch (this->number) {
        case 2:
            return ccc4(238, 228, 218,255);
        case 4:
            return ccc4(237, 224, 200,255);
        case 8:
            return ccc4(242, 177, 121,255);
        case 16:
            return ccc4(245, 149, 99,255);
        case 32:
            return ccc4(246, 124, 95,255);
        case 64:
            return ccc4(246, 94, 59,255);
        case 128:
            return ccc4(237, 207, 114,255);
        case 256:
            return ccc4(237, 207, 114,255);
        default:
            return ccc4(100, 100, 100,255);
            break;
    }
    
}
ccColor3B Number_grid::getFontColorByNum(){
    if(this->number == 2 || this->number == 4){
        return ccc3(119, 110, 101);
    }else{
        return ccc3(255, 255, 255);
    }
}

bool Number_grid::move(const char* direction,int actionCode){
    CCLOG("actionCode:%d|row%d,coloumn%d",actionCode,this->row,this->column);
    int distance = 0;
    float speed = 0.15f;
    if(actionCode < 0){//move and disappear
        distance = -1 - actionCode;
        if(distance > 0){
            this->setNewPosition(direction, distance);
            CCMoveTo *move = CCMoveTo::create(speed*distance, position);
            CCCallFuncN *disappear = CCCallFuncN::create(this, callfuncN_selector(Number_grid::disappear));
            CCSequence *actions = CCSequence::create(move,disappear,NULL);
            this->runAction(actions);
        }else{
            CCCallFuncN *disappear = CCCallFuncN::create(this, callfuncN_selector(Number_grid::disappear));
            this->runAction(disappear);
        }
        return false;//需要处理删除
    }else if (actionCode > 0 && actionCode<5){//just move
        distance = actionCode;
        this->setNewPosition(direction, distance);
        CCMoveTo *move = CCMoveTo::create(speed*distance, position);
        this->runAction(move);
    }else if (actionCode > 9){//move and duoble
        distance = actionCode%10;
        int delay = (actionCode-actionCode%10)/10-1;
        CCLOG("DELAY:%d,actioncode%d",delay,actionCode);
        if(distance > 0){
            this->setNewPosition(direction, distance);
            CCMoveTo *move = CCMoveTo::create(speed*distance, position);
            this->runAction(move);
        }
        this->scheduleOnce(schedule_selector(Number_grid::doubled), speed*delay);
    }
    return true;
}
void Number_grid::disappear(CCNode* who){
    who->removeFromParentAndCleanup(true);
}
void Number_grid::doubled(){
    this->setNumber(number*2);
    CCNode* layerNode = this->getChildByTag(1);
    layerNode->removeFromParentAndCleanup(true);
    CCLayerColor* layer = CCLayerColor::create();
    float gridWidth = 107;
    float gridHeight = 107;
    layer->initWithColor(this->getColorByNum());
    layer->setContentSize(CCSize(gridWidth/2, gridHeight/2));
    layer->setTag(1);
    this->addChild(layer,0);
    CCNode* labelNode = this->getChildByTag(2);
    CCLabelTTF *label = (CCLabelTTF*) labelNode;
    label->setColor(this->getFontColorByNum());
    CCString *numS = CCString::createWithFormat("%d",this->number);
    const char *s = numS->getCString();
    label->setString(s);
}
void Number_grid::setNewPosition(const char* direction,int distance){
    if(strcmp(direction,"up") == 0){
        row+=distance;
        position = ccp(position.x,position.y + 60.5*distance);
    }else if(strcmp(direction,"down") == 0){
        row-=distance;
        position = ccp(position.x,position.y - 60.5*distance);
    }else if(strcmp(direction,"right") == 0){
        column+=distance;
        position = ccp(position.x + 60.5*distance,position.y);
    }else{
        column-=distance;
        position = ccp(position.x - 60.5*distance,position.y);
    }
}