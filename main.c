/*
Ultimate Number Guessing Game 2026
Copyright (C) 2026  kinakomofmof

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3,
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CONFIG_PATH "/lib/com.kinakomofmof/game/settings/settings.yml"
#define DEFAULT_SCORE_PATH "/lib/com.kinakomofmof/game/scores/scores.txt"

// 設定
int saveScore = 1;
char scorePath[256] = DEFAULT_SCORE_PATH;

// -------------------------------
// 設定ファイル読み込み
// -------------------------------
void load_config() {
    FILE *fp = fopen(CONFIG_PATH, "r");
    if (!fp) return; // 初回起動

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "save:")) {
            saveScore = strstr(line, "true") ? 1 : 0;
        }
        if (strstr(line, "path:")) {
            char *p = strchr(line, '"');
            if (p) {
                p++;
                char *q = strchr(p, '"');
                if (q) *q = '\0';
                strcpy(scorePath, p);
            }
        }
    }
    fclose(fp);
}

// -------------------------------
// 初回セットアップ
// -------------------------------
void setup() {
    printf("--- GAME SETUP ---\n");

    printf("スコアを保存しますか？ (y/n): ");
    char c;
    scanf(" %c", &c);
    saveScore = (c == 'y');

    printf("スコア保存場所を選択:\n");
    printf("1. デフォルト (%s)\n", DEFAULT_SCORE_PATH);
    printf("2. 任意の場所\n> ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        strcpy(scorePath, DEFAULT_SCORE_PATH);
    } else {
        printf("パスを入力してください: ");
        scanf("%s", scorePath);
    }

    // ディレクトリ作成
    system("mkdir -p /lib/com.kinakomofmof/game/settings/");

    // 設定保存
    FILE *fp = fopen(CONFIG_PATH, "w");
    fprintf(fp,
        "score:\n"
        "  save: %s\n"
        "  path: \"%s\"\n",
        saveScore ? "true" : "false",
        scorePath
    );
    fclose(fp);

    printf("設定を保存しました。\n\n");
}

// -------------------------------
// スコア保存
// -------------------------------
void save_score(int attempts) {
    if (!saveScore) return;

    system("mkdir -p /lib/com.kinakomofmof/game/scores/");

    FILE *fp = fopen(scorePath, "a");
    if (!fp) return;

    fprintf(fp, "%d\n", attempts);
    fclose(fp);
}

// -------------------------------
// タイトル画面
// -------------------------------
void title_screen() {
    printf("=====================================\n");
    printf("      究極の数当てゲーム 2026\n");
    printf("=====================================\n");
    printf("   Enterキーで開始...\n");
    getchar();
    getchar();
}

// -------------------------------
// メインゲーム
// -------------------------------
int main() {

    // 設定読み込み
    load_config();

    // 初回起動なら setup
    if (saveScore != 0 && saveScore != 1) {
        setup();
    }

    while (1) {
        int secret_number, guess, attempts = 0;
        int max_value = 0, max_attempts = 0, choice;

        srand(time(NULL));

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

            if (diff <= 2 && diff != 0) {
                printf(">> ★ 超ニアピン！ ★\n");
            } else if (diff <= 10 && diff != 0) {
                printf(">> 近い！\n");
            }

            if (guess == secret_number) {
                printf("\n★ 正解！ %d回目でクリアしました！ ★\n", attempts);

                save_score(attempts);
                break;
            }
        }

        if (attempts >= max_attempts && guess != secret_number) {
            printf("\n【GAME OVER】残念！回数制限です。\n");
            printf("正解は [%d] でした。\n", secret_number);
        }

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

        while (getchar() != '\n');
    }

    return 0;
}