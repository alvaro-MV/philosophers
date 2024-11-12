/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:09:28 by alvmoral          #+#    #+#             */
/*   Updated: 2024/11/12 22:09:29 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dictionary.h"

t_dictionary	*dict_init(int capacity)
{
	t_dictionary	*dic;
	t_dic_entry		**entries;
	int				dic_capacity;

	dic = (t_dictionary *) malloc(sizeof(t_dictionary));
	if (!dic)
		return (NULL);
	if (capacity <= 0)
		dic_capacity = INITIAL_CAPACITY;
	else
		dic_capacity = capacity;
	dic->capacity = dic_capacity;
	dic->n_elements = 0;
	entries = (t_dic_entry **) malloc(dic_capacity * sizeof(t_dic_entry *));
	if (!entries)
	{
		free(dic);
		return (NULL);
	}
	dic->entries = entries;
	while (dic_capacity--)
		dic->entries[dic_capacity] = NULL;
	return (dic);
}

void	dict_insert(t_dictionary **dic_p, t_dic_entry *entry)
{
	unsigned int	hash_entry;
	unsigned int	index;
	t_dictionary	*dic;

	if (entry->key == NULL)
		return ;
	dic = *dic_p;
	if (dic->n_elements > (dic->capacity / 2))
	{
		if (!dict_expand(dic_p))
			return (dict_delete(dic));
		dic = *dic_p;
	}
	hash_entry = dict_hash(entry->key);
	index = hash_entry % dic->capacity;
	while (dic->entries[index] != NULL)
	{
		index++;
		if (index == dic->capacity - 1)
			index = 0;
	}
	dic->entries[index] = entry;
	dic->n_elements++;
	*dic_p = dic;
}

static void	map_old_values(t_dictionary *old_dic, t_dictionary *new_dic)
{
	unsigned int	i;
	unsigned int	new_index;
	unsigned int	new_capacity;

	i = 0;
	new_capacity = new_dic->capacity;
	while (i < old_dic->capacity)
	{
		if (old_dic->entries[i] != NULL)
		{
			new_index = dict_hash(old_dic->entries[i]->key) % new_capacity;
			while (new_dic->entries[new_index] != NULL)
			{
				new_index++;
				if (new_index == new_dic->capacity - 1)
					new_index = 0;
			}
			new_dic->entries[new_index] = old_dic->entries[i];
		}
		i++;
	}
}

int	dict_expand(t_dictionary **dic_pointer)
{
	int				new_capacity;
	t_dictionary	*old_dic;
	t_dictionary	*new_dic;

	old_dic = *dic_pointer;
	new_capacity = old_dic->capacity * 2;
	new_dic = dict_init(new_capacity);
	if (new_dic == NULL)
		return (0);
	map_old_values(old_dic, new_dic);
	free(old_dic->entries);
	free(old_dic);
	*dic_pointer = new_dic;
	return (1);
}
