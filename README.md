# Шаблон проекта ESP32

Заготовка для новых проектов на ESP-IDF. Работает с ESP32-C3 Super Mini, ESP32-S3 и обычной ESP32.

## Новый проект

```bash
cd ~/work/esp32-template
make new-project NAME=traffic-light
```

Появится папка `~/work/traffic-light` — копия шаблона со своим именем. Открой её в Cursor (**File → Open Folder**) и выполни `make build`.
Сам шаблон не трогай: правь уже созданные из него проекты.

## Команды

| Команда | Что делает |
|---|---|
| `make build` | собрать |
| `make flash` | залить в плату |
| `make monitor` | смотреть `printf` с платы (выход: **Ctrl+]** в английской раскладке) |
| `make run` | залить и сразу смотреть |
| `make clean` | удалить всё собранное |
| `make chip CHIP=esp32` | переключить проект на другой чип (`esp32`, `esp32c3` или `esp32s3`) |

В Cursor: **Cmd+Shift+B** — собрать; **Cmd+Shift+P → Tasks: Run Task → flash and monitor** — залить и смотреть.

## Структура

```
├── main/main.c          ← твоя программа, начинается с app_main()
├── sdkconfig.defaults   ← чип по умолчанию
└── Makefile             ← команды make
```

## Как добавить свой модуль

Создай папку `components/button/` с файлами `button.c`, `button.h` и `CMakeLists.txt`:

```cmake
idf_component_register(SRCS "button.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES esp_driver_gpio)
```

- `SRCS` — все `.c` файлы модуля.
- `PRIV_REQUIRES` — какие части ESP-IDF модуль использует внутри (`esp_driver_gpio` — пины). Если сборка пишет, что не находит заголовок, чаще всего сюда нужно добавить компонент.

Потом в `main.c`: `#include "button.h"`. Больше ничего регистрировать не нужно: ESP-IDF сам находит все папки в `components/`.

## Подсказки в редакторе

Подсказки clangd появятся после первого `make build`: он берёт настройки из папки `build`.
