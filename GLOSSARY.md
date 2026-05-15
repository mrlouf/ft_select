# Glossary

This project uses a lot of terminal control sequences and key codes. In particular, the tutorials and resources I found online often use ANSI escape codes to control the terminal, and these can be quite cryptic. Additionally, the key codes for special keys (like arrow keys, Home, End, etc.) can vary between different terminals and configurations.

Lastly, the project requires the mandatory use of the `termcap` library, which has its own set of functions and capabilities that need to be understood.

This glossary is an attempt to document the key codes, escape sequences, and termcap functions that are relevant to this project, and how they compare to ANSI equivalents.

## Key Codes

- `KEY_UP`: The key code for the up arrow key. This is typically represented as `\x1b[A` in ANSI escape codes.
- `KEY_DOWN`: The key code for the down arrow key. This is typically represented as `\x1b[B` in ANSI escape codes.
- `KEY_RIGHT`: The key code for the right arrow key. This is typically represented as `\x1b[C` in ANSI escape codes.
- `KEY_LEFT`: The key code for the left arrow key. This is typically represented as `\x1b[D` in ANSI escape codes.
