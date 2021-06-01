//
//  WumpusWorld.cpp
//  Ai_WumpusWorld
//
//  Created by 陈梓玮 on 2021/4/25.
//

#include "WumpusWorld.hpp"

void WumpusWorld::iniWorld()
{
    World.clear();
    World.resize(4,vector<State>(4,State()));
    pits_pos.clear();
    randomWorldGenerator();
    //case 1
//    //暂时生成一个固定的世界,也即书上199页的那个
//    World[0][0].state[CURRENT_POS] = 1;
//    World[0][1].state[BREEZE] = 1;
////    World[0][2].state[PIT] = 1;
//    World[0][3].state[BREEZE] = 1;
//    World[1][0].state[STENCH] = 1;
//    World[1][2].state[BREEZE] = 1;
////    World[2][0].state[WUMPUS] = 1;
//    World[2][1].state[BREEZE] = 1;
////    World[2][1].state[GOLD] = 1;
//    World[2][1].state[STENCH] = 1;
////    World[2][2].state[PIT] = 1;
//    World[2][3].state[BREEZE] = 1;
//    World[3][0].state[STENCH] = 1;
//    World[3][2].state[BREEZE] = 1;
////    World[3][3].state[PIT] = 1;
//
//    pits_pos.push_back(POINT(0,2));
//    pits_pos.push_back(POINT(2,2));
//    pits_pos.push_back(POINT(3,3));
//    wumpus_pos.first = 2;   wumpus_pos.second = 0;
//    gold_pos.first = 2; gold_pos.second = 1;
    
    
    //case 2 起始点在 2 3
//    World[2][3].state[CURRENT_POS] = 1;
//    World[0][0].state[BREEZE] = 1;
//    World[0][2].state[BREEZE] = 1;
//    World[2][0].state[BREEZE] = 1;
//    World[1][3].state[BREEZE] = 1;
//
//    World[2][1].state[STENCH] = 1;
//    World[3][2].state[STENCH] = 1;
//    World[3][0].state[STENCH] = 1;
//    World[3][2].state[BREEZE] = 1;
//
//    pits_pos.push_back(POINT(1,0));
//    pits_pos.push_back(POINT(0,3));
//    pits_pos.push_back(POINT(3,0));
//    wumpus_pos.first = 3;   wumpus_pos.second = 1;
//    gold_pos.first = 1; gold_pos.second = 1;
    
    //case 3 起始点
}
void WumpusWorld::putFlag(POINT p, int code)
{
    World[p.first][p.second].state[code] = 1;
}
void WumpusWorld::DFS(POINT p)//基于dfs的联机搜索，递归调用
{
    World[p.first][p.second].state[CURRENT_POS] = 1;
    World[p.first][p.second].state[SAFE] = 1;
    cout<<"current_pos is:"<<findCurrentPos().first<<'\t'<<findCurrentPos().second<<endl;
    if (findGold(p)) {
        //最短路径回家然后结束游戏
        exit(1);
    }
    if (isDead(p)) {
        //游戏结束
        exit(-1);
    }
    int x = p.first, y = p.second;
    World[x][y].state[VISITED] = 1;
    updateSurrdInfo(p);
    POINT temp = BFS(p);
    if(isInside(temp.first, temp.second)){
        p = findCurrentPos();
        DFS(p);
    }
    //评估上下左右危险度，选择危险度最小的走
    POINT i = judgeAction(p);
    World[p.first][p.second].state[CURRENT_POS] = 0;
    DFS(i);
}
POINT WumpusWorld::BFS(POINT p)//基于bfs返回安全点,如果没有安全点，则返回false
{
    updateSurrdInfo(p);
    clearSusp();
    comfWumpAndPit();
    cout<<"current_pos is:"<<findCurrentPos().first<<'\t'<<findCurrentPos().second<<endl;
    QTPath.push_back(p);
    if (findGold(p)) {//最短路径回家然后结束游戏
        return POINT(-1,-1);

    }
    if (isDead(p)) {//游戏结束
//        exit(-1);
        return POINT(-1,-1);
    }
    int x = p.first, y = p.second;
    World[x][y].state[CURRENT_POS] = 0;
    World[x][y].state[VISITED] = 1;
    for (int i = 1; i <= 3; ++i) {
        if (isInside(x, y+i) && World[x][y+i].state[SAFE] == 1 && World[x][y+i].state[VISITED] == 0) {
            //去那个点探查
            //要最短visited寻路过去啊
            World[x][y+i].state[CURRENT_POS] = 1;
            return POINT(x,y+i);
        }
        if (isInside(x, y-i) && World[x][y-i].state[SAFE] == 1 && World[x][y-i].state[VISITED] == 0) {
            //去那个点探查
            //要最短visited寻路过去啊
            World[x][y-i].state[CURRENT_POS] = 1;
            return POINT(x,y-i);
        }
        if (isInside(x+i, y) && World[x+i][y].state[SAFE] == 1 && World[x+i][y].state[VISITED] == 0) {
            //去那个点探查
            World[x+i][y].state[CURRENT_POS] = 1;
            return POINT(x+i,y);
        }
        if (isInside(x-i, y) && World[x-i][y].state[SAFE] == 1 && World[x-i][y].state[VISITED] == 0) {
            //去那个点探查
            World[x-i][y].state[CURRENT_POS] = 1;
            return POINT(x-i,y);
        }
        if (isInside(x-i, y-i) && World[x-i][y-i].state[SAFE] == 1 && World[x-i][y-i].state[VISITED] == 0) {
            //去那个点探查
            World[x-i][y-i].state[CURRENT_POS] = 1;
            return POINT(x-i,y-i);
        }
        if (isInside(x-i, y+i) && World[x-i][y+i].state[SAFE] == 1 && World[x-i][y+i].state[VISITED] == 0) {
            //去那个点探查
            World[x-i][y+i].state[CURRENT_POS] = 1;
            return POINT(x-i,y+i);
        }
        if (isInside(x+i, y+i) && World[x+i][y+i].state[SAFE] == 1 && World[x+i][y+i].state[VISITED] == 0) {
            //去那个点探查
            World[x+i][y+i].state[CURRENT_POS] = 1;
            return POINT(x+i,y+i);
        }
        if (isInside(x+i, y-i) && World[x+i][y-i].state[SAFE] == 1 && World[x+i][y-i].state[VISITED] == 0) {
            //去那个点探查
            World[x+i][y-i].state[CURRENT_POS] = 1;
            return POINT(x+i,y-i);
        }
    }
    World[x][y].state[CURRENT_POS] = 0;
    POINT t = judgeAction(p);
    World[t.first][t.second].state[CURRENT_POS] = 1;
    return t;
}
void WumpusWorld::updateSurrdInfo(POINT p)
{
    int x = p.first, y = p.second;
    if (World[x][y].state[BREEZE] == 0 && World[x][y].state[STENCH] == 0) {//当前状态无信息感知，则判断四周安全
        if (isInside(x-1, y))
            World[x-1][y].state[SAFE] = 1;
        if (isInside(x+1, y))
            World[x+1][y].state[SAFE] = 1;
        if (isInside(x, y-1))
            World[x][y-1].state[SAFE] = 1;
        if (isInside(x, y+1))
            World[x][y+1].state[SAFE] = 1;
    }
    
    if(World[x][y].state[BREEZE] == 0){//所在点无微风，如果上下左右有怀疑黑洞的，则排除该点黑洞存在可能性
        if (x >= 1 && World[x-1][y].state[PIT_SUSPECT] == 1)
            World[x-1][y].state[PIT_SUSPECT] = 0;
        if (x <= 2 && World[x+1][y].state[PIT_SUSPECT] == 1)
            World[x+1][y].state[PIT_SUSPECT] = 0;
        if (y <= 2 && World[x][y+1].state[PIT_SUSPECT] == 1)
            World[x][y+1].state[PIT_SUSPECT] = 0;
        if (y >= 1 && World[x][y-1].state[PIT_SUSPECT] == 1)
            World[x][y-1].state[PIT_SUSPECT] = 0;
    }
        

    if(wumpus_find == 0 &&World[x][y].state[STENCH] == 0){//所在点无臭味，如果上下左右有怀疑wumpus的，则排除该点wumpus存在可能性
        if (x >= 1 && World[x-1][y].state[WUMPUS_SUSPECT] == 1)
            World[x-1][y].state[WUMPUS_SUSPECT] = 0;

        if (x <= 2 && World[x+1][y].state[WUMPUS_SUSPECT] == 1)
            World[x+1][y].state[WUMPUS_SUSPECT] = 0;
        
        if (y <= 2 && World[x][y+1].state[WUMPUS_SUSPECT] == 1)
            World[x][y+1].state[WUMPUS_SUSPECT] = 0;

        if (y >= 1 && World[x][y-1].state[WUMPUS_SUSPECT] == 1)
            World[x][y-1].state[WUMPUS_SUSPECT] = 0;

        
    }

    if(World[x][y].state[BREEZE] == 1){//所在点有微风，如果上下左右有怀疑黑洞的，则确定该点黑洞存在可能性
        if (x >= 1 && World[x-1][y].state[PIT_SUSPECT] == 1)
            World[x-1][y].state[PIT] = 1;
        else if(x >= 1 && World[x-1][y].state[PIT_SUSPECT] == 0)
            putFlag(POINT(x-1,y), PIT_SUSPECT);
        
        if (x <= 2 && World[x+1][y].state[PIT_SUSPECT] == 1)
            World[x+1][y].state[PIT] = 1;
        else if(x <= 2 && World[x+1][y].state[PIT_SUSPECT] == 0)
            putFlag(POINT(x+1,y), PIT_SUSPECT);
        
        if (y <= 2 && World[x][y+1].state[PIT_SUSPECT] == 1)
            World[x][y+1].state[PIT] = 1;
        else if(y <= 2 && World[x][y+1].state[PIT_SUSPECT] == 0)
            putFlag(POINT(x,y+1), PIT_SUSPECT);
        
        if (y >= 1 && World[x][y-1].state[PIT_SUSPECT] == 1)
            World[x][y-1].state[PIT] = 1;
        else if(y >= 1 && World[x][y-1].state[PIT_SUSPECT] == 0)
            putFlag(POINT(x,y-1), PIT_SUSPECT);
    }

    //还要加个cnt如果怀疑的地方只有一个那就说明就是那个地方
    int wumpus_suspect_cnt = 0;
    POINT wumpus_confirm;
    if(World[x][y].state[STENCH] == 1){//所在点有臭味，如果上下左右有怀疑wumpus的，则确认该点wumpus存在可能性
        if (x >= 1 && World[x-1][y].state[WUMPUS_SUSPECT] == 1)
            World[x-1][y].state[WUMPUS] = 1;
        
        else if(x >= 1 && World[x-1][y].state[WUMPUS_SUSPECT] == 0 && World[x-1][y].state[SAFE] == 0){
            putFlag(POINT(x-1,y), WUMPUS_SUSPECT);
            wumpus_suspect_cnt += 1;
            wumpus_confirm = POINT(x-1,y);
        }
        
        if (x <= 2 && World[x+1][y].state[WUMPUS_SUSPECT] == 1)
            World[x+1][y].state[WUMPUS] = 1;
        else if(x <= 2 && World[x+1][y].state[WUMPUS_SUSPECT] == 0 && World[x+1][y].state[SAFE] == 0){
            putFlag(POINT(x+1,y), WUMPUS_SUSPECT);
            wumpus_suspect_cnt += 1;
            wumpus_confirm = POINT(x+1,y);
        }
        
        if (y <= 2 && World[x][y+1].state[WUMPUS_SUSPECT] == 1)
            World[x][y+1].state[WUMPUS] = 1;
        else if(y <= 2 && World[x][y+1].state[WUMPUS_SUSPECT] == 0 && World[x][y+1].state[SAFE] == 0){
            putFlag(POINT(x,y+1), WUMPUS_SUSPECT);
            wumpus_suspect_cnt += 1;
            wumpus_confirm = POINT(x,y+1);
        }
        
        if (y >= 1 && World[x][y-1].state[WUMPUS_SUSPECT] == 1)
            World[x][y-1].state[WUMPUS] = 1;
        else if(y >= 1 && World[x][y-1].state[WUMPUS_SUSPECT] == 0  && World[x][y-1].state[SAFE] == 0){
            putFlag(POINT(x,y-1), WUMPUS_SUSPECT);
            wumpus_suspect_cnt += 1;
            wumpus_confirm = POINT(x,y-1);
        }
    }
    if (wumpus_suspect_cnt == 1) {
        World[wumpus_confirm.first][wumpus_confirm.second].state[WUMPUS] = 1;
        wumpus_find = 1;
        wumpus_susp_clear();
        
    }
    
}

