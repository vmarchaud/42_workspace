package fr.vmarchaud.matcha;

import static spark.Spark.*;

public class Core {

	// Entry point for this program
	public static void main(String[] args) {
		new Core(args);
	}
	
	// Class access
	public static Core instance;

	public Core(String[] args) {
		instance = this;
		
		// setup mode
		port(4242);
		
		after((request, response) -> {
		    response.header("Content-Encoding", "gzip");
		});
		
		before((request, response) -> {
		    boolean authenticated = false;
		    // ... check if authenticated
		    if (!authenticated) {
		        halt(401, "You are not welcome here");
		    }
		});
	}
}
