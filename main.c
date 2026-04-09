#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Copyright (c)2026 kinakomofmof
Licensed under the Apache License, Version 2.0
*/

int main() {
    int secret_number, guess, attempts = 0;
    int max_value = 0, max_attempts = 0, choice;
    
    srand(time(NULL));

    printf("--- 究極の数当てゲーム (Hardcore Edition) ---\n");
    printf("1: イージー (1-25 / 10回)\n");
    printf("2: ノーマル (1-50 / 7回)\n");
    printf("3: ハード   (1-100 / 5回)\n");
    printf("4: スーパーハード (1-1000 / 7回)\n");
    printf("選択（1-4）: ");
    
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("1〜4の数字で選んでください: ");
        while (getchar() != '\n');
    }

    switch (choice) {
        case 1: max_value = 25;   max_attempts = 10; break;
        case 2: max_value = 50;   max_attempts = 7;  break;
        case 3: max_value = 100;  max_attempts = 5;  break;
        case 4: max_value = 1000; max_attempts = 7;  break; // 1000を7回はほぼ無理ゲー
    }

    secret_number = rand() % max_value + 1;
    printf("\n【制限回数: %d回】1から%dの間を当てろ！\n", max_attempts, max_value);
    
    while (attempts < max_attempts) {
        printf("[%d/%d] 予想: ", attempts + 1, max_attempts);
        
        if (scanf("%d", &guess) != 1) {
            printf("エラー：数字以外は受け付けません。\n");
            while (getchar() != '\n'); 
            continue;
        }
        
        attempts++;
        
        if (guess > secret_number) {
            printf(">> もっと小さい数字です。\n");
        } else if (guess < secret_number) {
            printf(">> もっと大きい数字です。\n");
        } else {
            printf("\n★ 正解！ %d回目でクリアしました！ ★\n", attempts);
            return 0;
        }
    }

    // 制限回数を超えた場合
    printf("\n【GAME OVER】残念！回数制限です。\n");
    printf("正解は [%d] でした。修行して直してこい！\n", secret_number);
    
    return 0;
}

