# Maitreya 9

Maitreya is an Open Source platform for Vedic and western astrology. Supported platforms are Windows, Max OS X, Linux and UNIX. Mobile platforms like Android or iOS are not supported.
The software is licensed under the GNU Public License and is free for private and commercial use. Details about the license can be found on the Maitreya's License page.

Western and Vedic astrology seem to be two different topics. And so most astrology programs support exactly one of them.
Maitreya supports both. And in deed, both branches of astrology are essentially two different views of the same thing.

**Note: Maitreya was originally developed by Martin Pe, but is no longer actively maintained. Therefore I have created this repository to continue the development of this software.**

**License: GNU GPL 2.0, same as the original project.**


## Features

The program supports many features of Vedic and western astrology.

- Many astrological objects (Upagrahas, Kalavelas, Arabic points, Uranian planets, planetoids).
- A lot of configuration options reflecting different schools and giving a chance for research
- Classic Dasas in text and graphical views (tree and bar diagram)
- Ashtakavarga, Shadbala, classic Yogas and their predictions from classic scriptures
- Solar (annual) chart, transits and progressions
- Various optical features like skins and highlight of aspects for charts and Sarvatobhadra
- Uranian astrology: sensitive points (midpoints, reflection points, sums, differences) and their events, annual predictions.
- Partner charts, ephemeris, eclipses, Hora.



## Platforms

### Windows

Tested on Windows 8 and Windows 10. Used to build Windows Installer.

Compiler: MinGW gcc 4.9.3

### Mac OS X

Tested on Mac OS X Yosemite.

Compiler: Apple LLVM version 6.0.

Build platform for Mac OS images (*.dmg)

### Unix

Tested on the following Unix distros:

| Platform                  | Compiler                |
| ------------------------- | ----------------------- |
| Arch Linux                | gcc 7.1.1 and clang 4.0 |
| Ubuntu 16.04 LTS (Xenial) | gcc 5.4.0               |
| FreeBSD 11                | clang 3.8.0             |
| OpenBSD 6                 | gcc 4.2.1               |
| Cent OS 7                 | gcc 4.8.5               |
| Fedora 25                 | gcc 6.3.1               |
| OpenSUSE 42.2             | gcc 4.8.5               |



## Getting Started

### The First Chart

- On startup two windows will open, a main window with menu and icon list and a chart window with a table of planetary positions.
- The menu command Document → Edit Chart Data will open a dialog window where you can edit the chart's data. Click OK to close the dialog and calculate positions according to the new data.
- Right click into the chart window will open a context menu. Here you can change the view type: Vedic/western
- The menu commands in the Vedic menu will open subwindows for Vedic charts
- Same for the commands in the Western menu for western astrology
- The chart will be saved with the command File → Save. Enter a suitable file name.
- The chart will be closed if you close the first tabular window of the chart.
- A new chart can be open with the command File → New
- Some view types do not belong to a specific chart (e.g. Ephemeris). Consequently some commands are not available, e.g. Dasa view.

### Basic Configuration

- The configuration is under Extras → Configuration.
- First tab ("General"): select your preferred view style: Vedic or Western.
- Go to the second tab and configure the Default Location.

### Basic Philosophy

- The application window contains a list of all opened windows. You can right click on the icons in the list to open a context menu. Each child window will be raised if you double click the icon. Menu commands only affect the active window.
- Each chart has a main window. All dependend child windows will be closed if you close the main window.
- Each child window has a context menu that can be opened with right click on the window.
- A new chart has the current time and default location as base data. You can change it with the chart data dialog (right click → Birth Data)
- You can toggle the view style (Vedic/western) of all child windows that support toggle.
- There are permanent and temporary options. Permanent options can be configured in the configuration dialog, temporary options can be switched in the context menu and will be lost after closing the window.
- Mouse wheel changes the style of graphical charts (MacOS X: shift+wheel).
- The chart data is stored in files. If you change the birth data, you will be asked if you want to save the data. Saved charts can be opened again later.



## Shortcuts

### Keyboard Shortcuts

