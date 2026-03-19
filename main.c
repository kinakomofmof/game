#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret_number, guess, attempts = 0;
    int max_value = 0, choice;
    
    srand(time(NULL));

    // 難易度の選択
    printf("難易度を選んでください：\n");
    printf("1: イージー (最大25)\n2: ノーマル (最大50)\n3: ハード (最大100)\n4: スーパーハード (最大1000)\n");
    printf("選択（1-4）: ");
    
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("1〜4の数字で選んでください: ");
        while (getchar() != '\n'); // バッファクリア
    }

    // 難易度に応じて最大値を設定
    switch (choice) {
        case 1: max_value = 25; break;
        case 2: max_value = 50; break;
        case 3: max_value = 100; break;
        case 4: max_value = 1000; break;
    }

    secret_number = rand() % max_value + 1;
    printf("\n1から%dの間の数字を当ててみてください！\n", max_value);
    
    // ゲーム本体
    do {
        printf("予想（1-%d）: ", max_value);
        if (scanf("%d", &guess) != 1) {
            printf("エラー：数字を入力してください。\n");
            while (getchar() != '\n'); 
            continue;
        }
        
        attempts++;
        
        if (guess > secret_number) {
            printf("もっと小さい数字です。\n");
        } else if (guess < secret_number) {
            printf("もっと大きい数字です。\n");
        } else {
            printf("正解！ %d回目で当てました。\n", attempts);
        }
    } while (guess != secret_number);
    
    return 0;
}

