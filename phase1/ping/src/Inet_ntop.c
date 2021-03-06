/*
 * Inet_ntop.c
 *
 *  Created on: May 6, 2015
 *      Author: louis
 */
#include "yamorn.h"

static char *__inet_ntop(const struct sockaddr *, socklen_t);

char *Inet_ntop(const struct sockaddr *sa, socklen_t salen) {
	char *ptr;
	if ((ptr = __inet_ntop(sa, salen)) == NULL) {
		perror("Inet_ntop");
		exit(1);
	}
	return (ptr);
}

static char *__inet_ntop(const struct sockaddr *sa, socklen_t salen) {
	static char str[128]; /* unix domain is largest */
	switch (sa->sa_family) {
	case AF_INET: {
		struct sockaddr_in *sin = (struct sockaddr_in *) sa;
		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			return (NULL);
		return (str);
	}
	case AF_INET6: {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa;
		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
			return (NULL);
		return (str);
	}
	default:
		snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d",
				sa->sa_family, salen);
		return (str);
	}
	return (NULL);

}
