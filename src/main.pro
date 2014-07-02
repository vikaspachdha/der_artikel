DEFINES += ENCRYPT_DATA
TEMPLATE = subdirs
SUBDIRS = libs/log4qt \
    libs/tiny_aes \
    der_artikel \
    thema_builder \
    unit_tests

CONFIG += ordered
