# Assetto Corsa Simple Camera

Simple tool for Assetto Corsa to edit car cameras in real time

## Installation

- Make sure you have the latest Steam version of the game, as this is the only version this plugin is compatible with. (exe size of 22890776 bytes)
- Plop the files into your game folder.
- Create a `.toml` config file with the same name as your target car inside `plugins/CameraEditor`, and edit its contents in a text editor while in-game.
- Enjoy, nya~ :3

## Building

Building is done on an Arch Linux system with CLion and vcpkg being used for the build process. 

Before you begin, clone [nya-common](https://github.com/gaycoderprincess/nya-common) and [nya-common-ac](https://github.com/gaycoderprincess/nya-common-ac) to folders next to this one, so they can be found.

Required packages: `mingw-w64-gcc`

You should be able to build the project now in CLion.