POINT WumpusWorld::judgeAction(POINT p)//评估根据当前点状态决定最优选择
{
    int x = p.first, y = p.second;
    vector<pair<POINT, int>> hx_score;

    for (int i = 0; i < 4; ++i) {
        
        if (isAbleToReach(x+i, y) && isInside(x+i, y) && World[x+i][y].state[VISITED] == 0) {
            pair<POINT, int> t(POINT(x+i,y), hx(x+i, y));
            hx_score.push_back(t);
        }
        if (isAbleToReach(x-i, y) && isInside(x-i, y) && World[x-i][y].state[VISITED] == 0) {
            pair<POINT, int> t(POINT(x-i,y), hx(x-i, y));
            hx_score.push_back(t);
        }
        if (isAbleToReach(x, y+i) && isInside(x, y+i) && World[x][y+i].state[VISITED] == 0) {
            pair<POINT, int> t(POINT(x,y+i), hx(x, y+i));
            hx_score.push_back(t);
        }
        if (isAbleToReach(x, y-i) && isInside(x, y-i) && World[x][y-i].state[VISITED] == 0) {
            pair<POINT, int> t(POINT(x,y-1), hx(x, y-i));
            hx_score.push_back(t);
        }
    }
    sort(hx_score.begin(), hx_score.end(), scoreComp());
    return hx_score.begin()->first;
}

