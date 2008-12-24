#undef _
#undef gettext_noop
#undef N_

#include "gettext.h"

#define _(String) gettext (String)
#define gettext_noop(String) String
#define N_(String) gettext_noop (String)


