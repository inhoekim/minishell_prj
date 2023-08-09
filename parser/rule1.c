#include "minishell.h"
// make_tree함수, make_leaf함수, make_and함수, make_or함수, syntax_error함수, check_first_set함수

// msh_grammar ::= pipeline conditional
t_node *msh_grammar()
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(PIPELINE) == TRUE)
    {
        parent = pipeline();
        if (parent)
        {
            child = conditional();
            if (child)
                return (make_tree(parent, child));
        }
    }
    syntax_error("Not available grammar");
    free_node(parent);
    return (NULL);
}

// conditional ::= AND pipeline conditional
// conditional ::= OR pipeline conditional
// conditional ::= empty
t_node *conditional()
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(AND) == TRUE)
    {
        parent = pipeline();
        if (parent)
        {
            child = conditional();
            if (child)
                return (make_and(parent, child));
        }
    }
    else if (check_first_set(OR) == TRUE)
    {
        parent = pipeline();
        if (parent)
        {
            child = conditional();
            if (child)
                return (make_or(parent, child));
        }
    }
    return (NULL);  
}

// pipeline ::= command piped_command
t_node  *pipeline()
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(COMMAND) == TRUE)
    {
        parent = command();
        if (parent)
        {
            child = piped_command();
            if (child)
                return (make_tree(parent, child));
        }
    }
    syntax_error("Not available grammar");
    return (NULL);
}
// command ::= simple_cmd
// command ::= ssh io_redirect_star
t_node *command()
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(SIMPLE_CMD) == TRUE)
    {
        parent = simple_cmd();
        return (parent);
    }
    else if (check_first_set(ssh))
    {
        parent = ssh();
        if (parent)
        {
            child =  io_redirect_star();
            if (child)
                return (make_tree(parent, child));
        }
    }
    syntax_error("Not available grammar");
    return (NULL);
}

// piped_command ::= PIPE pipeline
// piped_command ::= empty
t_node  *piped_command()
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(PIPE) == TRUE)
    {
        parent = make_leaf();
        child = pipeline();
        return (make_tree(parent, child));
    }
    return (NULL);
}

// ssh ::= LBRACE msh_grammar RBRACE
t_node  *ssh()
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(LBRACE) == TRUE)
    {
        // LBRACE이면 리프를 만드는데, 뒤에 RBRACE가 있는데 이것을 어떻게 붙일것인지
        parent = make_leaf();
        child = msh_grammar();
        return (make_tree(parent, child));
    }
    return (NULL);
}
// simple_cmd ::= WORD io_redirect_star
// simple_cmd ::= io_redirect_dagger io_redirect_dg_after_simple_cmd
t_node  *simple_cmd()
{
    t_node  *parent;
    t_node  *child;

    if (check_first_set(WORD) == TRUE)
    {
        parent = make_leaf();
        child = io_redirect_star();
        if (child)
            return (make_tree(parent, child));
    }
    else if (check_first_set(IO_REDIRECT) == TRUE)
    {
        parent = io_redirect_dagger();
        if (parent)
        {
            child = io_redirect_dg_after_simple_cmd();
            if (child)
                return (make_tree(parent, child));
        }
    }
    return (NULL);
}
// io_redirect_dg_after_simple_cmd ::= WORD io_redirect_star
// io_redirect_dg_after_simple_cmd ::= empty
t_node  *io_redirect_dg_after_simple_cmd()
{
    t_node  *parent;
    t_node  *child;
    
    if (check_first_set(WORD) == TRUE)
    {
        parent = make_leaf();
        child = io_redirect_star();
        return (make_tree(parent, child));
    }
    return (NULL);
}
// io_redirect_dagger ::= io_redirect io_redirect_star
t_node  *io_redirect_dagger()
{
    t_node  *parent;
    t_node  *child;
    if (check_first_set(IO_REDIRECT) == TRUE)
    {
        parent = io_redirect();
        if (parent)
        {
            child = io_redirect_star();
            return (make_tree(parent, child));
        }
    }
    return (NULL);
}
// io_redirect_star ::= io_redirect io_redirect_star
// io_redirect_star ::= empty
t_node  *io_redirect_star()
{
    t_node  *parent;
    t_node  *child;
    if (check_first_set(IO_REDIRECT) == TRUE)
    {
        parent = io_redirect();
        if (parent)
        {
            child = io_redirect_star();
            return (make_tree(parent, child));
        }
    }
    return (NULL);
}
// io_redirect ::= io_file
// io_redirect ::= io_here
t_node  *io_redirect()
{
    t_node  *parent;
    t_node  *child;
	
	if (check_first_set(IO_FILE) == TRUE)
		return(io_file());
	return (io_here());
}
// io_file ::= LESS WORD
// io_file ::= GREAT WORD
// io_file ::= DGREAT WORD
t_node  *io_file()
{
    t_node  *parent;
    t_node  *child;
	
	if(check_first_set(LESS) == TRUE)
    {
        return (make_io(LESS, parent));
    }
	if (check_first_set(GREAT) == TRUE)
    {
        return (make_io(GREAT, parent));
    }
	if (check_first_set(DGREAT) == TRUE)
	{
        make_io(DGREAT, parent)
    }
	return (NULL);
}
// io_here ::= DLESS WORD
t_node  *io_here()
{
    t_node  *parent;
    t_node  *child;

	if (check_first_set(DLESS) == TRUE)
        return(make_io(DLESS, parent));
}