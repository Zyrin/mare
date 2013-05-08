Mare
====

Mare steht f�r Make Replacement und ist ein ein Werkzeug �hnlich Make zur Automatisierung des Build-Vorgangs von Softwareprojekten. Dazu werden von Mare mit Hilfe von Regeln zur �bersetzung der Dateien des Projektes Abh�ngigkeiten zwischen Quelldateien und Zielen verwaltet und dar�ber bestimmt, welche Ziele nach �nderungen an Quelldateien zur Aktualisierung der Ziele neu erstellt werden m�ssen. Im Gegensatz zu Make ist das von Mare benutze Dateiformat, welches die �bersetzungsregeln beinhaltet mehr an die Bed�rfnisse moderner Softwareprojekte angepasst.

Motivation
----------

Make ist der Klassiker unter den Build-Tools und geh�rt bei Buildsystemen f�r UNIX-�hnliche Systeme fast immer dazu. Es ist relativ einfach, universell und l�sst sich schnell und einfach einsetzen. Doch Make allein wird inzwischen selten als eigenst�ndiges Buildsystem benutzt, da der Funktionsumfang nicht mehr den Anforderungen moderner Softwareprojekte gerecht wird. H�ufig werden Makefile-Generatoren wie automake, cmake, qmake, prebuild und andere Werkzeuge eingesetzt, um dieses Problem zu umgehen.

* Unterst�tzt von Versionsverwaltungssystemen wie SVN oder Git nutzen viele Projekte das Dateisystem zur Verwaltung der Quelldateien. Meist werden alle Quelldateien in Verzeichnissen geordnet abgelegt, so dass jedem Verzeichnis �bersetzungsregeln f�r die darin enthaltenen Dateien zugeordnet werden k�nnen. Wenn Make allein genutzt wird, dann wird eine Liste aller Dateien ben�tigt, die ohne die Nutzung von Kommandozeilenbefehlen oder anderen Erweiterungen nicht automatisch erstellt werden kann. Meist werden, Dateilisten daher entweder manuell in einem Makefile angeben oder von einem Makefile-Generator erzeugt.

* In einem Makefile werden �bersetzungsregeln sehr universell ohne Konventionen oder zus�tzlichen Informationen angegeben. Daher ist die Struktur des Projekts und der Zweck einer �bersetzungsregel schwer aus dem Makefile rekonstruierbar. Um die Struktur eines Projektes einem Entwickler aufzeigen zu k�nnen, nutzen viele Entwicklungswerkzeuge daher eigene Dateiformate zur Beschreibung eines Projekts. Dies f�hrt dazu, dass einige projektspezifische Informationen in mehren Dateien zum Teil redundant verwaltet werden m�ssen, was die Pflege dieser Information erschwert.

* Die g�ngigen Buildsysteme wie autotools oder cmake sind darauf ausgelegt mit zum Teil sehr unterschiedlich konfigurierten Plattformen umgehen zu k�nnen. Die ad�quate Spezifikation der externen Abh�ngigkeiten eines Projekts kann aufgrund dessen sehr Zeitaufwendig sein. H�ufig werden bei Softwareprojekten jedoch festgelegt, was f�r Plattformen unterst�tzt werden und wie diese Konfiguriert sein sollen. Daher w�rde auch ein weniger aufwendiges Buildsystem ausreichen. Dennoch werden auch bei solchen Projekten die Makefile-Generatoren gerne eingesetzt, da sie weitere Vorteile bieten. Das genutzt Buildsystem ist daher h�ufig viel umfangreicher und schwieriger zu warten, als es sein m�sste.

Funktionsweise
--------------

Mare ist ein kleines eigenst�ndiges Programm, dass in einem Arbeitsverzeichnis aufgerufen wird. Im Arbeitsverzeichnis sucht es nach einer Datei namens "Marefile". Diese Datei beschreibt nach welchen Regeln die Quelldateien in Ziele �bersetzt werden. Mare stellt fest, welche Ziele neu gebaut werden m�ssen und ruft die daf�r notwendigen Tools auf. Anstatt den Buildvorgang direkt auszuf�hren, kann das Marefile auch eingeschr�nkt in Projektdateien f�r eine IDE (z.B. Visual Studio, CodeBlocks, CodeLite) �bersetzt werden.

