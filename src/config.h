#ifndef CONFIG_H_
#define CONFIG_H_

#if defined(DARWIN)
#include "darwin_config.h"

#elif defined(WINDOWS)
#include "win_config.h"

#elif defined(UNIX)
#include "linux_config.h"

#endif

#endif /* CONFIG_H_ */