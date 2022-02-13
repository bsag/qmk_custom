#!/usr/bin/python

# ============================================
#   Creates an SVG keymap diagram by parsing
#   my qmk keymap.c file, including RGB LED
#   colours.
#
#   This is COMPLETELY SPECIFIC to my map!
#
#   by Matt Gemmell
#   Web:        https://mattgemmell.com/
#   Twitter:    https://twitter.com/mattgemmell
#   GitHub:     https://github.com/mattgemmell
#
# ============================================


# ============================================
#   SETTINGS
# ============================================

# Files (in same dir as this script)
keymap_filename = "keymap.c"
svg_filename = "keymap_diagram.svg"
create_layer_diagrams = True # also create one diagram per layer, named "[svg_filename basename]_[layer_id lowercase].[svg_filename extension]"

# SVG Geometry
diagram_inset = 10 # horizontal and vertical, around entire diagram
layer_spacing = 30 # vertical spacing between each layer
layout_keys_per_row = 12 # last row (only) can have fewer keys
layout_num_edge_keys_ignored = 1 # first and last x keys per row won't be displayed in diagram
# Note: layout_keys_per_row is the actual, real number of keys per row in the keymap structure. It includes ignored edge keys.
key_width = 65
key_height = 55
key_radius = 6 # corner radius
key_spacing = 4 # horizontal and vertical, both between keys and around entire layer
last_row_pad = 20 # additional vertical spacing (added to key_spacing) for final row

# Split layout
layout_split = True # expects an equal number of keys per half, and thus an even number of keys per row
split_spacing = 40 # horizontal spacing between halves of a split layout (used instead of horizontal key_spacing if layout_split is True)

# RGB LED colours
show_led_colours = False # if True, sets "rgb" CSS class on the root <svg> element
led_colours_opacity = 0.3 # 0.0 to 1.0

# Layers
show_layer_titles = True # applies to single overall diagram
show_layer_titles_per_layer = False # applies to separate layer-specific diagrams
layer_title_height = 20 # text box height; set font attributes in CSS below
layer_title_spacing = 10 # vertical spacing between layer title and its layer diagram
layer_held_keycodes = { # keycodes whose keys are implicitly held down on a given layer, gaining the held_css_class specified below
    "_NAV": ["NAV"],
    "_NUM": ["NUM"],
    "_RSYM": ["RSYM"],
    "_LSYM": ["LSYM"],
    "_FN": ["FN"],
}
held_css_class = "held" # keys which are held down on a given layer, i.e. MO(); edit the actual CSS below.
keycode_blank = "XXXXXXX"
blank_css_class = "blank" # as above, for keys with no function (i.e. keycode_blank above).
keycode_transparent = "_______"
transparent_css_class = "transparent" # as above, for transparent keys (falling through to base layer; i.e. keycode_transparent above).
# Note: Transparent keys (on non-base layers) will be labelled identically to the corresponding key on the base layer.

# Advanced
apply_keycode_class = True # applies the lowercase keycode name as a class to the key's DIV, to allow CSS customisation; for example, the "A" key would have class "kc_a" applied.
apply_keycode_title = True # applies the keycode (as-is) as a "title" attribute to the key's DIV, allowing it to be shown in a tooltip upon hover etc.

