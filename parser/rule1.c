#include "../include/minishell.h"
#include "../include/tokenizer.h"

// msh_grammar ::= pipeline conditional
t_node *msh_grammar(t_tokenizer tokenizer)
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(PIPELINE, get_curr_token()))
    {
        child = pipeline();
        if (child)
        {
            parent = conditional();
            if (parent)
                return (merge_tree(parent, child));
        }
		return (child);
    }
    syntax_error("Not available grammar");
    return (NULL);
}

// conditional ::= AND pipeline conditional
// conditional ::= OR pipeline conditional
// conditional ::= empty
t_node *conditional(t_tokenizer tokenizer)
{
    t_node  *pipe;
    t_node  *parent;
	t_node  *child;

    if (match_token(AND_IF))
    {
		pipe = pipeline();
		parent = conditional();
		child = make_tree(AND_IF, NULL, pipe);
		return (merge_tree(parent, child));
    }
    else if (match_token(OR_IF))
    {
		pipe = pipeline();
		parent = conditional();
		child = make_tree(AND_IF, NULL, pipe);
		return (merge_tree(parent, child);
    }
    return (NULL);
}

// pipeline ::= command piped_command
t_node  *pipeline(t_tokenizer tokenizer)
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(COMMAND))
    {
        child = command();
        if (child)
        {
            parent = piped_command();
            if (parent)
                return (merge_tree(parent, child));
        }
		return (child);
    }
    syntax_error("Not available grammar");
    return (NULL);
}

// piped_command ::= PIPE pipeline
// piped_command ::= empty
t_node  *piped_command(t_tokenizer tokenizer)
{
	t_node  *child;

	if (match_token(PIPE))
	{
		child = pipeline(tokenizer);
		return (make_tree(PIPE, NULL, child));
	}
	return (NULL);
}
