#include "buildins.h"
#include <stdio.h>

t_list	*read_env(char **strs)
{
	int i;
	t_list *env_list;
	t_env *var;
	char **tmp;

	env_list = NULL;
	i = 0;
	while (strs[i])
	{
		tmp = ft_split(strs[i], '=');
		var = malloc(sizeof (t_env));
		var->name = ft_strdup(tmp[0]);
		var->val = ft_strdup(tmp[1]);
		ft_lstadd_back(&env_list, ft_lstnew(var));
		while(*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(tmp - 2);
		i++;
	}
	return (env_list);
}

void print_env(t_list **env_list)
{
	t_list	*tmp;
	t_env	*var;

	if (*env_list)
		tmp = *env_list;
	while (tmp->next)
	{
		var = tmp->content;
		printf("%s = %s\n", var->name, var->val);
		tmp = tmp->next;
	}
}

t_env  *get_env_by_name(t_list **env_list, char *name)
{
	t_list *tmp;
	t_env *var;

	if (*env_list)
		tmp = *env_list;
	while (tmp->next)
	{
		var = tmp->content;
		if (ft_strncmp(var->name, name, ft_strlen(var->name)) == 0)
			return (var);
		tmp = tmp->next;
	}
	return (NULL);
}
