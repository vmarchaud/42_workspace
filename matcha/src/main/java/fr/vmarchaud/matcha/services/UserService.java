package fr.vmarchaud.matcha.services;

import java.util.UUID;

import org.sql2o.Connection;

import fr.vmarchaud.matcha.Core;
import fr.vmarchaud.matcha.objects.User;

public class UserService {
	
	/**
	 * Query an user from his id
	 * @param UUID
	 * @return User object or null if not found
	 */
	public User query(UUID id) {
		String sql = "SELECT * FROM users WHERE id = " + id.toString();
		try(Connection con = Core.getDatabase().open()) {
			return con.createQuery(sql).executeAndFetch(User.class).stream().findFirst().orElse(null);
		}
	}
	
	public boolean update(User user) {
		return false;
	}
}
