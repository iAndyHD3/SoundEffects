# SoundEffects
A geometry dash mod that adds sound effects to gameplay events
warning: buggy and incomplete

## Sounds

- `orbJump01.ogg` played when activating an orb
- `jump01.ogg` played when you jump (bad implemented and very buggy at the moment)
- `padJump01.ogg` played when activating a pad
- `collectItem01.ogg` played when an item is collected (key, coin, heart..)

## Setup

clone and configure/build with cmake using x86 msvc

### Manual Setup
if u want to do it in cmd then
```bash
# Configure
cmake -B build -A win32
# Build
cmake --build build --config Release
```
