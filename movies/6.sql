SELECT AVG(rating) FROM movies JOIN ratings WHERE ratings.movie_id=movies.id AND year=2012;