# SVG template segments
svg_header = '''<svg width="${svg_width}" height="${svg_height}" viewBox="0 0 ${svg_width} ${svg_height}" xmlns="http://www.w3.org/2000/svg" class="${svg_classes}">
<style>
    svg {
        font-family: -apple-system, "Helvetica Neue", sans-serif;
        font-size: 14px;
        text-rendering: optimizeLegibility;
        background-color: white;
    }

    text {
    	text-anchor: middle;
    	dominant-baseline: middle;
    }

    .text-container {
        background-color: white;
        border-radius: ${key_radius}px;
    }

    .text-container > div:hover {

    }

    .text-container > div {
        cursor: default;
        padding: 1px 2px;
        box-sizing: border-box;
        background-color: #f0f0f0;
        text-align: center;
        width: ${key_width}px;
        height: ${key_height}px;
        display: flex;
        justify-content: center;
        align-items: center;
        hyphens: auto;
        -webkit-hyphens: auto;
        -moz-hyphens: auto;
        -ms-hyphens: auto;
        border-radius: ${key_radius}px;
    }

    .text-container > div.${held_css_class} {
        background-color: #bbf;
    }

    .rgb .text-container > div.${held_css_class} {
        border: 3px solid #666;
    }

    .text-container > div.${blank_css_class} {

    }

    .text-container > div.${transparent_css_class} {

    }

    .layer_title {
		font-size: 17px;
		font-weight: bold;
		fill: #777;
    }

    .layer_bg {
        fill: #c0c0c0;
        width: ${layer_bg_width}px;
        height: ${layer_bg_height}px;
    }

    .kc_up, .kc_down, .kc_left, .kc_right,
    .kc_ent, .kc_bspc, .os_caps, .kc_esc,
    .os_shft, .os_ctrl, .os_alt, .os_cmd,
    .kc_mac_spotlight, .kc_pgup, .kc_pgdown,
    .kc_mac_undo, .kc_mac_redo, .kc_tab,
    .kc_mac_cut, .kc_spc, .kc_mac_lock_scrn,
    .kc_brightness_up, .kc_brightness_down,
    .kc_audio_vol_up, .kc_audio_vol_down, .kc_audio_mute,
    .kc_media_play_pause, .kc_media_prev_track, .kc_media_next_track {
    	color: transparent;
    }

    .kc_up:before, .kc_down:before, .kc_left:before, .kc_right:before,
    .kc_ent:before, .kc_bspc:before, .os_caps:before, .kc_esc:before,
    .os_shft:before, .os_ctrl:before, .os_alt:before, .os_cmd:before,
    .kc_mac_spotlight:before, .kc_pgup:before, .kc_pgdown:before,
    .kc_mac_undo:before, .kc_mac_redo:before, .kc_tab:before,
    .kc_mac_cut:before, .kc_spc:before, .kc_mac_lock_scrn:before,
    .kc_brightness_up:before, .kc_brightness_down:before,
    .kc_audio_vol_up:before, .kc_audio_vol_down:before, .kc_audio_mute:before,
    .kc_media_play_pause:before, .kc_media_prev_track:before, .kc_media_next_track:before  {
    	color: #333;
    	font-size: 18px;
		position: fixed;
		margin: 0 auto;
		content: "\\25b2";
    }

    .kc_down:before {
    	content: "\\25bc";
    }

    .kc_left:before {
    	content: "\\25c0";
    }

    .kc_right:before {
    	content: "\\25b6";
    }

    .kc_ent:before {
    	content: "\\23ce";
    	font-size: 20px;
    }

    .kc_bspc:before {
    	content: "\\232b";
    	font-size: 22px;
    }

    .os_caps:before {
    	content: "\\1f310";
    	font-size: 20px;
    }

    .kc_esc:before {
    	content: "\\238b";
    }

    .os_shft:before {
    	content: "\\21e7";
    }

    .os_ctrl:before {
    	content: "\\5e";
    }

    .os_alt:before {
    	content: "\\2325";
    }

    .os_cmd:before {
    	content: "\\2318";
    }

    .kc_mac_spotlight:before {
    	content: "\\2315";
    	font-size: 40px;
    	transform: scaleX(-1);
    }

    .kc_pgup:before {
    	content: "\\21de";
    }

    .kc_pgdown:before {
    	content: "\\21df";
    }

    .kc_mac_undo:before {
    	content: "\\293a";
    	font-size: 34px;
    }

    .kc_mac_redo:before {
    	content: "\\293b";
    	font-size: 34px;
    }

    .kc_tab:before {
    	content: "\\21e5";
    }

    .kc_mac_cut:before {
    	content: "\\2702";
    	font-size: 20px;
    }

    .kc_spc:before {
    	content: "\\2423";
    	font-size: 24px;
    }

    .kc_mac_lock_scrn:before {
    	content: "\\23fb";
    	font-size: 22px;
    }

    .kc_brightness_up:before {
    	content: "\\2600";
    	font-size: 30px;
    }

    .kc_brightness_down:before {
    	content: "\\263c";
    	font-size: 32px;
    }

    .kc_audio_vol_down:before {
    	content: "\\1f509";
    	font-size: 22px;
    }

    .kc_audio_vol_up:before {
    	content: "\\1f50a";
    	font-size: 22px;
    }

    .kc_audio_mute:before {
    	content: "\\1f507";
    	font-size: 22px;
    }

    .kc_media_play_pause:before {
    	content: "\\23ef";
    	font-size: 26px;
    }

    .kc_media_prev_track:before {
    	content: "\\23ee";
    	font-size: 26px;
    }

    .kc_media_next_track:before {
    	content: "\\23ed";
    	font-size: 26px;
    }

    .os_shft:after, .os_ctrl:after, .os_alt:after, .os_cmd:after, .os_caps:after {
        color: #33f;
    	font-size: 11px;
    	font-weight: bold;
    	font-variant: small-caps;
		position: fixed;
		bottom: 0;
		content: "one-shot";
		background-color: #ff8;
		width: 100%;
        border-radius: 0 0 6px 6px;
    }
${extra_css}
</style>
'''

