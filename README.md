# Leveling Up with Trivia

Leveling Up with Trivia was created and submitted as part of the Magshimim National Cyber Program 2nd year final project by Eliran Ben Moshe and Maor Dabool.

# Architecture

## Server
Built using C++.

Hosts all Trivia games and manages user states via a **state machine**.

### Uses:
- WinAPI
- SQLite
- [json.hpp](https://github.com/nlohmann/json)

### Infrastructure

#### Player States

- **Login (Initial State):** The starting point. When someone connects, they land here before they're authenticated or tied to an account.
- **Menu:** The main hub. From here, players can jump into a room, check out their stats, and access other primary actions.
- **Room Member (Waiting Room):** Once a player joins a room, they wait until the admin starts the game. They can check out the room's details and see the stats of other players in the lobby.
- **Room Admin (Waiting Room):** This is exactly like the Room Member state, but with host privileges. Admins can kick players, update room settings, and actually start the game. If the admin leaves, the room shuts down entirely and notifies everyone else as they get booted.
- **Game:** The actual gameplay phase where players request questions and submit their answers. If someone bails mid-game, it triggers the same leave logic as the waiting room (notifying others, or closing the room entirely if they're the admin).
- **Finished Game Early:** The holding pen for fast players. They've finished all their questions but are waiting for the rest of the lobby to wrap up. Leaving the game from this state triggers the exact same logic as leaving during the Game state.

#### State Transitions

**Starting up:** Launching the client throws you directly into the Login state.

**Logging in/out:** Authenticating moves you from Login to Menu.  
Logout sends you back to Login.

**Entering a Room:** Creating a room moves you from the Menu to Room Admin, while joining an existing one makes you a Room Member.

**Leaving a Room:** If you're a member and you leave (or get kicked, or the admin closes the room), you're brought back to the Menu. If you're the admin and you leave, it closes the room and sends you back to the Menu.

**Starting the Game:** When the admin starts the game, both the Members and the Admin are pulled into the Game state.

**Finish:** Once all players finish playing, the room is closed and everyone is back to the Menu state.

## Client
Built using Windows Presentation Foundation (WPF).

Utilizes **MVVM Patterns**.
