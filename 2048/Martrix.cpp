//
//  Martrix.cpp
//  2048
//
//  Created by 张 帆 on 14-4-28.
//
//
#include "cocos2d.h"
#include "Martrix.h"
#include "vector.h"
#include "iterator.h"
using namespace std;
typedef pair<vector<int>, vector<int> > orderedLine;
Martrix* Martrix::initWithZero(){
    CCLOG("init martrix");
    vector<int> ivec(4,0);
    vector<vector<int> > vecs(4,ivec);
    this->cur_martrix = vecs;
    return this;
}

void Martrix::addNumberToMartrix(int num,int row ,int column){
    cur_martrix[4-row][column-1] = num;
}

vector<int> Martrix::getSpace(){
    vector<int> space;
    vector<vector<int> >::iterator itr = cur_martrix.begin();
    int i = 0;
    while (itr != cur_martrix.end()){
        int j = 0;
        vector<int> ivec = *itr;
        vector<int>::iterator itr2 = ivec.begin();
        while (itr2 != ivec.end()) {
            if (*itr2 == 0) {
                space.push_back((4-i)*10+j+1);
            }
            itr2++;
            j++;
        }
        itr++;
        i++;
    }
    return space;
}
//返回动作和组合后的顺序，重力面在前
orderedLine Martrix::order(vector<int> line){
//    CCLOG("orderLine::%d,%d,%d,%d",line[0],line[1],line[2],line[3]);
    int drop = 0;
    //pair<mode,drop>  0为无动作，1为消失，2为double,两数合并前面的数double
    vector<pair<int, int> > actions;
    vector<int> newline(4);
    int lastNotZeroIndex = -1;
    for (int i = 0;i<4;i++){
        pair<int, int> action;
        if(line[i]>0){
            if(lastNotZeroIndex != -1 && line[lastNotZeroIndex] == line[i]){//前面存在整数
                action = make_pair(1, drop);
                actions[lastNotZeroIndex].first = 2;//前面的数标记为double
                drop++;
                lastNotZeroIndex = -1;
            }else{
                action = make_pair(0, drop);
            }
            lastNotZeroIndex = i;
        }else if (line[i] == 0){
            drop++;
            action = make_pair(0, 0);
        }
        actions.push_back(action);
	}
    pair<vector<int>, vector<int> > res;
    vector<int> actionCodes(4);
    for (int i =0; i<4; i++) {
        pair<int, int> action = actions[i];
        if (action.first == 0) {
            actionCodes[i] = action.second;
            newline[i-action.second] = line[i];
        }else if (action.first == 1){
            actionCodes[i] = -1 - action.second;
        }else{
            //get delay
            int delay = 0;
            for (int j=i+1; j<4; j++) {
                if(actions[j].first == 1){
                    delay = actions[j].second;
                    break;
                }
            }
            actionCodes[i] = 10 + action.second + delay*10;
            newline[i-action.second] = line[i]*2;
        }
    }
//   CCLOG("action::%d,%d,%d,%d",actionCodes[0],actionCodes[1],actionCodes[2],actionCodes[3]);
    res = make_pair(newline, actionCodes);
    return res;
}

vector< vector<int> > Martrix::transferMartrix(vector< vector<int> > input_martrix){
    vector<int> vec(4);
    vector<vector<int> > newVec(4,vec);
    for (int i =0;i<4;i++){
		for (int j=0;j<4;j++){
            newVec[j][i] = input_martrix[i][j];
        }
    }
    return newVec;
}
vector< vector<int> > Martrix::reverseMartrix(vector< vector<int> > input_martrix){
    vector<int> vec(4);
    vector<vector<int> > newVec(4,vec);
    for (int i =0;i<4;i++){
		for (int j=0;j<4;j++){
            newVec[i][j] = input_martrix[i][3-j];
        }
    }
    return newVec;
}
// 0 2 2 0 => 4 0 0 0
vector<vector<int> > Martrix::move(const char* direction){
    vector<vector<int> > tmp_martrix;
    if(strcmp(direction,"up") == 0){
		tmp_martrix = this->transferMartrix(cur_martrix);
	}else if(strcmp(direction,"down") == 0){
		tmp_martrix = this->transferMartrix(cur_martrix);
		tmp_martrix = this->reverseMartrix(tmp_martrix);
	}else if(strcmp(direction,"right") == 0){
		tmp_martrix = this->reverseMartrix(cur_martrix);
	}else{
        tmp_martrix = cur_martrix;
    }
    vector<int> vec(4);
    vector<vector<int> > newVec(4,vec);
    vector<vector<int> > actions(4,vec);
    for (int i=0;i<4;i++){
		orderedLine res = this->order(tmp_martrix[i]);
		newVec[i] = res.first;
		actions[i] = res.second;
	}
//    this->print_martrix(newVec);
    if(strcmp(direction,"up") == 0){
		cur_martrix = this->transferMartrix(newVec);
		actions = this->transferMartrix(actions);
	}else if(strcmp(direction,"down") == 0){
		cur_martrix = this->reverseMartrix(newVec);
		cur_martrix = this->transferMartrix(cur_martrix);
		actions = this->reverseMartrix(actions);
		actions = this->transferMartrix(actions);
	}else if(strcmp(direction,"right") == 0){
		cur_martrix = this->reverseMartrix(newVec);
		actions = this->reverseMartrix(actions);
	}else{
		cur_martrix = newVec;
	}
//    this->print_martrix(cur_martrix);
    return actions;
}

void Martrix::print_martrix(vector< vector<int> > vecs){
    CCLOG("cur_martrix::\n");
    for (int i = 0; i<4; i++) {
        CCLOG("%d %d %d %d\n",vecs[i][0],vecs[i][1],vecs[i][2],vecs[i][3]);
        
    }
}