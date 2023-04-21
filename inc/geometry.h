t_colision 	*get_dir_ray_collider(t_point pos, t_vector dir, int wide, t_objet *objets);
t_vector	rotate_vector(t_vector vector, float ang);
t_point		go_vector(t_point init, t_vector vector, int steps);
t_vector	normalize_vector(t_vector vector);
t_line		vector_to_line(t_vector vector, t_point pos, int steps);
t_vector	get_unit_vector(t_point p1, t_point p2);
float		vector_to_angle(t_vector vector);
bool		is_horizontal(t_line line);
bool		is_horizontal(t_line line);

