# oop-2026

## Установка vcpkg

Документация:
[Microsoft vcpkg Getting Started](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?utm_source=chatgpt.com)

### 1. Клонирование и установка

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh -disableMetrics
```

### 2. Добавление `VCPKG_ROOT`

Linux/macOS:

```bash
echo 'export VCPKG_ROOT="$HOME/vcpkg"' >> ~/.bashrc
source ~/.bashrc
```

Windows (PowerShell):

```powershell
setx VCPKG_ROOT "C:\path\to\vcpkg"
```

### 3. Создание проекта

```bash
vcpkg new --application
```

### 4. Установка зависимостей

```bash
vcpkg add port boost sfml
vcpkg install
```

### 5. Экспорт зависимостей

```bash
vcpkg export --zip --output-dir="./vcpkg_sdks"
```
