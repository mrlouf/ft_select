# Glossary

This project uses a lot of terminal control sequences and key codes. In particular, the tutorials and resources I found online often use ANSI escape codes to control the terminal, and these can be quite cryptic. Additionally, the key codes for special keys (like arrow keys, Home, End, etc.) can vary between different terminals and configurations.

Lastly, the project requires the mandatory use of the `termcap` library, which has its own set of functions and capabilities that need to be understood.

This glossary is an attempt to document the key codes, escape sequences, and termcap functions that are relevant to this project, and how they compare to ANSI equivalents.

## Termcap Functions

- `tgetent(char *bp, const char *name)`: Loads the entry for the terminal name into the buffer `bp`. This is used to initialize the termcap system and retrieve the capabilities of the terminal.
- `tgetstr(const char *id, char **area)`: Retrieves the string capability with the given identifier `id` and stores it in the area pointed to by `area`. This is used to get the control sequences for various terminal actions (like moving the cursor, clearing the screen, etc.).
- `tgetnum(const char *id)`: Retrieves the numeric capability with the given identifier `id`. This is used to get numeric values for terminal capabilities (like the number of columns and lines).
- `tgetflag(const char *id)`: Retrieves the boolean capability with the given identifier `id`. This is used to check for the presence of certain features in the terminal (like whether it supports color, etc.).

## Key Codes

- `KEY_UP`: The key code for the up arrow key. This is typically represented as `\x1b[A` in ANSI escape codes.
- `KEY_DOWN`: The key code for the down arrow key. This is typically represented as `\x1b[B` in ANSI escape codes.
- `KEY_RIGHT`: The key code for the right arrow key. This is typically represented as `\x1b[C` in ANSI escape codes.
- `KEY_LEFT`: The key code for the left arrow key. This is typically represented as `\x1b[D` in ANSI escape codes.