| Command                        | Hot Key      |
| ------------------------------ | ------------ |
| Vedic Mode                     | V            |
| Western Mode                   | W            |
| Close Window                   | Ctrl W       |
| Close Window                   | Escape       |
| Close File                     | Shift Ctrl W |
| Edit Horoscope Data            | B            |
| Animate Chart                  | Shift Ctrl A |
| Save                           | Ctrl S       |
| Save As                        | Ctrl A       |
| PDF Chart                      | Ctrl P       |
| Quick PDF Chart                | Shift Ctrl P |
| New Single/Multiple View       | Ctrl N       |
| New Single View                | Shift Ctrl N |
| New Multiple Child Choice View | Shift Ctrl M |
| New Multiple Child View        | Ctrl M       |
| Open Project                   | Ctrl O       |
| Exit                           | Ctrl Q       |
| Configuration                  | C            |
| Atlas                          | L            |
| Hora                           | H            |
| Ephemeris                      | E            |
| Eclipse                        | Ctrl E       |
| Partner                        | P            |
| Yoga Editor                    | Ctrl Y       |
| Documentation (Web)            | F1           |
| About                          | Shift F1     |
| New Ashtakavarga               | A            |
| New Dasa Tree                  | D            |
| New Dasa Tree Composite        | Ctrl D       |
| New Graphical Dasa             | G            |
| New Sarvatobhadra              | S            |
| New Shadbala                   | Ctrl B       |
| New Solar                      | Ctrl T       |
| New TextView                   | T            |
| New Transit                    | R            |
| New Uranian                    | U            |
| New Varga Summary              | Ctrl V       |
| New Western Chart              | 0            |
| New Yoga                       | Y            |
| Show Rasi (D-1)                | 1            |
| Show Navamsa (D-9)             | 2            |
| Show Hora (D-2)                | 3            |
| Show Drekkana (D-3)            | 4            |
| Show Chaturtamsa (D-4)         | 5            |
| Show Sastamsa (D-6)            | 6            |
| Show Saptamamsa (D-7)          | 7            |
| Show Ashtamsa (D-8)            | 8            |
| Show Dasamsa (D-10)            | 9            |
| Show Dvadasamsa (D-12)         | Shift 0      |
| Show Shodasamsa (D-16)         | Shift 1      |
| Show Vimsamsa (D-20)           | Shift 2      |
| Show Siddhamsa (D-24)          | Shift 3      |
| Show Bhamsa (D-27)             | Shift 4      |
| Show Trimsamsa (D-30)          | Shift 5      |
| Show Chatvarimsamsa (D-40)     | Shift 6      |
| Show Akshavedamsa (D-45)       | Shift 7      |
| Show Shastiamsa (D-60)         | Shift 8      |
| Show Ashtottaramsa (D-108)     | Shift 9      |
| Show Dvadas-Davadamsa (D-144)  | Shift Ctrl 0 |
| Show Bhava                     | Shift Ctrl 1 |

### Mouse Shortcuts

| View Type                                     | Effect                 | Action              |
| --------------------------------------------- | ---------------------- | ------------------- |
| All                                           | Open Context Menu      | Right Click         |
| Graphical Chart (Vedic and western)           | Toggle Skin            | Mouse Wheel         |
| Graphical Dasa, Dasa Tree View and Text Views | Scroll                 | Mouse Wheel         |
| Graphical Dasa                                | Toggle Antardasa Level | Shift   Mouse Wheel |
| Graphical Dasa                                | Increase/decrease Zoom | Ctrl   Mouse Wheel  |



## Developer's Guide


### UNIX-like Systems

The distribution is based on automake, so the traditional configure/make should be sufficient on most systems.

#### Prerequisites

You need wxWidgets including the headers. Version 3.0 is recommended. Legacy version 2.8 works as well. Version 2.6 is not supported any more.
Example list for wx 3.0 installation on Ubuntu is

- libwxbase3.0-0
- libwxbase3.0-dev
- libwxgtk3.0-gtk3-0
- libwxgtk3.0-gtk3-dev
- wx3.0-headers
- wx3.0-i18n
- libfontconfig1-dev

The following command can be pasted to the console:

	sudo apt-get install libwxbase3.0-0v5 libwxbase3.0-dev libwxgtk3.0-gtk3-0 libwxgtk3.0-gtk3-dev wx3.0-headers wx3.0-i18n libfontconfig1-dev
	
Other platforms have only 2 or 3 such packages. On Redhat/Fedora the wx packages are called wxGTK and wxGTK-dev.

We recommend Unicode packages if your platform provides Ansi and Unicode versions of the software. If not mentioned, Unicode will most likely be the default.

You can also compile wx from source code, see the wxWidgets Site.

Additional dependencies are

- Required: a C/C++ compiler, GNU compiler including g++ (C++ extension) wil be the default on most systems. clang compiler should work as well.
- Development headers of fontconfig package
- flex and byacc for compilation of Lex and Yacc sources (only required after make clean or for experts).
- aclocal, automake and autoconf (only if you want to dive deeper into the compilation details).

#### configure

Default installation directory ("prefix") is according to GNU conventions under /usr/local. Data directory would bei /usr/share/maitreya8, the binaries would be located at /usr/local/bin.
If you want to change this, type

	./configure --prefix=<directory>
	
where <directory> could be something like '/usr' or '/opt'.

If the configure script complains about a wrong automake version you can run the autogen.sh script to create the automake stuff from scratch. Automake and aclocal must be installed in that case.