svg_footer = '''
</svg>
'''

svg_layer_title = '''
<text x="${layer_title_x}" y="${layer_title_y}" class="layer_title">${layer_title}</text>
'''

svg_layer_bg = '''
<rect rx="${key_radius}" x="${layer_bg_x}" y="${layer_bg_y}" class="layer_bg" />
'''

svg_key = '''
<foreignObject x="${key_x}" y="${key_y}" width="${key_width}" height="${key_height}" class="text-container">
	<div xmlns="http://www.w3.org/1999/xhtml" lang="en" ${title_attr}class="${key_classes}">${key_label}</div>
</foreignObject>
'''

# ============================================
#   END OF SETTINGS
# ============================================


# Read keymap C file
keymap_file = open(keymap_filename, "r")
keymap_contents = keymap_file.read()
keymap_raw = ""
ledmap_raw = ""

# Extract raw C keymap and ledmap
import re
map_regexp = re.compile(r"^[^]\r\n]+?[a-z]+\[\][^}]+?{$.*?};$", re.MULTILINE | re.DOTALL)
keymap_match = map_regexp.search(keymap_contents)
search_start = 0;
if keymap_match != None:
    keymap_raw = keymap_match.group()
    search_start += keymap_match.span()[1]

# ledmap_match = map_regexp.search(keymap_contents[search_start:])
# if ledmap_match != None:
#     ledmap_raw = ledmap_match.group()

# Parse keys and LED colours into usable data
key_layers = {}
# led_layers = {}
layer_order = []
row_regexp = re.compile(r"^\s*\[([^\]]+)\][^({]+[({]$([^)}]+)[)}]", re.MULTILINE)
key_row_matches = row_regexp.finditer(keymap_raw)
# led_row_matches = row_regexp.finditer(ledmap_raw)
for key_row_match in key_row_matches:
    key_layers.update({key_row_match.group(1): [x.strip() for x in key_row_match.group(2).split(",")]});
    layer_order.append(key_row_match.group(1))
# for led_row_match in led_row_matches:
#     led_layers.update({led_row_match.group(1): [x.strip() for x in led_row_match.group(2).split(",")]});

# Create substitution mappings
layer_names = {
    "_QWERTY": "Base",
    "_NAV": "Navigation &amp; Shortcuts",
    "_NUM": "Numpad",
    "_RSYM": "Symbols (RH)",
    "_LSYM": "Symbols (LH)",
    "_FN": "F keys &amp; Media"
}

