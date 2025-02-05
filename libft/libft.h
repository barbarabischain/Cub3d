/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:31:37 by madias-m          #+#    #+#             */
/*   Updated: 2024/11/27 13:56:45 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// ft_printf
typedef struct s_flags
{
	int	hash;
	int	space;
	int	plus;
	int	space_fix;
	int	hyphen;
	int	o;
}	t_flags;

// Hash Table
# define FNV_OFFSET 14695981039346656037UL
# define FNV_PRIME 1099511628211UL

typedef struct s_item	t_item;
typedef struct s_table	t_table;

struct s_item
{
	long	key;
	void	*value;
	int		index;
};

struct s_table
{
	t_item	*items;
	int		size;
	int		capacity;
	void	(*add)(t_table, char *, void *);
	void	(*pop)(t_table, char *);
	void	(*get)(t_table, char *);
};

t_table	*hash_table_create(void);
void	hash_table_destroy(t_table *ht);

// Standard Libft
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_count_algarisms(size_t nbr, int base);
char	*get_next_line(int fd);
int		ft_printf(const char *str, ...);
void	put_char(int c, void *f, int *count);
void	put_str(char *str, void *f, int *count);
void	put_nbr(long nbr, t_flags *f, int *count);
void	put_unbr(unsigned int nbr, t_flags *f, int *count);
void	put_nbr_hex(size_t n, int is_low, t_flags *f, int *count);
void	put_ptr(size_t n, t_flags *f, int *count);
void	before(int len, t_flags *f, int *count);
void	after(int len, t_flags *f, int *count);
void	put_zero(int len, t_flags *f, int *count);

void	ft_printf_fd(int fd, const char *str, ...);

#endif
