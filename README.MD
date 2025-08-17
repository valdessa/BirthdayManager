<h1 align="center"> 🎁 BIRTHDAY MANAGER 🎉 </h1>

<div align="center">
<img src="logo.PNG" alt="Birthday Manager Logo"/>
<img src="logo2.PNG" alt="Birthday Manager Logo2"/>
<br><br>


</div>

## 📝 Introduction

Birthday Manager is a personal C++ project I developed in 2021. It’s built with **SDL2**, **ImGui**, and **SQLite**, and features a interactive clock interface and a birthday database manager.

One of the highlights of this project is its **custom memory management system**, using `MemoryNode` and `Vector` structures to efficiently handle dynamic data. 

This project was a great learning experience in 2021 for  **C memory handling**, **GUI development with ImGui**, and **integrating SQLite databases**.

>✨ **Easter Egg:** If you run the program on someone’s birthday, you’ll discover a little surprise hidden inside the application! 🎉


---

🌟🌟🌟 HOW TO BUILD AND EXECUTE 🌟🌟🌟

### Build the project

- **Debug build:** `tools\debug_compiler.bat`
- **Release build:** `tools\release_compiler.bat`

### Run the game

- **Debug mode:** `tools\RUN_BIRTHDAY_MANAGER_debug.bat`
- **Release mode:** `tools\RUN_BIRTHDAY_MANAGER_release.bat`

> ⚠️ Requirements: You need to have **Visual Studio build tools** installed.

<div align="center">
<br>
🌟🌟🌟 HISTORY VERSIONS 🌟🌟🌟
<br>
</div>

| Version | Date       | Changes |
|---------|------------|---------|
| 8.2.2   | 16/11/2022 | Dates reorderer from DD-MM-YYYY to YYYY-MM-DD |
| 8.2.1   | 18/03/2022 | Fixed bug with "Seconds Lived" (`int` → `unsigned long int`) |
| 8.2     | 24/01/2022 | Fixed crash if there’s no birthday database |
| 8.1     | 15/01/2022 | Fixed time variables for birthdays of the current month |
| 8.0     | 09/01/2022 | Updated `window.h` with `setIconWindow`; added Kirby icon; minor fixes |
| 7.0     | 02/01/2022 | Birthday Database and Manager working; unified Clock + Database Manager + Birthday Database |
| 6.0     | 26/12/2021 | Unified Clock + Database Manager |
| 5.0     | 25/12/2021 | Added ImGui and sound to the Clock; Clock Finished :D |
| 4.0     | 25/12/2021 | Clock circle done |
| 3.0     | 25/12/2021 | Clock animation working |
| 2.0     | 25/12/2021 | Clock needles working |
| 1.0     | 22/12/2021 | Seconds counter done |