# We'll just strip the keycode_prefix if a keycode isn't found in key_names.
keycode_prefix = "KC_"
key_names = {
    "KC_MAC_UNDO": "Undo",
    "KC_MAC_REDO": "Redo",
    "KC_MAC_CUT": "Cut",
    "KC_MAC_COPY": "Copy",
    "KC_MAC_PASTE": "Paste",
    "KC_MAC_LOCK_SCRN": "Lock Screen",
    "KC_MAC_SCRN_SHOT": "Screen Shot",
    "KC_MAC_SCRN_MRKP": "Markup Screen",
    "KC_HOME": "Home",
    "KC_END": "End",
    "PTAB": "Prev Tab",
    "NTAB": "Next Tab",
    "KC_ALF": "Alfred",
    "KC_LSFT": "Shift",
    "KC_LCTL": "Ctrl",
    "KC_LALT": "Option",
    "KC_LGUI": "Cmd",
    "OS_CAPS": "Globe",
    "TH_TAB": "Tab (RSYM)",
    "TH_SPC": "Spc (NAV)",
    "TH_ENT": "Ent (NUM)",
    "TH_BSP": "Bspc (LSYM)",
    "TH_SLS": "/? (FN)",
    "HOME_A": "A (Ctrl)",
    "HOME_S": "S (Alt)",
    "HOME_D": "D (Cmd)",
    "HOME_F": "F (Shft)",
    "HOME_J": "J (Shft)",
    "HOME_K": "K (Cmd)",
    "HOME_L": "L (Alt)",
    "HOME_QT": "' (Ctrl)",
    "APP_SWITCH_FRWD": "Switch App",
    "NAV": "Nav",
    "NUM": "Num",
    "KC__VOLDOWN": "Vol Down",
    "KC__MUTE": "Mute",
    "KC__VOLUP": "Vol Up",
    "KC_MS_ACCEL2": "Mouse Accel 2",
    "KC_MS_WH_DOWN": "Mouse Wheel Down",
    "KC_MS_BTN1": "Left Click",
    "KC_MS_UP": "Mouse &#9650;",
    "KC_MS_BTN2": "Right Click",
    "KC_MS_ACCEL1": "Mouse Accel 1",
    "KC_MS_WH_UP": "Mouse Wheel Up",
    "KC_MS_LEFT": "Mouse &#9664;",
    "KC_MS_DOWN": "Mouse &#9660;",
    "KC_MS_RIGHT": "Mouse &#9654;",
    "KC_BRIGHTNESS_UP": "Screen Bright Up",
    "KC_MPRV": "Prev Track",
    "KC_MPLY": "Play Pause",
    "KC_MNXT": "Next Track",
    "KC_MS_ACCEL0": "Mouse Accel 0",
    "KC_BRIGHTNESS_DOWN": "Screen Bright Down",
    "KC_QUOT": "'\"",
    "KC_COMM": ",",
    "KC_DOT": ".",
    "KC_SLSH": "/",
    "KC_SPC": "Space",
    "KC_ESC": "Esc",
    "KC_PGUP": "Page Up",
    "KC_UP": "Up",
    "KC_BSPC": "Bkspc",
    "KC_DELETE": "Del",
    "KC_TAB": "Tab",
    "KC_PGDN": "Page Down",
    "KC_LEFT": "Left",
    "KC_DOWN": "Down",
    "KC_RIGHT": "Right",
    "KC_ENT": "Enter",
    "KC_SCLN": ";",
    "KC_COLN": ":",
    "KC_PLUS": "+",
    "KC_MINS": "-",
    "KC_EQL": "=",
    "KC_LT": "&lt;",
    "KC_GT": "&gt;",
    "KC_DLR": "$",
    "KC_AT": "@",
    "KC_HASH": "#",
    "KC_GRV": "`",
    "KC_EXLM": "!",
    "KC_DQUO": "\"",
    "KC_LPRN": "(",
    "KC_RPRN": ")",
    "KC_BSLASH": "\\",
    "KC_MINUS": "-",
    "KC_ASTR": "*",
    "KC_EQUAL": "=",
    "KC_LBRC": "[",
    "KC_RBRC": "]",
    "KC_LCBR": "{",
    "KC_RCBR": "}",
    "GBP": "GBP",
    "KC_UNDS": "_",
    "DEG": "DEG",
    "KC_PERC": "%",
    "KC_PIPE": "|",
    "KC_AMPR": "&amp;",
    "KC_CIRC": "^",
    "KC_TILD": "~",
    "PMIN": "+/-",
    # add shifted symbols to numpad keys
    # "KC_1": "1!",
    # "KC_2": "2@",
    # "KC_3": "3#",
    # "KC_4": "4$",
    # "KC_5": "5%",
    # "KC_6": "6^",
    # "KC_7": "7\&",
    # "KC_8": "8*",
    # "KC_9": "9(",
}

# Parse colour values and create mapping
# led_colours = {}
# colours_regexp = re.compile(r"#define\s+(\S+)\s+\{([^\}]+)\}", re.MULTILINE)
# colours_matches = colours_regexp.finditer(keymap_contents)
# for colour_match in colours_matches:
#     led_colours.update({colour_match.group(1): [x.strip() for x in colour_match.group(2).split(",")]});

# Ensure we have at least layout_keys_per_row keys on our base layer.
num_keys = len(key_layers[layer_order[0]])
if num_keys < layout_keys_per_row:
    layout_keys_per_row = num_keys

