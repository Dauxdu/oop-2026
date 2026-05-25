# oop-2026

## Установка vcpkg

Документация:
[Microsoft vcpkg Getting Started](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs)

1. Установка vcpkg

### Arch Linux

Установка через `pacman`:

```bash
sudo pacman -Syu vcpkg
```

```bash
git clone https://github.com/microsoft/vcpkg $VCPKG_ROOT
cd $VCPKG_ROOT

./bootstrap-vcpkg.sh -disableMetrics
```

### Windows

Создать системную переменную окружения:

| Переменная   | Значение                 |
| ------------ | ------------------------ |
| `VCPKG_ROOT` | `C:\Program Files\vcpkg` |

Добавить в системную переменную окружения:

| Переменная | Значение                 |
| ---------- | ------------------------ |
| `Path`     | `C:\Program Files\vcpkg` |

Установка:

```powershell
git clone https://github.com/microsoft/vcpkg "C:\Program Files\vcpkg"
cd "C:\Program Files\vcpkg"

bootstrap-vcpkg.bat -disableMetrics
```

2. Создание проекта

В корне проекта выполнить:

```bash
vcpkg new --application
```

Будут созданы файлы:

- `vcpkg.json`
- `vcpkg-configuration.json`

3. Установка зависимостей

Добавление библиотек в проект:

```bash
vcpkg add port sfml boost
```

После этого зависимости автоматически появятся в `vcpkg.json`.

Пример `vcpkg.json`:

```json
{
  "name": "oop-2026",
  "version": "1.0.0",
  "dependencies": ["boost", "sfml"]
}
```

4. Системные пакеты Linux и macOS

На Linux и macOS проект можно собрать без `vcpkg`, если зависимости установлены через системный пакетный менеджер.

Пример для Arch Linux:

```bash
sudo pacman -Syu boost sfml protobuf
```

Однако использование `vcpkg` предпочтительнее, так как позволяет:

- фиксировать версии библиотек;
- упростить переносимость проекта;
- использовать одинаковые зависимости на разных ОС;
- хранить конфигурацию зависимостей внутри проекта.

5. Экспорт зависимостей

Экспорт установленных библиотек:

```bash
vcpkg export --zip --output-dir="./vcpkg_sdks"
```

Архив можно использовать для переноса зависимостей между машинами или CI-средами.