The wx-config script is essential for the platform dependent compiler switches. configure must find it, otherwise the program will not compile. wx-config is searched in various standard directories. If configure doesn't find your wx-config, start configure with the option

	--with-wx-config=<name>
	
The resulting executable (src/gui/maitreya8.bin) will be quite big. You can strip if you don't want debugging informations (strip src/gui/maitreya8.bin).

The font "Saravali.ttf" from the directory "src/fonts" must be installed on your system.

This is done automatically by 'make install' and can be done manually as follows

- install the font with your system's configuration tools
- copy the font to the default True Type font directory (e.g. /usr/share/fonts/truetype).


### Debian and Ubuntu

On Debian and derivates (Ubuntu, Mint etc.) there are packages for Swiss Ephemeris available.
The binaries and headers are available in the packages libswe0 resp. libswe-dev.

The packages can be used for compilation of Maitreya.

	export LIBSWE_CFLAGS=-I/usr/include
	export LIBSWE_LIBS="-lswe"
	configure --with-swe=system

Data files for the swiss ephemeris are available in the packages

- swe-standard-data
- swe-extra-data

The data files will be installed under /usr/share/ephe. Maitreya will recognize the data files on startup and set the path to the directory automatically, see General Configuration/Ephemeris.


### Free BSD

wxGTK must be installed. It can be found in the section x11-toolkits. Unicode version of wxgtk 3.0 is recommended.
The script wx-config is named wxgtk2u-3.0-config. The configure command looks like

	./configure --with-wx-config=wxgtk2u-3.0-config

If configure complains about missing fontconfig installation you can set these environment variables and call configure again. See note below (C shell syntax, use export command for bash or ksh).

	setenv FONTCONFIG_CFLAGS "-I/usr/include"
	setenv FONTCONFIG_LIBS "-lfontconfig"
	./configure --with-wx-config=wxgtk2u-3.0-config
	make
	
If font installation with make install does not work you can install it manually instead: copy the font Saravali.ttf from the source directory src/fonts to /usr/local/lib/X11/fonts/TTF and restart the application.


### Windows

Visual Studio is not supported any more.

We use MinGW on Windows.
The compilation with MinGW is a bit more complicated.

#### First step

First step: install MinGW. This is straight forward. Read the corresponding MingGW documentation.

#### Second step

Second step: Installation of wxWidgets

Get the source code for wxWidgets from wxWidgets.org. You can fetch either the windows packages (like wx-msw) or the wxAll package. Unpack the source code. Documentation is under doc/msw.

Go to the the root directory of the wxWidgets source code distribution.

Type this:

	./configure --disable-shared --enable-unicode
	make
	make install

You can also leave the option --disable-shared. You will then get a shared library of wxWidgets. The release will be bigger then.

If everything goes well, you'll have a ready-to-use wxWidgets installation.

You can test your installation by compiling one of the samples (e.g. sample minimal). Just go to the directory, type

	make

and start the example.

#### Third step

Third step: Installation of Maitreya

Create a directory for the source code tree, e.g. c:\maitreya. Enter this directory.

Unpack the source code archive

	unzip maitreya-<version>.zip (zip file)
	or tar jxvf maitreya-<version>.tar.bz2 (bzip2 file) etc.

Type

	make -f Makefile.win

Hope that everything's going well.

The executable (src/gui/maitreya.8exe) will be quite big. You can strip if you don't want debugging informations (strip src/gui/maitreya.exe).

#### Notes

You need the MinGW DLL to start the program. So you can either start the program from the MinGW shell or you provide the files (one or more mingw*.dll) on the path.
These files are located in the msys or mingw directory. It's okay to copy them to the place where the executable or Maitreya is located. Probably you can also copy them to the windows directory, try it.


### Mac OS X
The program compiles and runs on Mac OS X Yosemite or later. GNU gcc and g++ are required (install xcode)
The following steps work on Mac OS X Yosemite with wxWidgets-3.0.3: download wxWidgets source package, unpack it. Create folder for build, change to folder and call configure and make

	../configure --disable-shared --with-macosx-version-min=10.6
	make
	
Unpack the maitreya release and call configure and make.

	export CC="gcc -mmacosx-version-min=10.6"
	export CXX="g++ -mmacosx-version-min=10.6"
	./configure --with-wx-config=[path-to-wx-build]/wx-config
	make
	
Calling the script "create_mac_release.sh" will create the release directory and application folder "Maitreya8.app" with required data. It can be started with the "open" command or with mouse click from the Finder.
Create the disk image with

	create_mac_release.sh dmg




## History

Martin's Website : http://www.saravali.de

### Non-Maintained Repos

- Version 8: https://github.com/martin-pe/maitreya8

- Version 7: https://github.com/martin-pe/maitreya7 

- Version 6: https://github.com/martin-pe/maitreya6




