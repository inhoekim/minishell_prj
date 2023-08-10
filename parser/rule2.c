#include "../include/minishell.h"
#include "../include/tokenizer.h"

// command ::= simple_cmd
// command ::= ssh io_redirect_star
t_node *command(t_tokenizer tokenizer)
{
	t_node  *parent;
	t_node  *child;

	if (check_first_set(SIMPLE_CMD))
	{
		parent = simple_cmd(tokenizer);
		return (parent);
	}
	else if (match_token(SUBSHELL_LEFT))
	{
		child = ssh(tokenizer);
		if (child)
		{
			parent = io_redirect_star(tokenizer);
			if (parent)
				return (merge_tree(parent, child));
		}
		return (child);
	}
	syntax_error("Not available grammar");
	return (NULL);
}

// ssh ::= LBRACE msh_grammar RBRACE
t_node  *ssh(t_tokenizer tokenizer)
{
	t_node  *parent;

	if (match_token(SUBSHELL_LEFT))
	{
		parent = msh_grammar(tokenizer);
		if (match_token(SUBSHELL_RIGHT))
			return (make_tree(SUBSHELL, parent, NULL));
	}
	syntax_error("Not available grammar");
	return (NULL);
}
//simple_cmd ::= WORD io_redirect_or_word_star
//simple_cmd ::= io_redirect_dagger io_redirect_dg_after_simple_cmd
t_node  *simple_cmd(t_tokenizer tokenizer)
{
	t_node  *parent;
	t_node  *child;

	if (match_token(WORD))
	{
		child = make_node(WORD, tokenizer);
		parent = io_redirect_or_word_star(tokenizer);
		if (child)
			return (merge_tree(parent, child));
		return (parent);
	}
	else if (check_first_set(IO_REDIRECT))
	{
		parent = io_redirect_dagger(tokenizer);
		if (parent)
		{
			child = io_redirect_dg_after_simple_cmd(tokenizer);
			if (child)
				return (make_tree(parent, child));
		}
	}
	syntax_error("Not available grammar");
	return (NULL);
}

//io_redirect_or_word_star ::= io_redirect io_redirect_or_word_star
//io_redirect_or_word_star ::= WORD io_redirect_or_word_star
//io_redirect_or_word_star ::= empty
t_node  *io_redirect_or_word_star(t_tokenizer tokenizer)
{
	t_node  *parent;
	t_node  *child;

	if (check_first_set(IO_REDIRECT))
	{
		parent = io_redirect(tokenizer);
		child = io_redirect_or_word_star(tokenizer);
		return (merge_tree(parent, child));
	}
	else if (check_first_set(WORD))
	{
		child = make_node(WORD, tokenizer);
		parent = io_redirect_or_word_star(tokenizer);
		return (merge_tree(parent, child)); //만약 word-word가 만나면 child word + parent word = new word가 되어야함
	}
	return (NULL);
}

// io_redirect_dagger ::= io_redirect io_redirect_star
t_node  *io_redirect_dagger(t_tokenizer tokenizer)
{
	t_node  *parent;
	t_node  *child;
	if (check_first_set(IO_REDIRECT))
	{
		parent = io_redirect(tokenizer);
		child = io_redirect_star(tokenizer);
		return (merge_tree(parent, child));
	}
	syntax_error("Not available grammar");
	return (NULL);
}