# Calculate overall viewbox dimensions, paying attention to layout_num_edge_keys_ignored.
import math
num_rows = int(math.ceil(float(num_keys) / float(layout_keys_per_row)))
num_real_cols = layout_keys_per_row
num_cols = num_real_cols
if layout_num_edge_keys_ignored > 0:
    num_cols -= (2 * layout_num_edge_keys_ignored)

layer_width = (num_cols * key_width) + (num_cols * key_spacing)
if layout_split:
    layer_width += split_spacing
else:
    layer_width += key_spacing
svg_width = (2 * diagram_inset) + layer_width

num_layers = len(layer_order)
layer_height = (num_rows * key_height) + ((num_rows + 1) * key_spacing) + last_row_pad
svg_height = (2 * diagram_inset) + (num_layers * layer_height) + ((num_layers - 1) * layer_spacing)
if show_layer_titles:
    svg_height += num_layers * (layer_title_height + layer_title_spacing)

extra_css = ""
from string import Template

# if show_led_colours:
#     colour_css_template = Template('''
#     .text-container > div.${colour_class} {
# 		background-color: rgba(${colour_rgb}, ${led_colours_opacity});
#     }
# ''')
#     for colour in led_colours:
#         colour_class = colour.lower()
#         colour_rgb_vals = led_colours[colour]
#         if not (colour_rgb_vals[0] == "0" and colour_rgb_vals[1] == "0" and colour_rgb_vals[2] == "0"):
#             colour_rgb = ", ".join(colour_rgb_vals)
#             extra_css += colour_css_template.substitute({'colour_class': colour_class,
#                                                          'colour_rgb': colour_rgb,
#                                                          'led_colours_opacity': led_colours_opacity})

# Generate output
svg_raw = ""
svg_layer_header = "" # for per-layer svg output
svg_layers = {} # for per-layer svg output

# Header
svg_classes = []
if show_led_colours:
    svg_classes.append("rgb")
header_template = Template(svg_header)
svg_raw += header_template.substitute({'svg_width': svg_width,
                                       'svg_height': svg_height,
                                       'svg_classes': " ".join(svg_classes),
                                       'key_width': key_width,
                                       'key_height': key_height,
                                       'key_radius': key_radius,
                                       'held_css_class': held_css_class,
                                       'blank_css_class': blank_css_class,
                                       'transparent_css_class': transparent_css_class,
                                       'layer_bg_width': layer_width,
                                       'layer_bg_height': layer_height,
                                       'extra_css': extra_css})
if create_layer_diagrams:
    layer_diagram_height = layer_height + (2 * diagram_inset)
    if show_layer_titles_per_layer:
        layer_diagram_height += (layer_title_height + layer_title_spacing)
    svg_layer_header = header_template.substitute({'svg_width': svg_width,
                                                   'svg_height': layer_diagram_height,
                                                   'svg_classes': " ".join(svg_classes),
                                                   'key_width': key_width,
                                                   'key_height': key_height,
                                                   'key_radius': key_radius,
                                                   'held_css_class': held_css_class,
                                                   'blank_css_class': blank_css_class,
                                                   'transparent_css_class': transparent_css_class,
                                                   'layer_bg_width': layer_width,
                                                   'layer_bg_height': layer_height,
                                                   'extra_css': extra_css})

if show_layer_titles or show_layer_titles_per_layer:
    layer_title_template = Template(svg_layer_title)
    layer_title_x = float(svg_width) / 2.0; # SVG text boxes are positioned at their centre point

layer_bg_template = Template(svg_layer_bg)
key_template = Template(svg_key)

cur_y = diagram_inset
layer_num = 0

