#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
// 打印游戏界面,包括游戏棋盘和分数
void PrintfMap(int map[4][4], int score) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%6d", map[i][j]);
        }
        printf("\n");
    }
    printf("得分：%d\n", score);
}
// 在随机空白位置生成2或4
void RandomNumber(int map[4][4]) {
    int empty[16][2];
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j] == 0) {
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int randomIndex = rand() % count;
        int randomValue = (rand() % 2 == 0) ? 2 : 4;
        map[empty[randomIndex][0]][empty[randomIndex][1]] = randomValue;
    }
}
// 界面向左移动，合并相同数字
bool MoveLfet(int map[4][4]) {
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        int target = 0;
        for (int j = 0; j < 4; j++) {
            if (map[i][j] != 0) {
                if (target > 0 && map[i][target - 1] == map[i][j]) {
                    map[i][target - 1] *= 2;
                    map[i][j] = 0;
                    changed = true;
                }
                else {
                    if (target != j) {
                        map[i][target] = map[i][j];
                        map[i][j] = 0;
                        changed = true;
                    }
                    target++;
                }
            }
        }
    }
    return changed;
}
// 界面向上移动，合并相同数字
bool MoveUp(int map[4][4]) {
    bool changed = false;
    for (int j = 0; j < 4; j++) {
        int target = 0;
        for (int i = 0; i < 4; i++) {
            if (map[i][j] != 0) {
                if (target > 0 && map[target - 1][j] == map[i][j]) {
                    map[target - 1][j] *= 2;
                    map[i][j] = 0;
                    changed = true;
                }
                else {
                    if (target != i) {
                        map[target][j] = map[i][j];
                        map[i][j] = 0;
                        changed = true;
                    }
                    target++;
                }
            }
        }
    }
    return changed;
}
// 界面向右移动，合并相同数字
bool MoveRight(int map[4][4]) {
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        int target = 4 - 1;
        for (int j = 4 - 1; j >= 0; j--) {
            if (map[i][j] != 0) {
                if (target < 4 - 1 && map[i][target + 1] == map[i][j]) {
                    map[i][target + 1] *= 2;
                    map[i][j] = 0;
                    changed = true;
                }
                else {
                    if (target != j) {
                        map[i][target] = map[i][j];
                        map[i][j] = 0;
                        changed = true;
                    }
                    target--;
                }
            }
        }
    }
    return changed;
}
// 界面向下移动，合并相同数字
bool MoveDown(int map[4][4]) {
    bool changed = false;
    for (int j = 0; j < 4; j++) {
        int target = 4 - 1;
        for (int i = 4 - 1; i >= 0; i--) {
            if (map[i][j] != 0) {
                if (target < 4 - 1 && map[target + 1][j] == map[i][j]) {
                    map[target + 1][j] *= 2;
                    map[i][j] = 0;
                    changed = true;
                }
                else {
                    if (target != i) {
                        map[target][j] = map[i][j];
                        map[i][j] = 0;
                        changed = true;
                    }
                    target--;
                }
            }
        }
    }
    return changed;
}
// 判断游戏是否结束（没有空白位置且相邻位置没有相同数字）
bool isGameOver(int map[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (map[i][j] == 0) {
                return false;
            }
            if (i > 0 && map[i][j] == map[i - 1][j]) {
                return false;
            }
            if (j > 0 && map[i][j] == map[i][j - 1]) {
                return false;
            }
            if (i < 4 - 1 && map[i][j] == map[i + 1][j]) {
                return false;
            }
            if (j < 4 - 1 && map[i][j] == map[i][j + 1]) {
                return false;
            }
        }
    }
    return true;
}
//主函数，初始化游戏，判断游戏没有失败的时候执行对应功能函数，用switch语句识别输入的方向
int main() {
    int map[4][4] = { 0 };
    srand(time(NULL));
    //开始的时候需要两个数才能正常运行第一步
    RandomNumber(map);
    RandomNumber(map);
    int score = 0;
    PrintfMap(map, score);

    while (!isGameOver(map)) {
        char input;
        scanf_s(" %c", &input);
        bool changed = false;
        switch (input) {
        case 'w':
            changed = MoveUp(map);
            break;
        case 'a':
            changed = MoveLfet(map);
            break;
        case 's':
            changed = MoveDown(map);
            break;
        case 'd':
            changed = MoveRight(map);
            break;
        default:
            printf("无效输入！请输入 w/a/s/d。\n");
            continue;
        }
        if (changed) {
            RandomNumber(map);
        }
        score++;
        PrintfMap(map, score);
    }
    printf("游戏结束！\n");
    return 0;
}