#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char    *ptr;
	size_t  init;

	if (start > ft_strlen(s))
			len = 0;
	else if (len > ft_strlen(s) - start)
			len = ft_strlen(s) - start;
	ptr = (char *) ft_calloc(len + 1, sizeof(char));
	if (ptr == NULL)
			return (NULL);
	init = 0;
	while (s[init] && len--)
	{
			ptr[init++] = s[start++];
	}
	ptr[init] = ""[0];
	return (ptr);
}