In einem Marefile gibt es drei spezielle Listen mit den Namen "targets", "configurations" und "platforms". "configurations" listet alle verf�gbaren Konfiguration (z.B. Debug und Release) auf und "targets" enth�lt alle Ziele, die erstellt werden k�nnen, und die daf�r ben�tigten �bersetzungsregeln. "platforms" listet m�gliche Zielplattformen auf und wird in der Regel nur f�r Projekte ben�tigt in denen Cross-Compiler genutzt werden. Ein Marefile f�r eine einfache C++-Anwendung, bei der alle Quelldateien in einem Verzeichnis "src" liegen kann z.B. wie folgt aussehen:

```
configurations = { Debug, Relase }
targets = {
  myApplication = cppApplication + {
    files = {
      "src/**.cpp" = cppSource
    }
  }
}
```

Kompilation
-----------

### Windows

Um Mare unter Windows zu kompilieren, wird git und Visual Studio 2010 (oder neuer) ben�tigt.
https://github.com/craflin/mare.git wird in ein beliebiges Arbeitsverzeichnis geklont. Im Verzeichnis "VS2010" befinden sich dann Projektdateien f�r Visual Studio mit denen Mare kompiliert werden kann.

### Linux

Um Mare unter Linux (oder einem �hnlichen Betriebssystem) zu �bersetzen, wird git, ein g++ kompatibler Compiler und make ben�tigt:

```
$ cd /your/working/directory
$ git clone https://github.com/craflin/mare.git mare
$ cd mare
$ make
```

Die ausf�hrbare Datei befindet sich, dann im Verzeichnis "Debug". Diese kann dazu genutzt werden, um Mare auch ohne Debug-Symbole zu �bersetzen:

```
$ cd /your/working/directory/mare
$ Debug/mare config=Release
```

Das Marefile
------------

Ein Marefile besteht aus verschachtelten assoziativen Listen, bei denen der Schl�ssel eine Zeichenkette ist und der Datenwert eine weitere assoziative Liste sein kann. Datenwerte k�nnen aber auch weggelassen werden. Assoziative Listen k�nnen auch als Zeichenkette interpretiert werden, indem alle in der Liste enthaltenen Schl�ssel mit Leerzeichen getrennt aneinander gereiht werden. Innerhalb einer assoziativen Liste k�nnen mehrere darin enthaltene assoziative Listen definiert werden, indem mehrere Schl�ssel mit Leerzeichen getrennt angegeben werden. Dazu kann auch eine als Zeichenkette interpretierte assoziative Liste in einem Schl�ssel eingef�gt werden. Zudem k�nnen assoziative Listen aus anderen assoziativen Listen zusammengesetzt werden und diverse Fallunterscheidungen f�r verschiedene Konfiguration durchgef�hrt werden.

Ein in einem Marefile angegebenes Ziel (hier "Example1") enth�lt eine Menge an Eingabedateien ("input"), Ausgabedateien ("output") und einen Befehl ("command"), mit dem aus den Eingabedateien die Ausgabedateien erstellt werden k�nnen:

```
targets = {
  Example1 = {
    input = "file1.o file2.o"
    output = "Example1"
    command = "g++ file1.o file2.o -o Example1"
  }
}
```

Die Dateien aus "input" und "output" werden hier mehrfach aufgef�hrt. Um dies zu vermeiden kann zur Vereinfachung auch Folgendes geschrieben werden: 

```
targets = {
  Example1 = {
    input = "file1.o file2.o"
    output = "Example1"
    command = "g++ $(input) -o $(output)"
  }
}
```

Die Objektdateien ("file1.o file2.o") sollen bei diesem Beispiel zun�chst aus .cpp-Dateien erstellt werden. Dazu enth�lt ein Ziel einen Schl�ssel namens "files", welcher Regeln enth�lt um Quelldateien zu verarbeiten: 

```
targets = {
  Example1 = {
    input = "file1.o file2.o"
    output = "Example1"
    command = "g++ $(input) -o $(output)"
    
    cppFlags = "-O3"
    
    files = {
      "file1.cpp" = {
        input = "file1.cpp"
        output = "file1.o"
        command = "g++ $(cppFlags) -c $(input) -o $(output)"
      }
      "file2.cpp" = {
        input = "file2.cpp"
        output = "file2.o"
        command = "g++ $(cppFlags) -c $(input) -o $(output)"
      }
    }
  }
}
```

Die Regeln f�r die beiden Dateien "file1.cpp" und "file2.cpp" k�nnen zusammengefasst werden:

