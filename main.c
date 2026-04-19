#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Copyright (c)2026 kinakomofmof
Licensed under the Apache License, Version 2.0
*/

void title_screen() {
    printf("=====================================\n");
    printf("      究極の数当てゲーム 2026\n");
    printf("=====================================\n");
    printf("   Enterキーで開始...\n");
    getchar(); // 前の入力を消す
    getchar(); // Enter待ち
}

int main() {
    while (1) {  // ★ リトライ対応のゲームループ
        int secret_number, guess, attempts = 0;
        int max_value = 0, max_attempts = 0, choice;

        srand(time(NULL));

        // ★ タイトル画面
        title_screen();

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
            case 4: max_value = 1000; max_attempts = 7;  break;
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

            int diff = abs(guess - secret_number);

            if (guess > secret_number) {
                printf(">> もっと小さい数字です。\n");
            } else if (guess < secret_number) {
                printf(">> もっと大きい数字です。\n");
            }

            // ★ ヒント強化
            if (diff <= 2 && diff != 0) {
                printf(">> ★ 超ニアピン！ ★\n");
            } else if (diff <= 10 && diff != 0) {
                printf(">> 近い！\n");
            }

            if (guess == secret_number) {
                printf("\n★ 正解！ %d回目でクリアしました！ ★\n", attempts);
                break;
            }
        }

        if (attempts >= max_attempts && guess != secret_number) {
            printf("\n【GAME OVER】残念！回数制限です。\n");
            printf("正解は [%d] でした。修行して直してこい！\n", secret_number);
        }

        // ★ リトライ機能
        char retry;
        printf("\nもう一度遊ぶ？ (y/n): ");
        while (scanf(" %c", &retry) != 1 || (retry != 'y' && retry != 'n')) {
            printf("y か n を入力してください: ");
            while (getchar() != '\n');
        }

        if (retry == 'n') {
            printf("また遊んでね！\n");
            break;
        }

        // 入力バッファクリア
        while (getchar() != '\n');
    }

    return 0;
}