"PC tester" - pc aplikace pro demostraci vypoctu histogramu v GLSL

Vyvojove prostredi:
-Microsoft Visual Studio 2010

Ke spusteni jsou potreba knihovny:
-SDL 1.2 (SDL.lib, SDLmain.lib) - https://www.libsdl.org/download-1.2.php
-GLEW (glew32.lib) - http://glew.sourceforge.net/
-devil (devil.lib) - https://github.com/DentonW/DevIL, http://openil.sourceforge.net/download.php
-ILU, ILUT (ILU.lib, ILUT.lib) - soucast DevIL

Poznamky k prekladu:
-Je nutne zmenit ve vlastnostech projektu cestu k hlavickovym souborum
(Properties-> C/C++ -> General -> Additional Include Directories)
-Dale je nutne nastavit cestu knihovnam
(Properties -> Linker -> General -> Additional Library Dependencies)
-A prilinkovat knihovny
(Properties -> Linker -> Input -> Additional Dependencies)
a vlozit nasledujici knihovny
SDL.lib
glew32.lib
SDLmain.lib
OpenGL32.lib
devil.lib
ILU.lib
ILUT.lib

Ovladani aplikace:
-Zobrazi pouze testovaci obrazek a do konzole vypise pocet polozek v 
jednotlivych binech histogramu