```
targets = {
  Example1 = {
    input = "file1.o file2.o"
    output = "Example1"
    command = "g++ $(input) -o $(output)"
    
    cppFlags = "-O3"
    
    files = {
      "file1.cpp file2.cpp" = {
        input = "$(file)"
        output = "$(patsubst %.cpp,%.o,$(file))"
        command = "g++ $(cppFlags) -c $(input) -o $(output)"
      }
    }
  }
}
```

Die Regel zum �bersetzten einer .cpp-Datei l�sst sich auch auslagern, womit die Spezifikation �berschaubarer wird: 

```
targets = {
  Example1 = {
    input = "file1.o file2.o"
    output = "Example1"
    command = "g++ $(input) -o $(output)"
    
    cppFlags = "-O3"
    
    files = {
      "file1.cpp file2.cpp" = myCppSource
    }
  }
}

myCppSource = {
  input = "$(file)"
  output = "$(patsubst %.cpp,%.o,$(file))"
  command = "g++ $(cppFlags) -c $(input) -o $(output)"
}
```

Die Liste der Objektdateien ("file1.o file2.o") kann automatisch aus der Quelldateienliste erzeugt werden und der Name der Ausgabedatei "Example1" kann aus dem Namen des Ziels abgeleitet werden:

```
targets = {
  Example1 = {
    input = "$(patsubst %.cpp,%.o,$(files))"
    output = "$(target)"
    command = "g++ $(input) -o $(output)"
    
    cppFlags = "-O3"
    
    files = {
      "file1.cpp file2.cpp" = myCppSource
    }
  }
}
...
```

Damit k�nnen auch die Regeln zum Linken des Programms ausgelagert werden:

```
targets = {
  Example1 = myCppApplication + {
    cppFlags = "-O3"
    files = {
      "file1.cpp file2.cpp" = myCppSource
    }
  }
}

myCppSource = {
  input = "$(file)"
  output = "$(patsubst %.cpp,%.o,$(file))"
  command = "g++ $(cppFlags) -c $(input) -o $(output)"
}

myCppApplication = {
  input = "$(patsubst %.cpp,%.o,$(files))"
  output = "$(target)"
  command = "g++ $(input) -o $(output)"
}
```

Die Liste der Quelldateien kann automatisch aus im Dateisystem vorhandenen Dateien generiert werden:

```
targets = {
  Example1 = myCppApplication + {
    cppFlags = "-O3"
    files = {
      "**.cpp" = myCppSource
    }
  }
}
...
```

Einzelne Schl�ssel bei ausgelagerten Regeln k�nnen beim einbinden der Regeln �berschrieben werden. Wenn hier der Name der Ausgabedatei z.B. nicht "Example1" sein soll, kann "output" nachtr�glich ver�ndert werden:

```
targets = {
  Example1 = myCppApplication + {
    output = "Example1.blah"
    cppFlags = "-O3"
    files = {
      "**.cpp" = myCppSource
    }
  }
}
...
```

F�r einfache c- und cpp-Anwendungen gibt es bereits eingebaute Regeln (cApplication, cppApplication, cDynamicLibrary, cppDynamicLibrary, cStaticLibrary, cppStaticLibrary, cSource und cppSource) mit denen das Marefile vereinfacht werden kann. (siehe Abschnitt "voreingebaute Regeln")

### Spezialisierung

Mit einer "if <expr> <statements> [else <statements>"-Anweisung k�nnen bei der Angabe einer Liste spezielle Anpassungen f�r verschiedene Konfigurationen vorgenommen werden:

```
cppFlags = "-mmmx"
if configuration == "Release" {
  cppFlags += "-O3"
}
...
```

oder

```
cppFlags = {
  "-mmmx"
  if configuration == "Release" { "-O3" }
}
...
```

oder

```
cppFlags = "-mmmx -O3"
if configuration != "Release" {
  cppFlags -= "-O3"
}
...
```

oder

```
cppFlags = {
  "-mmmx -O3"
  if configuration != "Release" { -"-O3" }
}
...
```

