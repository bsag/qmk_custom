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
layout_keys_per_row = 10 # last row (only) can have fewer keys
layout_num_edge_keys_ignored = 0 # first and last x keys per row won't be displayed in diagram
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
led_colours_lightness = 0.85 # 0.0 to 1.0

# Layers
show_layer_titles = True # applies to single overall diagram
show_layer_titles_per_layer = False # applies to separate layer-specific diagrams
layer_title_height = 20 # text box height; set font attributes in CSS below
layer_title_spacing = 10 # vertical spacing between layer title and its layer diagram
held_css_class = "held" # CSS class applied to keys which are held down on a given layer, i.e. MO(); edit the actual CSS below.
keycode_blank = "NO"
blank_css_class = "blank" # as above, applied to keys with no function (i.e. keycode_blank above).
keycode_transparent = "KC_TRNS"
transparent_css_class = "transparent" # as above, applied to transparent keys (falling through to base layer; i.e. keycode_transparent above).
# Note: Transparent keys (on non-base layers) will be labelled identically to the corresponding key on the base layer.
annotation_keycodes = { # keycodes with annotations
    "layer": {"keycodes": ["NAV_SPC", "NUM", "SYM", "FUN", "WNAV"],
              "label": "layer"},
    "one-shot": {"keycodes": ["OS_SHFT", "OS_CTRL", "OS_ALT", "OS_CMD"],
                 "label": "one-shot"},
    held_css_class: {"keycodes": [], # special case, to provide label for held layer keys
                     "label": "held"},
}
layer_held_keycodes = { # keycodes whose keys are implicitly held down on a given layer, gaining the held_css_class specified below
  "_NAV": ["NAV_SPC"],
  "_NUM": ["NUM"],
  "_SYM": ["SYM"],
  "_WNAV": ["KC_LSFT", "NAV_SPC"],
  "_FUN": ["NUM", "SYM"]
}

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

    .text-container > div {
        cursor: default;
        box-sizing: border-box;
        background-color: #f0f0f0;
        text-align: center;
        width: ${key_width}px;
        height: ${key_height}px;
        border-radius: ${key_radius}px;
        display: flex;
        flex-direction: column;
		overflow: hidden;
    }

    .glyph {
        padding: 1px 2px;
        display: flex;
        justify-content: center;
        align-items: center;
        hyphens: auto;
        -webkit-hyphens: auto;
        -moz-hyphens: auto;
        -ms-hyphens: auto;
		flex: 1 0 auto;
    }

    .text-container > div:after {
        box-sizing: border-box;
        font-size: 11px;
    	font-weight: bold;
    	font-variant: small-caps;
		position: fixed;
		bottom: 0;
		padding-bottom: 1px;
		width: 100%;
		display: none;
    }

    .text-container > div.${held_css_class} > .glyph {
        background-color: #bbf;
    }

    .rgb .text-container > div.${held_css_class} > .glyph {
        background-color: initial;
        border: 3px solid #00e;
        border-bottom-width: 0;
        border-radius: ${key_radius}px ${key_radius}px 0 0;
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
    .kc_lsft, .nav_spc,
    .kc_exlm, .kc_at, .kc_hash, .kc_dlr, .kc_perc,
    .kc_ampr, .kc_astr, .kc_unds, .kc_mins,
    .kc_pipe, .kc_scln, .kc_eql, .kc_coln, .kc_tild,
    .kc_lt, .kc_gt, .kc_grv, .kc_circ, .kc_plus, .kc_bsls,
    .kc_quot, .kc_dot, .kc_comm, .kc_slsh,
    .os_shft, .os_ctrl, .os_alt, .os_cmd,
    .kc_mac_spotlight, .kc_pgup, .kc_pgdn,
    .kc_mac_undo, .kc_mac_redo, .kc_tab,
    .kc_mac_cut, .kc_spc, .kc_mac_lock_scrn,
    .kc_brightness_up, .kc_brightness_down,
    .kc_volu, .kc_vold, .kc_mute,
    .kc_mply, .kc_mprv, .kc_mnxt {
    	font-size: 18px;
    }

    .kc_bspc {
    	font-size: 22px;
    }

    .os_caps {
    	font-size: 19px;
    	padding-top: 4px !important;
    }

    .kc_mac_spotlight {
    	font-size: 40px;
    }

    .kc_mac_undo {
    	font-size: 34px;
    }

    .kc_mac_redo {
    	font-size: 34px;
    }

    .kc_mac_cut {
    	font-size: 20px;
    }

    .kc_spc {
    	font-size: 24px;
    }

    .kc_mac_lock_scrn {
    	font-size: 22px;
    }

    .kc_brightness_up {
    	font-size: 28px;
    }

    .kc_brightness_down {
    	font-size: 32px;
    }

    .kc_audio_vol_down {
    	font-size: 22px;
    }

    .kc_audio_vol_up {
    	font-size: 22px;
    }

    .kc_audio_mute {
    	font-size: 22px;
    }

    .kc_media_play_pause {
    	font-size: 26px;
    }

    .kc_media_prev_track {
    	font-size: 26px;
    }

    .kc_media_next_track {
    	font-size: 26px;
    }

    .annotation {
        box-sizing: border-box;
        font-size: 11px;
    	font-weight: bold;
    	font-variant: small-caps;
		padding-bottom: 2px;
		width: 100%;
        color: #f6f6f6;
		background-color: #666;
    }

    .${held_css_class} .annotation.layer {
        background-color: #00e;
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
	<div xmlns="http://www.w3.org/1999/xhtml" lang="en" ${title_attr}class="${key_classes}"><div class="glyph">${key_label}</div>${annotation}</div>
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

ledmap_match = map_regexp.search(keymap_contents[search_start:])
if ledmap_match != None:
    ledmap_raw = ledmap_match.group()

# Parse keys and LED colours into usable data
key_layers = {}
led_layers = {}
layer_order = []
row_regexp = re.compile(r"^\s*\[([^\]]+)\][^({]+[({]$([^)}]+)[)}]", re.MULTILINE)
key_row_matches = row_regexp.finditer(keymap_raw)
led_row_matches = row_regexp.finditer(ledmap_raw)
for key_row_match in key_row_matches:
    key_layers.update({key_row_match.group(1): [x.strip() for x in key_row_match.group(2).split(",")]});
    layer_order.append(key_row_match.group(1))
for led_row_match in led_row_matches:
    led_layers.update({led_row_match.group(1): [x.strip() for x in led_row_match.group(2).split(",")]});

# Create substitution mappings
layer_names = {
  "_BKL": "Base - BEAKL27",
  "_DEF": "QWERTY",
  "_NUM": "Numbers",
  "_SYM": "Symbols",
  "_NAV": "Navigation &amp; shortcuts",
  "_WNAV": "Workspace navigation",
  "_FUN": "F keys",
}

# We'll just strip the keycode_prefix if a keycode isn't found in key_names.
keycode_prefix = "KC_"
key_names = {
    "KC_NO": {"label": "", "title": ""},
    "M_UNDO": {"label": "Undo", "title": "Undo"},
    "M_CUT": {"label": "Cut", "title": "Cut"},
    "M_COPY": {"label": "Copy", "title": ""},
    "M_PSTE": {"label": "Paste", "title": ""},
    "M_SAVE": {"label": "Save", "title": ""},
    "W1": {"label": "W1", "title": ""},
    "W2": {"label": "W2", "title": ""},
    "W3": {"label": "W3", "title": ""},
    "W4": {"label": "W4", "title": ""},
    "W5": {"label": "W5", "title": ""},
    "W6": {"label": "W6", "title": ""},
    "TG_QWTY": {"label": "To QWERTY", "title": ""},
    "KC_HOME": {"label": "Home", "title": ""},
    "KC_END": {"label": "End", "title": ""},
    "KC_DEL": {"label": "Del", "title": ""},
    "TAB_L": {"label": "Prev Tab", "title": ""},
    "TAB_R": {"label": "Next Tab", "title": ""},
    "ALF": {"label": "Alfred", "title": "Alfred"},
    "HOOK": {"label": "Hook", "title": "Hook"},
    "LHLF": {"label": "Resize left", "title": ""},
    "RHLF": {"label": "Resize right", "title": ""},
    "FULL": {"label": "Resize full", "title": ""},
    "OS_SHFT": {"label": "&#8679;", "title": "Shift"},
    "OS_CTRL": {"label": "&#94;", "title": "Control"},
    "OS_ALT": {"label": "&#8997;", "title": "Option"},
    "OS_CMD": {"label": "&#8984;", "title": "Command"},
    "SW_APP": {"label": "Switch App", "title": ""},
    "KC_LSFT": {"label": "&#8679;", "title": "Shift"},
    "NAV_SPC": {"label": "&#9251;", "title": ""},
    "NUM": {"label": "Num", "title": ""},
    "SYM": {"label": "Sym", "title": ""},
    "WNAV": {"label": "Work space", "title": ""},
    "FUN": {"label": "Fun", "title": ""},
    "KC_VOLD": {"label": "&#128265;", "title": "Volume Down"},
    "KC_MUTE": {"label": "&#128263;", "title": "Mute"},
    "KC_VOLU": {"label": "&#128266;", "title": "Volume Up"},
    "KC_MPRV": {"label": "&#9198;", "title": "Previous Track"},
    "KC_MPLY": {"label": "&#9199;", "title": "Play/Pause"},
    "KC_MNXT": {"label": "&#9197;", "title": "Next Track"},
    "KC_QUOT": {"label": "'", "title": ""},
    "KC_COMM": {"label": ",", "title": ""},
    "KC_DOT": {"label": ".", "title": ""},
    "KC_SLSH": {"label": "/", "title": ""},
    "KC_SPC": {"label": "&#9251;", "title": "Space"},
    "KC_ESC": {"label": "&#9099;", "title": "Escape"},
    "KC_PGUP": {"label": "&#8670;", "title": "Page Up"},
    "KC_UP": {"label": "&#9650;", "title": "Up"},
    "KC_BSPC": {"label": "&#9003;", "title": "Backspace"},
    "KC_TAB": {"label": "&#8677;", "title": "Tab"},
    "KC_PGDN": {"label": "&#8671;", "title": "Page Down"},
    "KC_LEFT": {"label": "&#9664;", "title": "Left"},
    "KC_DOWN": {"label": "&#9660;", "title": "Down"},
    "KC_RGHT": {"label": "&#9654;", "title": "Right"},
    "KC_ENT": {"label": "&#9166;", "title": "Enter"},
    "KC_SCLN": {"label": ";", "title": ""},
    "KC_LPRN": {"label": "(", "title": ""},
    "KC_RPRN": {"label": ")", "title": ""},
    "KC_BSLS": {"label": "\\", "title": ""},
    "KC_MINS": {"label": "-", "title": ""},
    "KC_ASTR": {"label": "*", "title": ""},
    "KC_EQL": {"label": "=", "title": ""},
    "KC_EXLM": {"label": "&#33;", "title": ""},
    "KC_AT": {"label": "&#64;", "title": ""},
    "KC_HASH": {"label": "&#35;", "title": ""},
    "KC_DLR": {"label": "&#36;", "title": ""},
    "KC_PERC": {"label": "&#37;", "title": ""},
    "KC_PIPE": {"label": "&#124;", "title": ""},
    "KC_COLN": {"label": "&#58;", "title": ""},
    "KC_TILD": {"label": "&#126;", "title": ""},
    "KC_LT": {"label": "&#60;", "title": ""},
    "KC_GT": {"label": "&#62;", "title": ""},
    "GBPD": {"label": "&#163;", "title": ""},
    "KC_AMPR": {"label": "&#38;", "title": ""},
    "KC_UNDS": {"label": "&#95;", "title": ""},
    "PMIN": {"label": "&#177;", "title": ""},
    "KC_CIRC": {"label": "&#94;", "title": ""},
    "KC_PLUS": {"label": "&#43;", "title": ""},
    "KC_LBRACKET": {"label": "[", "title": ""},
    "KC_RBRACKET": {"label": "]", "title": ""},
    "KC_GRV": {"label": "`", "title": ""},
}

# Parse colour values and create mapping
led_colours = {}
colours_regexp = re.compile(r"#define\s+(\S+)\s+\{([^\}]+)\}", re.MULTILINE)
colours_matches = colours_regexp.finditer(keymap_contents)
colour_rgb = []
import colorsys
for colour_match in colours_matches:
    colour_rgb_str = [x.strip() for x in colour_match.group(2).split(",")]
    colour_rgb = []
    for component_rgb in colour_rgb_str:
        colour_rgb.append(float(component_rgb) / float(255))
    colour_hsl = colorsys.rgb_to_hsv(colour_rgb[0], colour_rgb[1], colour_rgb[2])
    lightness = colour_hsl[2]
    if not (colour_hsl[0] == 0 and colour_hsl[1] == 0):
        lightness = led_colours_lightness
    led_colours.update({colour_match.group(1): [colour_hsl[0], colour_hsl[1], lightness]});

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

if show_led_colours:
    colour_css_template = Template('''
    .text-container > div.${colour_class} {
		background-color: hsl(${colour_hsl});
    }
''')
    for colour in led_colours:
        colour_class = colour.lower()
        colour_hsl_vals = led_colours[colour]
        if not (colour_hsl_vals[2] == 0):
            colour_hsl = "%f, %f%%, %f%%" % (colour_hsl_vals[0] * 360.0,
                                             colour_hsl_vals[1] * 100.0,
                                             colour_hsl_vals[2] * 100.0)
            extra_css += colour_css_template.substitute({'colour_class': colour_class,
                                                         'colour_hsl': colour_hsl})

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
                key_label = key_names[key]["label"]
            elif key.startswith(keycode_prefix):
                key_label = key[len(keycode_prefix):]
            elif key == keycode_blank:
                key_classes.append(blank_css_class)
                key_label = ""

            # CSS classes to apply to the key container
            key_is_held = (layer_id in layer_held_keycodes and key in layer_held_keycodes[layer_id])
            if key_is_held:
                key_classes.append(held_css_class)
            if show_led_colours and layer_id in led_layers:
                key_classes.append(led_layers[layer_id][key_index].lower())
            if apply_keycode_class and key not in [keycode_blank, keycode_transparent]:
                key_classes.append(key.lower())

            # Title attribute
            title_attr = ""
            title_val = ""
            if key in key_names:
                title_val = key_names[key]["title"]
            title_keycode = key
            if key_is_transparent:
                title_keycode = keycode_transparent
            if title_val != "" and apply_keycode_title:
                title_attr = 'title="%s (%s)" ' % (title_val, title_keycode)
            elif title_val != "":
                title_attr = 'title="%s" ' % (title_val)
            elif apply_keycode_title:
                title_attr = 'title="%s" ' % (title_keycode)

            # Annotation
            annotation = ""
            for ann_class in annotation_keycodes:
                if key in annotation_keycodes[ann_class]["keycodes"]:
                    ann_content = annotation_keycodes[ann_class]["label"]
                    if key_is_held:
                        ann_content = annotation_keycodes[held_css_class]["label"]
                    annotation = '<div class="annotation %s">%s</div>' % (ann_class, ann_content)
                    break;
            # <div class="annotation one-shot">one-shot</div>

            # Process key template
            svg_raw += key_template.substitute({'key_radius': key_radius,
                                                'key_x': cur_x,
                                                'key_y': cur_y,
                                                'title_attr': title_attr,
                                                'key_classes': " ".join(key_classes),
                                                'key_width': key_width,
                                                'key_height': key_height,
                                                'key_label': key_label,
                                                'annotation': annotation})

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
