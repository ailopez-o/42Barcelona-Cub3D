void	my_pixel_put(t_mlx *screen, t_point pixel);
void	draw_line(t_mlx *screen, t_point start, t_point end);
void	draw_vector(t_mlx *screen, t_vector vector, t_point pos, int color);
void 	clear_screen(t_mlx *screen);
void	draw_player(t_mlx *screen, t_player player);
void 	draw_circle(t_mlx *screen, t_point center, int radius, int color);
void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos, t_colision *colisions);
void    draw_polygon(t_mlx *screen, t_polygon *polygon);
void    draw_objets(t_mlx *screen, t_objet *objets);
