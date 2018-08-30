#include "../libfiller.h"

# define BUFF_SIZE 12

typedef struct		s_lst
{
	char			*var;
	int				fd;
	struct s_lst	*next;
}					t_lst;

int get_next_line(const int fd, char **line)
{
    static t_lst *first = NULL;
    char *str;
    char buf[BUFF_SIZE];
    size_t i;
    size_t b;
    int res;
    t_lst *crnt;
	t_lst *fordel;
    char *temp;
    i = 0;
    if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, "", 0))
        return (-1);
    if (first == NULL) // ���� ������ ��������� � �������, ��������� ���������
    {
        if (!(first = (t_lst*)malloc(sizeof(t_lst)))) // �������� ������ ��� ���������
            return (-1);
        if (!(first->var = ft_strnew((size_t)0))) // �������� ������ ��� ����������� ������, �� \n - ����� ��� ������������
            return (-1);
        first->fd = fd;
        first->next = NULL;
    }
    crnt = first;
    while (crnt->fd != fd && crnt->next) // ���� fd����
        crnt = crnt->next;
    if (crnt->fd != fd) // ���� fd ���� �� ������, ��������� ��������� ������ �������
    {
        if (!(crnt->next = (t_lst*)malloc(sizeof(t_lst)))) // �������� ������ ��� ������ fd � ����� ������
            return (-1);
        if (!(crnt->next->var = ft_strnew((size_t)0))) // �������� ������ ��� ������, �� \n
            return (-1);
        crnt->next->fd = fd;
        crnt->next->next = NULL;
        crnt = crnt->next;
    }
    // �������� �� �������� � ������� �������� �������, ��������, ���� ��� �� ������ ��������� � �� ����� fd
    while (crnt->var[i] != '\n' && crnt->var[i]) // ���� � ������ \n, ��������, ���� ��� �� ������ ��������� � �� ����� fd
        i++;
    if (crnt->var[i] == '\n') // ���� ������� \n
    {
        *line = ft_strnew(i); // ������� ������, ������� �������, �������� i(������� � �����)
        *line = ft_memcpy(*line, crnt->var, i); // �������� � ��� ������, ��� �� \n
        i++; // ��������� 1��, ������ ��� i � ����� ���������� � 0
        if (ft_strlen(crnt->var) >= i) // ���� � ����������� ������ ����� \n ���� �������
        {
            str = crnt->var;
            crnt->var = ft_strnew(ft_strlen(str) - i); // �������� ������ ��� ������� ������
            crnt->var = ft_memcpy(crnt->var, &str[i], ft_strlen(str) - i); // �������� ������� ����� \n
            free (str);
        }
        return (1);
    }
    b = read(fd, buf, BUFF_SIZE);
    if (b == 0)
    {
		if (ft_strlen(crnt->var) != 0) // ���� ����� ������
		{
            *line = crnt->var; // ���� � ����������� ���������� ���� �������
			crnt->var = ft_strnew((size_t)0);
			return (1);
		}
		else
		{
			fordel = first;
			if (first->fd == crnt->fd)
			{
				first = crnt->next;
			}
			else
			{
				while (fordel->next != crnt) // ���� fd����
					fordel = fordel->next;
				fordel->next = crnt->next;
			}
			free(crnt->var);
			free(crnt);
			*line = ft_strnew((size_t)0);
			return (0);
		}

    }
    i = 0;
    while (buf[i] != '\n' && i < b) // ���� � ������ ���������� ���� \n
        i++;
        if (buf[i] == '\n' && i != b) // ���� �������
    {
        temp = ft_strnew(i); // ������� ������ �������� ��������� �������� �� \n
        temp = ft_memcpy(temp, buf, i); //�������� � ���� � ������, ������� ����� ��������
        *line = ft_strjoin(crnt->var, temp); // ������������� ������ ����������� � ������������� � ���� �� \n
        free(temp);
        i++;
        if (b >= i) // ���� ����� \n ���� ��� ��������� �������
        {
            free(crnt->var);
			crnt->var = ft_strnew(b - i); // �������� ������, ����� ��������� ��
            crnt->var = ft_memcpy(crnt->var, &buf[i], b - i); // �������� ������� ����� \n
        }
        return (1);
    }
    else // ���� �� ������� \n
    {
        temp = ft_strnew(b);
        temp = ft_memcpy(temp, buf, b);
        str = ft_strjoin(crnt->var, temp);
        free(temp);
        free(crnt->var);
        crnt->var = ft_strnew((size_t)0);
        res = get_next_line(fd, line);
        temp = *line;
        if (res == 1 || res == 0)
            *line = ft_strjoin(str, temp);
        free(temp);
		if (res == -1)
			return (-1);
    }
    return (1);
}
