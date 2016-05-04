package fr.vmarchaud.matcha.routes;

import static spark.Spark.*;

public class AuthRoute extends Route {

	public static final String END_POINT = "/auth/";
	
	public void registerRoutes() {
		
		get(END_POINT + "login", (request, response) -> {
			return "lol";
		});
		
	}
}
