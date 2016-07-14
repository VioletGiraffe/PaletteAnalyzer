TEMPLATE = subdirs

SUBDIRS = app cpputils core qtutils cpp-template-utils

core.depends = cpputils qtutils

qtutils.depends = cpputils

app.depends = core qtutils cpputils
