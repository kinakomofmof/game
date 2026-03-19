# 変数の定義
CC      = gcc
CFLAGS  = -Wall -O2
TARGET  = game

# デフォルトの動作：コンパイル
all: $(TARGET)

# 実行ファイルの生成
$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

# インストール（/binにコピーして実行権限を付与）
install: $(TARGET)
	cp $(TARGET) $(DEST)
	chmod +x $(DEST)/$(TARGET)
	@echo "インストールが完了しました。'$(TARGET)' で起動できます。"

# アンインストール
uninstall:
	rm -f $(DEST)/$(TARGET)
	@echo "アンインストールが完了しました。"

# 一時ファイルの削除
clean:
	rm -f $(TARGET)

.PHONY: all install uninstall clean
