#include <libintl.h>
#include <string>

#define _(String) std::string(gettext(String))
