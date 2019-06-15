contains(DEFINES, NO_XITS_FONTS) {
  warning("NO_XITS_FONTS was defined ==> we do not link XITS fonts as ressource ... Think about installing them separately on the target machine")
} else {
  RESOURCES += $$PWD/xits.qrc
}