Daf�r sind die Folgenden "Variablen" hilfreich:
* "configuration" - enth�lt den Namen der aktuellen Konfiguration ("Debug", "Release", ...) 
* "platform" - enth�lt den Namen der Zielplattform ("Win32", "Linux", "MacOSX", ...) 
* "host" - enth�lt den Namen der Hostplattform ("Win32", "Linux", "MacOSX", ...) 
* "tool" - enth�lt den Namen eines �bersetzers ("vcxproj", "codelite", "codeblocks", "cmake") 
* "target" - enth�lt den Namen des aktuell zu �bersetzenden Ziels 
* "architecture" - enth�lt die Architektur des Hostsystems ("i686", "x86_64") 

### Include

�berall in einer Liste, wo ein Schl�ssel angegeben werden kann, k�nnen auch Listen aus einer externen Datei eingebunden werden:

```
targets = {
  include "Example1.mare"
}
...
```

### Dateinamen Wildcards

Wenn Wildcards in einem Schl�ssel benutzt werden, dann wird das Dateisystem nach passenden Dateien durchsucht und eine mit Leerzeichen getrennte Liste der gefunden Dateien an die Stelle des Schl�ssels eingef�gt. Im folgendem Beispiel wird z.B. "**.cpp" durch "file1.cpp file2.cpp" ersetzt, sofern diese beiden Dateien im Dateisystem existieren:

```
targets = {
  Example1 = myCppApplication + {
    files = {
      "**.cpp" = myCppSource
    }
  }
}
...
```

Dabei werden die folgenden Wildards verstanden:
* "*" - eine beliebige Zeichenkette in einem Dateinamen (z.B. "*.cpp" ist kompatibel mit "ab.cpp", "bcd.cpp")
* "?" - ein beliebiges Zeichen in einem Dateinamen (z.B. "a?.cpp" ist kompatibel mit "ab.cpp", "ac.cpp" aber nicht mit "aef.cpp") 
* "**" - eine beliebige Zeichenkette in einem Pfadnamen (z.B. "**.cpp" ist kompatibel mit "aa.cpp", "bb.cpp", "subdir/bbws.cpp", "subdir/subdir/bassb.cpp") 

### Leerzeichen in Schl�sseln

Leerzeichen in einem Schl�ssel werden so interpretiert, dass es sich um eine Liste von Schl�ssel handelt. Damit kann mehreren Schl�sseln gleichzeitig ein Datenwert zugeordnet werden. Wenn ein Schl�ssel aber tats�chlich ein Leerzeichen enthalten sein soll (z.B. f�r einen Dateinamen mit Leerzeichen) kann die Zeichenkette in "\"" angegeben werden: 

```
myKey = "\"file name.txt\""
```

(Dieses Feature ist experimentell.)

### ',' und ';'

Angaben in einem Marefile k�nnen optional mit Komma oder Semikolon getrennt werden:

```
targets = {
  Example1 = myCppApplication + {
    files = {
      "*.cpp" = myCppSource;
    },;;,,
  },
};
...
```

### Funktionen

