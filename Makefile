# NOTE: Don't name the QMK Configurator JSON keymap file as "keymap.json"
# because `qmk compile` directly translates it into C and compiles it too,
# thereby completely bypassing this Makefile and our keymap header/footer!

TOPLEVEL=`git rev-parse --show-toplevel`
# KEYBOARD=totem
KEYMAP=fride
USER_DIR=$(realpath ./user)
TOTEM_DIR=$(realpath ./totem)
PLANCK_DIR=$(realpath ./planck/keymaps/fride)
QMK_HOME=/Users/jgf/code/private/qmk_firmware
QMK_USER_DIR=$(QMK_HOME)/users/fride
QMK_KEYBOARDS_DIR=$(QMK_HOME)/keyboards
QMK_TOTEM_DIR=$(QMK_KEYBOARDS_DIR)/totem
QMK_PLANCK_DIR=$(QMK_KEYBOARDS_DIR)/planck/keymaps/fride

$(QMK_USER_DIR):
	ln -s $(USER_DIR) $(QMK_USER_DIR)

$(QMK_TOTEM_DIR):
	ln -s $(TOTEM_DIR) $(QMK_TOTEM_DIR)

$(QMK_PLANCK_DIR):	
	ln -s $(PLANCK_DIR) $(QMK_PLANCK_DIR)

build_planck:$(QMK_USER_DIR) $(QMK_PLANCK_DIR) 
	test ! -e keymap.json # see comment at the top of this Makefile
	qmk compile -kb planck/rev6 -km $(KEYMAP) -j 0


flash: build
	qmk flash -kb $(KEYBOARD) -km $(KEYMAP)

build: $(QMK_USER_DIR) $(QMK_TOTEM_DIR) 
	test ! -e keymap.json # see comment at the top of this Makefile
	qmk compile -kb $(KEYBOARD) -km $(KEYMAP) -j 0

clean:
	qmk clean

clobber: clean
	rm -fv keymap.c keymap_config_converted.json
	rm -fv $(TOPLEVEL)/$$( echo $(KEYBOARD) | tr / _ )_$(KEYMAP).*

.PHONY: clean clobber build flash totem redox

totem : KEYBOARD="totem"
totem : flash

redox : KEYBOARD=redox
redox : flash