def svg_for_layer(layer_id, start_y, show_title):
    svg_raw = ""
    cur_y = start_y
    row_num = 0
    col_num = 0
    cur_x = diagram_inset

    # Layer title
    if show_title:
        layer_title = layer_names[layer_id]
        layer_title_y = float(cur_y) + (float(layer_title_height) / 2.0)
        svg_raw += layer_title_template.substitute({'layer_title_x': layer_title_x,
                                                    'layer_title_y': layer_title_y,
                                                    'layer_title': layer_title})
        cur_y += (layer_title_height + layer_title_spacing)

    # Layer background
    svg_raw += layer_bg_template.substitute({'key_radius': key_radius,
                                             'layer_bg_x': cur_x,
                                             'layer_bg_y': cur_y})

    cur_x += key_spacing
    cur_y += key_spacing

    # Keys
    key_index = 0 # Zero-based
    key_classes = []
    key_label = ""
    layer_keys = key_layers[layer_id]
    for key in layer_keys:
        key_label = key
        key_classes = []

        last_col_num = num_real_cols;
        if row_num == num_rows - 1:
            # Last row may have fewer keys.
            last_col_num = num_keys % ((num_rows - 1) * num_real_cols)

        # Decide whether to output key
        output_key = True
        if layout_num_edge_keys_ignored > 0:
            if col_num < layout_num_edge_keys_ignored or (last_col_num - col_num) <= layout_num_edge_keys_ignored:
                output_key = False

        if output_key:
            # Key's human-readable label
            key_is_transparent = False
            if key == keycode_transparent:
                key_is_transparent = True
                key_classes.append(transparent_css_class)
                if layer_id != layer_order[0]:
                    # Obtain transparent key's effective keycode from base layer
                    key = key_layers[layer_order[0]][key_index]

            if key in key_names:
                key_label = key_names[key]
            elif key.startswith(keycode_prefix):
                key_label = key[len(keycode_prefix):]
            elif key == keycode_blank:
                key_classes.append(blank_css_class)
                key_label = ""

            # CSS classes to apply to the key container
            if layer_id in layer_held_keycodes and key in layer_held_keycodes[layer_id]:
                key_classes.append(held_css_class)
            if show_led_colours and layer_id in led_layers:
                key_classes.append(led_layers[layer_id][key_index].lower())
            if apply_keycode_class and key not in [keycode_blank, keycode_transparent]:
                key_classes.append(key.lower())

            title_attr = ""
            title_val = key
            if apply_keycode_title:
                if key_is_transparent:
                    title_val = keycode_transparent
                title_attr = 'title="%s" ' % title_val

            svg_raw += key_template.substitute({'key_radius': key_radius,
                                                'key_x': cur_x,
                                                'key_y': cur_y,
                                                'title_attr': title_attr,
                                                'key_classes': " ".join(key_classes),
                                                'key_width': key_width,
                                                'key_height': key_height,
                                                'key_label': key_label})

        # Prep for next key
        key_index += 1
        if (key_index % num_real_cols == 0) or (key_index == num_keys):
            # Start of a new row
            cur_x = diagram_inset + key_spacing
            cur_y += (key_spacing + key_height)
            row_num += 1
            col_num = 0
            if row_num == num_rows - 1:
                # Last row
                cur_y += last_row_pad

                last_col_num = num_keys % ((num_rows - 1) * num_real_cols)
                if last_col_num < num_real_cols:
                    # Fewer keys in last row; indent them so they're still centred.
                    cur_x += (((num_real_cols - last_col_num) / 2) * (key_spacing + key_width))
        else:
            # Continue current row
            if output_key:
                cur_x += key_width
            col_num += 1
            if col_num == last_col_num / 2 and layout_split:
                cur_x += split_spacing
            elif output_key:
                cur_x += key_spacing

    return {'svg': svg_raw, 'delta_y': cur_y - start_y}

for layer_id in layer_order:
    layer_svg_data = svg_for_layer(layer_id, cur_y, show_layer_titles)
    svg_raw += layer_svg_data['svg']

    # Prep for next layer
    layer_num += 1
    cur_y += layer_spacing + layer_svg_data['delta_y']

    if create_layer_diagrams:
        layer_svg_data = svg_for_layer(layer_id, diagram_inset, show_layer_titles_per_layer)
        svg_layers[layer_id] = svg_layer_header + layer_svg_data['svg'] + svg_footer

# Footer
svg_raw += svg_footer # no vars in this, so it can be included literally

# Write out SVG file.
svg_file = open(svg_filename, "w")
svg_file.write(svg_raw)
svg_file.close()
# Got to love Python.

if create_layer_diagrams:
    for layer_id in svg_layers:
        svg_filename_components = svg_filename.split(".")
        svg_filename_root = svg_filename_components[0]
        svg_filename_ext = svg_filename_components[1]
        layer_filename = svg_filename_root + "_" + layer_id.lstrip("_").lower() + "." + svg_filename_ext
        svg_file = open(layer_filename, "w")
        svg_file.write(svg_layers[layer_id])
        svg_file.close()
