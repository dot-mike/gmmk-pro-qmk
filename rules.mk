FIRMWARE_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

TAP_DANCE_ENABLE = yes
ENCODER_ENABLE = yes
VIA_ENABLE = yes
BUILD_DIR=$(FIRMWARE_DIR)/build