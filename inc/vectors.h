t_vector	rotate_vector(t_vector vector, float ang);
t_point		go_vector(t_point init, t_vector vector, int steps);
t_vector	normalize_vector(t_vector vector);
t_point		get_colision(t_line wall, t_line ray);
t_line		vector_to_line(t_vector vector, t_point pos, int steps);
t_point		*get_ray_colider(t_point pos, t_line wall);
t_point		*get_dir_ray_colider(t_point pos, t_vector dir, int wide, t_line wall);
