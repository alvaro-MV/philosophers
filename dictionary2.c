/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:31 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/13 02:04:09 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dictionary.h"

int	dict_get(t_dictionary *dic, char *key)
{
	unsigned int	index;
	unsigned int	counter;

	if (key == NULL)
		return (NULL);
	index = dict_hash(key) % dic->capacity;
	counter = 0;
	while (counter < dic->capacity - 1)
	{
		if (dic->entries[index]
			&& !strcmp(dic->entries[index]->key, key))
			return (dic->entries[index]->fork_held);
		index++;
		if (index == dic->capacity - 1)
			index = 0;
		counter++;
	}
	return (NULL);
}

unsigned int	dict_hash(char *key)
{
	unsigned int	hash;
	int				i;
	int				length;

	hash = 2166136261u;
	i = 0;
	length = ft_strlen(key);
	while (i < length)
	{
		hash ^= (uint8_t) key[i];
		hash *= 16777619;
		i++;
	}
	return (hash);
}

void	dict_delete(t_dictionary *dic)
{
	unsigned int	i;

	i = 0;
	while (i < dic->capacity)
	{
		if (dic->entries[i] != NULL)
		{
			free(dic->entries[i]->key);
			//free(dic->entries[i]->value);
		}
		free(dic->entries[i]);
		i++;
	}
	free(dic->entries);
	free(dic);
}
