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
    //当前矩阵
    vector< vector<int> > cur_martrix;
protected:
    //矩阵行和列都倒过来
    vector< vector<int> > transferMartrix(vector< vector<int> > input_martrix);
    //矩阵列倒过来
    vector< vector<int> > reverseMartrix(vector< vector<int> > input_martrix);
    //核心算法，转换那行数字，返回排队后的  数字和action code
    orderedLine order(vector<int> line);
    //打印矩阵
    void print_martrix(vector< vector<int> >);
};

#endif
