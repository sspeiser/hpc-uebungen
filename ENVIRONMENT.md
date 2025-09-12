Grundsätzlich gehe ich davon aus, dass Sie im HFT PC-Raum LVIS arbeiten.

**VORSICHT**: Die PCs werden nach jedem Reboot zurückgesetzt, d.h. alle Dateien auf C: sind verloren! Sichern Sie daher Ihre Dateien unbedingt per Git auf dem HFT Gitlab Server: https://gitlab.rz.hft-stuttgart.de/
Alternativ können Sie auch das P: Laufwerk verwenden um Daten zu sichern, jedoch sollten Sie es nicht für die tägliche Arbeit verwenden, weil es zu langsam ist.

Wir verwenden folgende Umgebung:
- Windows 11 auf PC mit Intel Prozessor und NVIDIA GPU
- Microsoft C-Compiler (aus Visual Studio Enterprise)
  - Auf Privat-PC können Sie ggfs. nutzen: Visual Studio Community Edition mit Workload C++ Desktop Development:
    https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false#installvs
  - Unter macOS/Linux reichen clang/gcc, die defaultmäßig dabei sind
- Entwicklungsumgebung: Visual Studio Code (!, nicht Enterprise - dies ist eine komplett andere IDE) mit Extension "C/C++-Tools" (ms-vscode.cpptools-extension-pack)
- Build-Tool: CMake (https://cmake.org/download/)
- OpenCL: Im PC-Raum über das NVIDIA CUDA SDK installiert (https://developer.nvidia.com/cuda-downloads?target_os=Windows&target_arch=x86_64&target_version=11&target_type=exe_local)
- MS-MPI: https://www.microsoft.com/en-us/download/details.aspx?id=100593
  - Ist für Windows das einfachste, auf anderen Plattformen/HPC-Clustern ist eine Umgebung im Normalfall vorhanden
- Python: Umgebung verwaltet mit uv (https://github.com/astral-sh/uv/releases), normalerweise: Python 3.13 mit NumPy, Pandas und Matplotlib

Es ist noch weitere Software installiert u.a. CLion als IDE und andere Compiler - diese können Sie verwenden aber auf eigene Gefahr.

## Vorgehen: Eignes Repository anlegen

- Gehen Sie auf https://gitlab.rz.hft-stuttgart.de/projects/new
- Wählen Sie "Import Project"
- Wählen Sie "Repository by URL"
- Fügen Sie ein "https://github.com/sspeiser/hpc-uebungen"
- Click auf "Create project"
- Wenn es fertig ist öffnet sich die Repository Seite
- Click auf "Code" und dann kopieren der URL unter "Clone with HTTPS"
- Command Prompt öffnen (Link auf Desktop im LVIS)
- Eingabe "C:" und ENTER
- Eingabe "git clone " und dann per STRG-V die URL Ihres Gitlab Repositories einfügen
- Mit ENTER bestätigen
- Danach befinden sich alle Dateien unter C:/hpc-uebungen
- Bevor Sie den rechner hinunterfahren mit git add, git commit und git push die Änderungen auf Gitlab speichern
- Beim nächsten Start des Rechners wieder per git clone runterkopieren

## Vorgehen C-Programm ausführen

1. Öffnen Sie Visual Studio Code
2. File -> Open Folder und dann das Verzeichnis der Übung/des Beispiels öffnen indem die CMakeLists.txt ist, z.B. das Verzeichnis "caches"
3. Bei Select Kit "Visual Studio Enterprise 2022 Release - amd64" (o.ä.) auswählen
4. **nicht** den "Play Button" ("Run C/C++ File") nutzen!
5. Per Tastenkombi Ctrl+Shift+P wird die Kommandopalette aufgerufen, dort nutzen wir "CMake: Configure" (Projekt initial konfigurieren); "CMake: Build" (kompilieren); "CMake: Debug" und "CMake: Run without Debugging"
6. Alternativ gehen die kleinen Knöpfe links unten



## Vorgehen Python

1. Per Kommandozeile in das Verzeichnis der Übung/des Beispiels gehen, in dem die pyproject.toml, z.B. das Verzeichnis "amdahl"
2. In Kommandozeile "uv sync" ausführen
3. Öffnen Sie Visual Studio Code
4. File -> Open Folder und dann das Verzeichnis der Übung/des Beispiels auswählen
5. Falls die ersten Schritte ausgelassen: Im integrierten Terminal "uv init" ausführen
6. Rechts unten in der Statusleiste das "Virtual Environment" im aktuellen Verzeichnis (".venv") auswählen - alternativ das auswählen wenn VS Code das erste mal danach frägt


## Vorgehen DACHS

TBD