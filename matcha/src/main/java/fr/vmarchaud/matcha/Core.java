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
	}
}