int WumpusWorld::hx(int x, int y)//评估函数
{
    int temp_score = 0;
    if (World[x][y].state[WUMPUS] == 1)
        return INT_MIN;
    if (World[x][y].state[PIT] == 1)
        return INT_MIN;
    if (World[x][y].state[WUMPUS_SUSPECT] == 1)
        temp_score += -1;
    if (World[x][y].state[PIT_SUSPECT] == 1)
        temp_score += -1;
    return temp_score;
}


bool WumpusWorld::isInside(int x, int y)
{
    return (x >= 0 && x <= 3 && y >= 0 && y <= 3);
}
POINT WumpusWorld::findCurrentPos()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (World[i][j].state[CURRENT_POS] == 1) {
                return POINT(i,j);
            }
        }
    }
    cerr<<"怎么currentpos不见了？？"<<endl;
    return POINT();
}

bool WumpusWorld::isDead(POINT p)
{
    for (int i = 0; i < pits_pos.size(); ++i) {
        if (p.first == pits_pos[i].first && p.second == pits_pos[i].second) {
            score += DEATH_COST;
            return 1;
        }
    }
    if (p.first == wumpus_pos.first && p.second == wumpus_pos.second) {
        score += DEATH_COST;
        return 1;
    }
    return 0;
}
bool WumpusWorld::findGold(POINT p)
{
    if (p.first == gold_pos.first && p.second == gold_pos.second) {
        score += GOLD_VALUE;
        return 1;
    }
    return 0;
}
void WumpusWorld::wumpus_susp_clear()//如果wumpus找到了则删除所有怀疑的地方
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            World[i][j].state[WUMPUS_SUSPECT] = 0;

        }
    }
}
void WumpusWorld::clearSusp()//每走一步维护所有sus的点，看看是否能清除
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (World[i][j].state[WUMPUS_SUSPECT] == 1) {
                if (isInside(i+1, j) && World[i+1][j].state[STENCH] == 0) {
                    World[i][j].state[WUMPUS_SUSPECT] = 0;
                }
                if (isInside(i-1, j) && World[i-1][j].state[STENCH] == 0) {
                    World[i][j].state[WUMPUS_SUSPECT] = 0;
                }
                if (isInside(i, j-1) && World[i][j-1].state[STENCH] == 0) {
                    World[i][j].state[WUMPUS_SUSPECT] = 0;
                }
                if (isInside(i, j+1) && World[i][j+1].state[STENCH] == 0) {
                    World[i][j].state[WUMPUS_SUSPECT] = 0;
                }
            }
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (World[i][j].state[PIT_SUSPECT] == 1) {
                if (isInside(i+1, j) && World[i+1][j].state[BREEZE] == 0) {
                    World[i][j].state[PIT_SUSPECT] = 0;
                }
                if (isInside(i-1, j) && World[i-1][j].state[BREEZE] == 0) {
                    World[i][j].state[PIT_SUSPECT] = 0;
                }
                if (isInside(i, j-1) && World[i][j-1].state[BREEZE] == 0) {
                    World[i][j].state[PIT_SUSPECT] = 0;
                }
                if (isInside(i, j+1) && World[i][j+1].state[BREEZE] == 0) {
                    World[i][j].state[PIT_SUSPECT] = 0;
                }
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (World[i][j].state[STENCH] == 1) {
                int cnt = 0;
                POINT pos;
                if (isInside(i+1, j) && World[i+1][j].state[WUMPUS_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i+1,j);
                }
                if (isInside(i-1, j) && World[i-1][j].state[WUMPUS_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i-1,j);
                }
                if (isInside(i, j-1) && World[i][j-1].state[WUMPUS_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i,j-1);
                }
                if (isInside(i, j+1) && World[i][j+1].state[WUMPUS_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i,j+1);
                }
                if (cnt == 1) {
                    World[pos.first][pos.second].state[WUMPUS] = 1;
                }
            }
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (World[i][j].state[BREEZE] == 1) {
                int cnt = 0;
                POINT pos;
                if (isInside(i+1, j) && World[i+1][j].state[PIT_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i+1,j);
                }
                if (isInside(i-1, j) && World[i-1][j].state[PIT_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i-1,j);
                }
                if (isInside(i, j-1) && World[i][j-1].state[PIT_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i,j-1);
                }
                if (isInside(i, j+1) && World[i][j+1].state[PIT_SUSPECT] == 0) {
                    cnt++;
                    pos = POINT(i,j+1);
                }
                if (cnt == 1) {
                    World[pos.first][pos.second].state[WUMPUS] = 1;
                    wumpus_susp_clear();
                    wumpus_find = 1;
                }
            }
        }
    }
    
}
void WumpusWorld::comfWumpAndPit()//每走一步维护所有臭气以及微风的点，看看是否能确认四周的wump或pit
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (World[i][j].state[BREEZE] == 1) {
                //检查周围是否只有一个susp，如果只有一个则确定该位置为石锤
                int cnt = 0;
                int tx = -1, ty = -1;
                
                if (isInside(i+1, j) && World[i+1][j].state[PIT_SUSPECT] == 1) {
                    cnt++;
                    tx = i+1; ty = j;
                }
                if (isInside(i-1, j) && World[i-1][j].state[PIT_SUSPECT] == 1) {
                    cnt++;
                    tx = i-1; ty = j;
                }
                if (isInside(i, j+1) && World[i][j+1].state[PIT_SUSPECT] == 1) {
                    cnt++;
                    tx = i; ty = j+1;
                }
                if (isInside(i, j-1) && World[i][j-1].state[PIT_SUSPECT] == 1) {
                    cnt++;
                    tx = i; ty = j-1;
                }
                if (cnt == 1) {
                    World[tx][ty].state[PIT] = 1;
                }

            }
            if (wumpus_find == 0 && World[i][j].state[STENCH] == 1) {
                int cnt = 0;
                int tx = -1, ty = -1;
                if (isInside(i+1, j) && World[i+1][j].state[WUMPUS_SUSPECT] == 1) {
                    cnt++;
                    tx = i+1; ty = j;
                }
                if (isInside(i-1, j) && World[i-1][j].state[WUMPUS_SUSPECT] == 1) {
                    cnt++;
                    tx = i-1; ty = j;
                }
                if (isInside(i, j+1) && World[i][j+1].state[WUMPUS_SUSPECT] == 1) {
                    cnt++;
                    tx = i; ty = j+1;
                }
                if (isInside(i, j-1) && World[i][j-1].state[WUMPUS_SUSPECT] == 1) {
                    cnt++;
                    tx = i; ty = j-1;
                }
                if (cnt == 1) {
                    World[tx][ty].state[WUMPUS] = 1;
                    wumpus_find = 1;
                }
            }
        }
    }
}