Innerhalb eines Schl�ssels k�nnen Funktionen der Form "$(function arguments)" benutzt werden. Diese verhalten sich so, wie die Funktionen die auch in einem Gnu Makefile genutzt werden k�nnen (siehe http://www.gnu.org/software/make/manual/make.html#Functions). Jedoch sind derzeit noch nicht alle Funktionen implementiert. Implementiert sind die Folgenden:
* subst, patsubst, filter, filter-out, firstword, lastword, dir, notdir, suffix, basename, addsuffix, addprefix, if, foreach, origin 

Zus�tzlich gibt es noch:
* lower - wandelt alle Zeichen der W�rter einer Liste in kleingeschriebene Buchstaben um ("$(lower AbC)" wird zu "abc")
* upper - wandelt alle Zeichen der W�rter einer Liste in gro�geschriebene Buchstaben um ("$(upper dDd)" wird zu "DDD")
* readfile - f�gt den Inhalt einer Datei ein (z.B: "$(readfile anyfile.d)") 

### voreingebaute Regeln

F�r einfache C- und C++-Anwendungen/Dlls/Libs, gibt es so genannte voreingebaute Regeln (built-in rules), die von den �bersetzen (f�r z.B. Visual Studio oder CMake) unterschiedlich interpretiert werden, um eine m�glichst "native" �bersetzung zu erm�glichen. 
* cppSource, cSource - Regeln f�r cpp/c Quelldateien 
* cppApplication, cApplication - Regel f�r normale cpp/c Programme
* cppDynamicLibrary, cDynamicLibrary - Regel f�r cpp/c DLLs bzw. "shared objects" 
* cppStaticLibrary, cStaticLibrary - Regeln f�r statische cpp/c Bibliotheken 

Diese Regeln k�nnen mit folgenden Listen angepasst werden:
* linker - Der benutzte Linker (Standardwert ist "gcc" bei cApplication oder cDynamicLibrary; "g++" bei cppApplication oder cppDynamicLibrary und "ar" bei cppStaticLibrary oder cStaticLibrary ) 
* linkFlags, libPaths, libs - Flags f�r den Linker
* cCompiler, cppCompiler - Der benutzte Compiler (Standardwert ist "gcc" bei cApplication, cDynamicLibrary oder cStaticLibrary und "g++" bei cppApplication, cppDynamicLibrary oder cppStaticLibrary)
* cFlags, cppFlags, defines, includePaths - Flags f�r den Compiler
* buildDir - Verzeichnis in dem Objektdateien abgelegt werden (Standardwert ist "$(configuration)") 

Ein einfaches Marefile wie

```
targets = {
  Example1 = cppApplication + {
    defines = { "NDEBUG" }
    libs = { "jpeg" }
    includePaths = { "anypath1", "anypath2" }
    files = {
      "*.cpp" = cppSource
    }
  }
}
```

sollte sowohl direkt von Mare verstanden werden, wie auch in z.B. Visual Studio Projektdateien oder in Dateien f�r CMake �bersetzt werden k�nnen. Die �bersetzer f�r CodeLite, CodeBlocks, NetBeans sind bisher nicht ganz vollst�ndig, so dass ein Marefile f�r diese IDEs noch nicht direkt �bersetzt werden kann. Die CodeLite, CodeBlocks, NetBeans �bersetzer (und auch der Visual Studio �bersetzer) unterst�tzen jedoch die Verwendung eines externen Buildsystems, so dass Mare als Buildsystem in CodeLite, CodeBlocks, NetBeans oder Visual Studio genutzt werden kann. Dazu k�nnen innerhalb eines Ziels die Felder "buildCommand", "reBuildCommand" und "cleanCommand" benutzt werden:

```
targets = {
  Example1 = cppApplication + {
    defines = { "NDEBUG" }
    libs = { "jpeg" }
    includePaths = { "anypath1", "anypath2" }
    files = {
      "*.cpp" = cppSource
    }
    
    if tool = "codelite" || tool == "codeblocks" {
      buildCommand = "./mare $(target) config=$(configuration)"
      cleanCommand = "./mare clean $(target) config=$(configuration)"
      reBuildCommand = "./mare rebuild $(target) config=$(configuration)"
    }
  }
}
```

### �bersetzer

Die �bersetzer sind alle noch nicht ganz Vollst�ndig und k�nnen daher noch nicht alle vorgesehenen Features. Hier eine �bersicht �ber den aktuellen Entwicklungsstand:
<table>
  <tr>
    <td></td>
    <td>mare&nbsp;1)</td>
    <td>vcxproj</td>
    <td>make</td>
    <td>codelite</td>
    <td>codeblocks</td>
    <td>cmake</td>
    <td>netbeans</td>
  </tr>
  <tr>
    <td>configurations</td>
    <td>geht</td>
    <td>geht</td>
    <td>geht</td>
    <td>geht</td>
    <td>geht</td>
    <td></td>
    <td>geht</td>
  </tr>
  <tr>
    <td>platforms</td>
    <td>geht</td>
    <td>?</td>
    <td>geht</td>
    <td>?</td>
    <td>?</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>{c,cpp}{Source,Application,DynamicLibrary,StaticLibrary}</td>
    <td>geht</td>
    <td>geht</td>
    <td>geht</td>
    <td></td>
    <td></td>
    <td>geht</td>
    <td></td>
  </tr>
  <tr>
    <td>{c,cpp}Compiler</td>
    <td>geht</td>
    <td></td>
    <td>geht</td>
    <td></td>
    <td></td>
    <td>geht</td>
    <td></td>
  </tr>
  <tr>
    <td>linker</td>
    <td>geht</td>
    <td></td>
    <td>geht</td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>{build,clean,reBuild}Command</td>
    <td></td>
    <td>geht</td>
    <td></td>
    <td>geht</td>
    <td>geht</td>
    <td></td>
    <td>geht</td>
  </tr>
</table>

1) keine �bersetzung, direkte Interpretation des Marefiles
