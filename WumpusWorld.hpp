//
//  WumpusWorld.hpp
//  Ai_WumpusWorld
//
//  Created by 陈梓玮 on 2021/4/25.
//

#ifndef WumpusWorld_hpp
#define WumpusWorld_hpp

#include <vector>
#include <iostream>
#include <random>
//#include <queue>
#include <stack>
#include <utility>
//#include <map>

using namespace std;

#define PITNUMBER 3
#define WUMPUSNUMBER 1
#define GOLDNUMBER 1


#define CURRENT_POS     0       // 当前点
#define SAFE            1       // 安全
#define VISITED         2       // 已访问
#define STENCH          3       // 臭气
#define BREEZE          4       // 微风
#define PIT_SUSPECT     5       // 怀疑有陷阱
#define WUMPUS_SUSPECT  6       // 怀疑有怪兽
#define GOLD            7       // 金子,不能被修改
#define PIT             8       // 陷阱，不能被修改
#define WUMPUS          9       // 怪兽，不能被修改

#define GOLD_VALUE      1000      // 金子价值
#define ARROW_COST      -10       //使用箭消耗
#define DEATH_COST      -1000     // 死亡消耗
#define STEP_COST       -1        // 行动消耗
#define POINT pair<int ,int>


struct State{
    vector<bool> state;
    State():state(10,0){}
};

struct Action{
    bool up = 0;
    bool down = 0;
    bool left = 0;
    bool right = 0;
    Action() = default;
    Action(int u, int d, int l, int r):up(u), down(d), left(l), right(r){}
};

struct scoreComp{
    bool operator()(const pair<POINT,int> &p1, const pair<POINT,int> &p2) const{
        return p1.second > p2.second;
    }
};
class WumpusWorld
{
public:
    vector<POINT> pits_pos;//pit所在位置
    POINT wumpus_pos;//wumpus所在位置
    POINT gold_pos;//金币所在位置
    vector<vector<State>> World;//二维矩阵存各个点信息
    int score = 0;
    bool wumpus_find = 0;
    bool gold_find = 0;
    mt19937 e;
//public:
    WumpusWorld():World(4,vector<State>(4,State())) {};
    void gameStart();
    void iniWorld();
    void randomWorldGenerator();
    bool isConflict(int x, int y);//生成地图是用于检查是否重叠
    void putFlag(POINT p, int code);//只能单个置flag
    void DFS(POINT p = POINT(0,0));//基于dfs的联机搜索
    POINT BFS(POINT p);
    void updateSurrdInfo(POINT p);//给出当前所在的节点
    POINT judgeAction(POINT p);//评估根据当前点状态决定最优选择
    int hx(int x, int y);//评估函数
    bool isInside(int x, int y);
    POINT findCurrentPos();
    bool isDead(POINT p);
    bool findGold(POINT p);
    
    //实现逻辑判断
    void wumpus_susp_clear();//如果wumpus找到了则删除所有怀疑的地方
    void clearSusp();//每走一步维护所有sus的点，看看是否能清除
    void comfWumpAndPit();//每走一步维护所有臭气以及微风的点，看看是否能确认四周的wump或pit
    bool isAbleToReach(int x, int y);
    
    vector<POINT> QTPath;
};
#endif /* WumpusWorld_hpp */