bool WumpusWorld::isAbleToReach(int x, int y)
{
    if (isInside(x+1, y) && World[x+1][y].state[VISITED] == 1) {
        return true;
    }
    if (isInside(x-1, y) && World[x-1][y].state[VISITED] == 1) {
        return true;
    }
    if (isInside(x, y+1) && World[x][y+1].state[VISITED] == 1) {
        return true;
    }
    if (isInside(x, y-1) && World[x][y-1].state[VISITED] == 1) {
        return true;
    }
    return false;
}


void WumpusWorld::randomWorldGenerator()
{
    static uniform_int_distribution<int> rand_pos(0,3);
    int x = rand_pos(e), y = rand_pos(e);
    cout<<"human pos:"<<x<<'\t'<<y<<endl;
    World[x][y].state[CURRENT_POS] = 1;
    //生成pit
    for (int i = 0; i < PITNUMBER; ++i) {
        do {
                x = rand_pos(e); y = rand_pos(e);
           } while (isConflict(x, y));
        pits_pos.push_back(POINT(x,y));
        cout<<"pit pos:"<<x<<'\t'<<y<<endl;
        if (isInside(x+1, y)) {
            World[x+1][y].state[BREEZE] = 1;
        }
        if (isInside(x-1, y)) {
            World[x-1][y].state[BREEZE] = 1;
        }
        if (isInside(x, y+1)) {
            World[x][y+1].state[BREEZE] = 1;
        }
        if (isInside(x, y-1)) {
            World[x][y-1].state[BREEZE] = 1;
        }
    }
    //生成gold
    for (int i = 0; i < GOLDNUMBER; ++i) {
        do {
                x = rand_pos(e); y = rand_pos(e);
            } while (isConflict(x, y));
        World[x][y].state[GOLD] = 1;
        gold_pos.first = x; gold_pos.second = y;
        cout<<"gold pos:"<<x<<'\t'<<y<<endl;
    }
    //生成wumpus
    for (int i = 0; i < WUMPUSNUMBER; ++i) {
        do {
                x = rand_pos(e); y = rand_pos(e);
            } while (isConflict(x, y));
        wumpus_pos.first = x;   wumpus_pos.second = y;
        cout<<"wumpus pos:"<<x<<'\t'<<y<<endl;
        if (isInside(x+1, y)) {
            World[x+1][y].state[STENCH] = 1;
        }
        if (isInside(x-1, y)) {
            World[x-1][y].state[STENCH] = 1;
        }
        if (isInside(x, y+1)) {
            World[x][y+1].state[STENCH] = 1;
        }
        if (isInside(x, y-1)) {
            World[x][y-1].state[STENCH] = 1;
        }
    }
}
bool WumpusWorld::isConflict(int x, int y)//生成地图是用于检查是否重叠
{

    if (World[x][y].state[PIT] == 1) {
        return true;
    }
    if (World[x][y].state[CURRENT_POS] == 1) {
        return true;
    }
    if (World[x][y].state[GOLD] == 1) {
        return true;
    }
    //使危险不能离人只有1格子
    if (isInside(x+1, y) && World[x+1][y].state[CURRENT_POS] == 1) {
        return true;
    }
    if (isInside(x-1, y) && World[x-1][y].state[CURRENT_POS] == 1) {
        return true;
    }
    if (isInside(x, y+1) && World[x][y+1].state[CURRENT_POS] == 1) {
        return true;
    }
    if (isInside(x, y-1) && World[x][y-1].state[CURRENT_POS] == 1) {
        return true;
    }
    return false;
}

void WumpusWorld::gameStart()
{
    QTPath.clear();
    POINT temp = findCurrentPos();
    while (temp.first != -1) {
        temp = BFS(temp);
    }
    
}
