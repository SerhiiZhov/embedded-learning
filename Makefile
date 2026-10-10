# Обёртка над idf.py, чтобы работать привычными командами make.
# Плата ищется сама; если подключено несколько — укажи явно: make flash PORT=/dev/cu.usbmodem11101
PORT ?= $(firstword $(wildcard /dev/cu.usbmodem* /dev/cu.usbserial* /dev/cu.wchusbserial* /dev/cu.SLAB_USBtoUART*))
IDF = export PATH="$$(brew --prefix python@3.12)/libexec/bin:$$PATH" && . $$HOME/esp/esp-idf/export.sh >/dev/null && idf.py

build:
	$(IDF) build

flash:
	$(IDF) -p $(PORT) flash

monitor:
	$(IDF) -p $(PORT) monitor

run:
	$(IDF) -p $(PORT) flash monitor

clean:
	$(IDF) fullclean

# Сменить чип: make chip CHIP=esp32   (или esp32c3)
chip:
	$(IDF) set-target $(CHIP)

# Новый проект из этой папки: make new-project NAME=traffic-light  →  появится ../traffic-light
new-project:
	@test -n "$(NAME)" || { echo "Укажи имя: make new-project NAME=my-project"; exit 1; }
	@test ! -e ../$(NAME) || { echo "Папка ../$(NAME) уже существует"; exit 1; }
	rsync -a --exclude build --exclude sdkconfig --exclude sdkconfig.old \
		--exclude managed_components --exclude dependencies.lock ./ ../$(NAME)/
	sed -i '' 's/^project(.*)/project($(NAME))/' ../$(NAME)/CMakeLists.txt
	@echo "Готово: ../$(NAME). Открой эту папку в Cursor и выполни make build"

.PHONY: build flash monitor run clean chip new-project
