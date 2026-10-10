# Шаблон проєкту ESP32

Заготовка для нових проєктів на ESP-IDF. Працює з ESP32-C3 Super Mini, ESP32-S3 і звичайною ESP32.

## Новий проєкт

```bash
cd ~/work/esp32-template
make new-project NAME=traffic-light
```

З'явиться папка `~/work/traffic-light` — копія шаблону зі своїм іменем. Відкрий її в Cursor (**File → Open Folder**) і виконай `make build`.
Сам шаблон не чіпай: редагуй уже створені з нього проєкти.

## Команди

| Команда | Що робить |
|---|---|
| `make build` | зібрати |
| `make flash` | залити в плату |
| `make monitor` | дивитися `printf` з плати (вихід: **Ctrl+]** в англійській розкладці) |
| `make run` | залити й одразу дивитися |
| `make clean` | видалити все зібране |
| `make chip CHIP=esp32` | переключити проєкт на інший чип (`esp32`, `esp32c3` або `esp32s3`) |

У Cursor: **Cmd+Shift+B** — зібрати; **Cmd+Shift+P → Tasks: Run Task → flash and monitor** — залити й дивитися.

## Структура

```
├── main/main.c          ← твоя програма, починається з app_main()
├── sdkconfig.defaults   ← чип за замовчуванням
└── Makefile             ← команди make
```

## Як додати свій модуль

Створи папку `components/button/` з файлами `button.c`, `button.h` і `CMakeLists.txt`:

```cmake
idf_component_register(SRCS "button.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES esp_driver_gpio)
```

- `SRCS` — усі `.c` файли модуля.
- `PRIV_REQUIRES` — які частини ESP-IDF модуль використовує всередині (`esp_driver_gpio` — піни). Якщо збірка пише, що не знаходить заголовок, найчастіше сюди потрібно додати компонент.

Потім у `main.c`: `#include "button.h"`. Більше нічого реєструвати не потрібно: ESP-IDF сам знаходить усі папки в `components/`.

## Підказки в редакторі

Підказки clangd з'являться після першого `make build`: він бере налаштування з папки `build`.
