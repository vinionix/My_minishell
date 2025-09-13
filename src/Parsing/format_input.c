#include "../consha.h"

static int	handle_quotes(char *input, char *temp, int *i, int j)
{
	int	chr_jump;

	chr_jump = jump_char(input[*i]);
	if (chr_jump == 2 || chr_jump == 3)
	{
		if (not_interpret(input, *i))
			return (j);
		temp[j++] = input[(*i)++];
		while (input[*i] && chr_jump != jump_char(input[*i]))
			temp[j++] = input[(*i)++];
		if (input[*i] == '\0')
		{
			printf("Error\n");
			free(temp);
			return (-1);
		}
	}
	return (j);
}

static int	handle_sep_type1(char *input, char *temp, int *i, int j)
{
	if ((*i > 0) && jump_char(input[*i - 1]) != 1
		&& chr_separator(input, *i - 1) == 0)
		temp[j++] = ' ';
	if (input[*i + 1])
	{
		temp[j++] = input[(*i)++];
		temp[j++] = input[(*i)++];
	}
	if (input[*i] && jump_char(input[*i]) != 1)
		temp[j++] = ' ';
	return (j);
}

static int	handle_sep_type2(char *input, char *temp, int *i, int j)
{
	if ((*i > 0) && jump_char(input[*i - 1]) != 1
		&& chr_separator(input, *i - 1) == 0)
		temp[j++] = ' ';
	temp[j++] = input[(*i)++];
	if (jump_char(input[*i]) != 1)
		temp[j++] = ' ';
	return (j);
}

char	*format_input(char *input)
{
	int		i;
	int		j;
	char	*temp;
	int		receiver;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(input) * 4 + 1));
	if (!temp)
		return (NULL);
	while (input[i])
	{
		j = handle_quotes(input, temp, &i, j);
		if (j == -1)
			return (NULL);
		receiver = chr_separator(input, i);
		if (receiver >= 1 && receiver <= 4)
			j = handle_sep_type1(input, temp, &i, j);
		else if (receiver >= 5 && receiver <= 9)
			j = handle_sep_type2(input, temp, &i, j);
		else if (receiver == 0)
			temp[j++] = input[i++];
	}
	temp[j] = '\0';
	return (temp);
}
