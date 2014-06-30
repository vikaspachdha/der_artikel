
INCLUDEPATH += $$PWD/.. \
    $$PWD/../libs/tiny_aes \
    $$PWD/../libs/log4qt

DEPENDPATH += $$PWD

HEADERS += $$PWD/result.h \
    $$PWD/thema_interface.h \
    $$PWD/thema.h \
    $$PWD/word.h \
    $$PWD/article.h \
    $$PWD/version.h \
    $$PWD/common.h \
    $$PWD/word_model.h \
    $$PWD/thema_loader.h \
    $$PWD/thema_model.h

SOURCES += $$PWD/result.cpp \
    $$PWD/thema.cpp \
    $$PWD/word.cpp \
    $$PWD/article.cpp \
    $$PWD/common.cpp \
    $$PWD/word_model.cpp \
    $$PWD/thema_loader.cpp \
    $$PWD/thema_model.cpp


