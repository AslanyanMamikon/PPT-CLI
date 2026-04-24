# ppt-cli — Presentation Editor for the Command Line

ppt-cli is a command-line tool that lets you create and manage slide presentations entirely from your terminal. Add slides, insert shapes and text, undo mistakes, and export to SVG — no GUI required.

---

## Dependencies

- [nlohmann/json](https://github.com/nlohmann/json) — for JSON save/load support

> **Platform note:** Developed and tested on Windows. Behavior on Linux/macOS has not been verified.

---

## Features

- Create presentations and add slides with different layout types
- Insert shapes (rectangles, circles, lines) and text objects onto slides
- Full undo/redo support for all editing actions
- Save and load presentations as JSON files
- Render slides to SVG files individually or as a full presentation
- Built-in help system for every command

---

## Usage

Launch the CLI:

```
ppt-cli
```

You will be dropped into an interactive prompt:

```
(ppt) >
```

Type commands at the prompt. Use `help` to explore available commands, and `exit` to quit.

---

## Commands

### Slide Management

| Command | Description |
|---|---|
| `add slide` | Add a new slide at the end or at a specific position |
| `remove slide` | Remove a slide by position |
| `move slide` | Move a slide from one position to another |
| `duplicate slide` | Duplicate a slide at a given position |
| `list` | List all slides in the current presentation |

**Examples:**
```
add slide -text title
add slide -text content -pos 2
remove slide -pos 3
move slide -from 2 -to 4
duplicate slide -pos 1
list
```

Supported `-text` (layout) values: `blank` (default), `title`, `content`

---

### Shape & Object Management

| Command | Description |
|---|---|
| `add rectangle` | Add a rectangle to a slide |
| `add circle` | Add a circle to a slide |
| `add text` | Add a text object to a slide |
| `add line` | Add a line to a slide |
| `remove shape` | Remove a shape from a slide by name |

**Common flags for `add` shape commands:**

| Flag | Required | Description |
|---|---|---|
| `-name` | Yes | Unique name for the shape |
| `-slide` | No | Slide position to add to (default: 1) |
| `-x` | Yes | X coordinate |
| `-y` | Yes | Y coordinate |
| `-fill` | No | Fill color (default: `white`) |
| `-border` | No | Border color (default: `black`) |
| `-border-width` | No | Border thickness (default: `1`) |

**Rectangle / Text extra flags:**

| Flag | Required | Description |
|---|---|---|
| `-width` | Yes | Width in pixels |
| `-height` | Yes | Height in pixels |

**Circle extra flags:**

| Flag | Required | Description |
|---|---|---|
| `-radius` | Yes | Radius in pixels |

**Text extra flags:**

| Flag | Required | Description |
|---|---|---|
| `-content` | No | Text content |
| `-font` | No | Font family (default: `Arial`) |
| `-font-size` | No | Font size (default: `12`) |
| `-color` | No | Text color (default: `black`) |

**Line extra flags:**

| Flag | Required | Description |
|---|---|---|
| `-x2` | Yes | End X coordinate |
| `-y2` | Yes | End Y coordinate |
| `-color` | No | Line color (default: `black`) |
| `-width` | No | Line thickness (default: `1`) |

**Examples:**
```
add rectangle -name bg -slide 1 -x 10 -y 10 -width 400 -height 200 -fill lightblue
add circle -name logo -x 100 -y 100 -radius 50 -fill red
add text -name title -x 20 -y 30 -width 300 -height 60 -content "Hello World" -font Arial -font-size 24
add line -name divider -x 0 -y 200 -x2 1920 -y2 200 -color gray -width 2
remove shape -name logo -slide 1
```

---

### Undo / Redo

| Command | Description |
|---|---|
| `undo` | Undo the last action |
| `redo` | Redo the previously undone action |

Undo/redo history is maintained up to 100 actions per session.

---

### Save & Load

| Command | Description |
|---|---|
| `save` | Save the presentation to a JSON file |
| `load` | Load a presentation from a JSON file |

**Examples:**
```
save presentation.json
load presentation.json
save -file my_deck.json
load -file my_deck.json
```

The default filename for `save` is `presentation.json`.

---

### Rendering & Export

| Command | Description |
|---|---|
| `render slide` | Render a single slide to an SVG file |
| `render presentation` | Render all slides to SVG files in a folder |
| `show slide` | Print a slide's SVG output directly to the console |

**`render slide` flags:**

| Flag | Description |
|---|---|
| `-pos` | Slide position to render (default: 1) |
| `-output` | Output filename (default: `slide_<id>.svg`) |
| `-width` | Canvas width in pixels (default: 1920) |
| `-height` | Canvas height in pixels (default: 1080) |
| `-grid` | Include a background grid in the output |

**`render presentation` flags:**

| Flag | Description |
|---|---|
| `-output` | Output folder name (default: `slides`) |
| `-width` | Canvas width in pixels (default: 1920) |
| `-height` | Canvas height in pixels (default: 1080) |
| `-grid` | Include a background grid in the output |

**Examples:**
```
render slide -pos 2 -output my_slide.svg
render presentation -output exported_slides -width 1280 -height 720
show slide -pos 1
show slide -pos 1 -grid
```

---

### Help & Exit

| Command | Description |
|---|---|
| `help` | List all available commands |
| `help <command>` | Show detailed usage for a specific command |
| `exit` | Exit the application |

**Examples:**
```
help
help add slide
help render presentation
help undo
```

---

## Presentation JSON Format

Presentations are saved and loaded as `.json` files. Below is a minimal example:

```json
{
  "slideCount": 1,
  "slides": [
    {
      "id": 1,
      "text": "blank",
      "objects": [
        {
          "type": "Rectangle",
          "name": "bg",
          "geometry": {
            "topLeft": { "x": 10, "y": 10 },
            "bottomRight": { "x": 410, "y": 210 }
          },
          "fillColor": "white",
          "borderColor": "black",
          "borderWidth": 1
        }
      ]
    }
  ]
}
```

Supported object types in JSON: `Rectangle`, `Circle`, `Text`, `Line`

---

## Quick Start Example

```
(ppt) > add slide -text title
(ppt) > add rectangle -name header -slide 1 -x 0 -y 0 -width 1920 -height 120 -fill steelblue
(ppt) > add text -name title -slide 1 -x 60 -y 30 -width 800 -height 80 -content "My Presentation" -font Arial -font-size 48 -color white
(ppt) > add slide -text content
(ppt) > add text -name body -slide 2 -x 100 -y 200 -width 1000 -height 400 -content "Slide content goes here"
(ppt) > save my_presentation.json
(ppt) > render presentation -output slides
(ppt) > exit
```
