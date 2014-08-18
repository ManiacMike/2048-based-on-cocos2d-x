//
//  Matrix.h
//  2048
//
//  Created by 张 帆 on 14-4-28.
//
//

#ifndef _048_Martrix_h
#define _048_Martrix_h
#include "vector.h"
#include "cocos2d.h"
using namespace std;

class Martrix :public cocos2d::CCSprite{
public:
    typedef pair<vector<int>, vector<int> > orderedLine;//排队信息
    //返回一个4*4全为0的martrix
    Martrix* initWithZero();
    //移动martrix返回actions
    vector<vector<int> > move(const char* direction);
    //添加数字到martrix
    void addNumberToMartrix(int num,int row ,int column);
    //返回空白处 10,11,41
    vector<int> getSpace();
    
    vector< vector<int> > cur_martrix;
protected:    
    vector< vector<int> > transferMartrix(vector< vector<int> > input_martrix);
    vector< vector<int> > reverseMartrix(vector< vector<int> > input_martrix);
    orderedLine order(vector<int> line);
    void print_martrix(vector< vector<int> >);
};

#endif
