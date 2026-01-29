# ⚔️ Dungeon Raid Console

A C++ console-based puzzle RPG game inspired by "Dungeon Raid". The game combines **Match-3 mechanics** with dungeon crawling strategy. The goal is to survive as long as possible by connecting matching items and defeating enemies.

## 🎮 How to Play

The game takes place on a **6x6 grid**. Each turn, you must connect a sequence of **at least 3 adjacent items** (horizontally, vertically, or diagonally).

**Input Format:**
Enter coordinate pairs separated by spaces: `Column,Row`
> Example: `2,3 2,4 3,5`

### Legends:
* **H (Hero):** You! Keep your HP above 0.
* **E (Enemy):** Deals damage at the end of the turn. Connect **Swords** to **Enemies** to kill them.
* **C (Coin):** Adds +5 Score.
* **S (Sword):** Adds damage to your attack when connected with Enemies.
* **P (Potion):** Heals 10 HP.
* **A (Armor):** Adds +3 Armor (protects against damage).

## 🛠️ Mechanics

* **Combat:** Unlike standard Match-3 games, you can connect **Swords** and **Enemies** in a single line. Each sword increases damage dealt to *all* connected enemies.
* **Defense:** Armor absorbs incoming damage. If damage exceeds armor, your Health (HP) decreases.
* **Turn Based:** You have a limited number of turns (10) to get the highest score possible.

## 💻 Technical Info

* **Language:** C++ (C++17 standard)
* **Architecture:** Object-Oriented Programming (OOP)
    * **Polymorphism:** `Entity` base class with `Item`, `Enemy`, `Hero` derived classes.
    * **Memory Management:** Proper allocation/deallocation of grid entities.
    * **Logic:** Custom match-finding and grid-collapsing algorithms.

## 🚀 How to Run

### Requirements
* A C++ Compiler (GCC/G++, MinGW, or Clang).
* Visual Studio Code (optional, any terminal works).

### Instructions
1.  **Clone the repository**
    ```bash
    git clone https://github.com/Jahgodka/dungeon-raid-console.git
    cd dungeon-raid-console
    ```

2.  **Navigate to the source code**
    ```bash
    cd game
    ```

3.  **Compile and Run**
    Run the following command in your terminal:
    ```bash
    g++ *.cpp -o dungeon_raid
    ./dungeon_raid
    ```
    *(On Windows CMD, use `dungeon_raid.exe` instead of `./dungeon_raid`)*
