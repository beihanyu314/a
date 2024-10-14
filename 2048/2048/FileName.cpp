#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
// ��ӡ��Ϸ����,������Ϸ���̺ͷ���
void PrintfMap(int map[4][4], int score) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%6d", map[i][j]);
        }
        printf("\n");
    }
    printf("�÷֣�%d\n", score);
}
// ������հ�λ������2��4
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
// ���������ƶ����ϲ���ͬ����
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
// ���������ƶ����ϲ���ͬ����
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
// ���������ƶ����ϲ���ͬ����
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
// ���������ƶ����ϲ���ͬ����
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
// �ж���Ϸ�Ƿ������û�пհ�λ��������λ��û����ͬ���֣�
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
//����������ʼ����Ϸ���ж���Ϸû��ʧ�ܵ�ʱ��ִ�ж�Ӧ���ܺ�������switch���ʶ������ķ���
int main() {
    int map[4][4] = { 0 };
    srand(time(NULL));
    //��ʼ��ʱ����Ҫ�����������������е�һ��
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
            printf("��Ч���룡������ w/a/s/d��\n");
            continue;
        }
        if (changed) {
            RandomNumber(map);
        }
        score++;
        PrintfMap(map, score);
    }
    printf("��Ϸ������\n");
    return 0;
}