#include "kerncompat.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#if BTRFS_FLAT_INCLUDES
#else
#endif /* BTRFS_FLAT_INCLUDES */

/*
 * This function should be only used when parsing command arg, it won't return
 * error to its caller and rather exit directly just like usage().
 * error occur:set ret -1,the returned value is invalid.
 */
u64 arg_strtou64(const char *str,int *ret)
{
	u64 value;
	char *ptr_parse_end = NULL;
    *ret = 0;

	value = strtoull(str, &ptr_parse_end, 0);
	if (ptr_parse_end && *ptr_parse_end != '\0') {
		fprintf(stderr, "ERROR: %s is not a valid numeric value.\n",
			str);
		*ret = -1;
        return value;
	}

	/*
	 * if we pass a negative number to strtoull, it will return an
	 * unexpected number to us, so let's do the check ourselves.
	 */
	if (str[0] == '-') {
		fprintf(stderr, "ERROR: %s: negative value is invalid.\n",
			str);
		*ret = -1;
        return value;
	}
	if (value == ULLONG_MAX) {
		fprintf(stderr, "ERROR: %s is too large.\n", str);
		*ret = -1;
        return value;
	}
	return value;
}
